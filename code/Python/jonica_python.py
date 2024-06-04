### Estructura genérica del programa
import os
import serial
import time
import argparse
import numpy as np
import sys
import cv2
import importlib.util
from enum import Enum
from flask import Flask, render_template, Response
from threading import Thread
from paho.mqtt import client as mqtt_client

### -------------------------------------------------------------------------------- MQTT comm config
mqtt_config_dict = {
    "broker": '192.168.100.28', # IP addr
    "port": 1883, # Port, generalmente 1883
    "client_id": "RaspberryPiClient",
}

subscription_topics = [
    "/mode",
    "/setup",
    "/object/reset",
]

publishing_topics = {
    "cube_green": "/object/green/cube",
    "cube_red": "/object/green/cube",
    "sphere_green": "/object/green/cube",
    "sphere_red": "/object/green/cube",
}

### -------------------------------------------------------------------------------- Serial comm config
# TODO: El puerto estaría bueno detectarlo solo, o pasarlo como argumento. Ojo que en Ubuntu es distinto!!
serial_config_dict = {
    "baud_rate": 9600,
    "port": 'COM3',
}
# arduino = serial.Serial(serial_config_dict["port"], serial_config_dict["baud_rate"]) # Serial config

CLASSIFIER_SERVO_MOTOR_PREFIX = "smclass"
RAMP_SERVO_MOTOR_PREFIX = "smramp"
MODE_PREFIX = "mode"
CLASSIFICATION_CYCLE_FINISHED = "cycle_finished"

RAMP_SERVO_MOTOR_CLOSE_ANGLE = '0'
RAMP_SERVO_MOTOR_OPEN_ANGLE = '90'
CLASSIFIER_SERVO_MOTOR_INITIAL_ANGLE = '0'

class Modes(Enum):
    STOP = 0
    RUN = 1

global_mode = Modes.STOP.value
global_cycle_finished = True

### -------------------------------------------------------------------------------- Global variables
global_objects_qty = {
    "cube_green": 0,
    "cube_red": 0,
    "sphere_green": 0,
    "sphere_red": 0
} 

# Capaz es al pedo, puede ser un comentario
class ClassifierModes(Enum):
    UNIQUE_OBJECT_SINGLE_CONTAINER = 1
    UNIQUE_OBJECT_DOUBLE_CONTAINER = 2
    COLOR_DOUBLE_CONTAINER = 3
    SHAPE_DOUBLE_CONTAINER = 4

global_classifier_mode = '1'

global_classifier_motor_angles = {
    "1": {
        "cube_green": "20", # Harcodearlooooos
        "cube_red": "60",
        "sphere_green": "100",
    },
    "2": {
        "cube_green": "0", # Harcodearlooooos
        "cube_red": "80",
        "sphere_green": "160",
    },
    "3": {
        "cube_green": "0", # Harcodearlooooos
        "cube_red": "80",
        "sphere_green": "0",
    },
    "4": {
        "cube_green": "0", # Harcodearlooooos
        "cube_red": "0",
        "sphere_green": "80",
    },
}

### -------------------------------------------------------------------------------- Live video config
app = Flask(__name__)

# camera = cv2.VideoCapture(0) # Cambiar por el correspondiente

### -------------------------------------------------------------------------------- MQTT functions
def mqtt_connect():
    def on_connect(client, userdata, flags, rc):
        if rc == 0:
            # DEBUG
            print("Connected to MQTT Broker!")
        else:
            # DEBUG
            print("Failed to connect, return code %d\n", rc)
  
    # Set Connecting Client ID
    client = mqtt_client.Client(mqtt_config_dict["client_id"])

    client.on_connect = on_connect
    client.connect(mqtt_config_dict["broker"], mqtt_config_dict["port"])
    return client

def mqtt_run():
    client = mqtt_connect()
    mqtt_subscribe(client)
    client.loop_start()
    return client

def mqtt_subscribe(client):
    def on_message(client, userdata, msg):
        # DEBUG
        # print(f"Received `{msg.payload.decode()}` from `{msg.topic}` topic")
        topic_handlers = {
            subscription_topics[0]: handle_mode_topic,
            subscription_topics[1]: handle_classifier_mode_topic,
            subscription_topics[2]: handle_reset_topic,
        }
        handler = topic_handlers.get(msg.topic, handle_default)
        handler(msg)

    for topic in subscription_topics:
        client.subscribe(topic)
    client.on_message = on_message

def handle_mode_topic(msg):
    global global_cycle_finished
    global global_mode

    global_mode = int(msg.payload.decode())
    send_serial_msg(arduino, MODE_PREFIX, str(global_mode))
    if global_mode == Modes.RUN.value:
        global_cycle_finished = False
    
    # DEBUG
    # print(f"Mode: `{global_mode}`")

def handle_reset_topic(msg):
    for object_ in global_objects_qty:
        global_objects_qty[object_] = 0
        # DEBUG
        # print("Reset `{object_}` to `{global_objects_qty[object_]}`")

def handle_classifier_mode_topic(msg):
    global_classifier_mode = msg.payload.decode()
    # print("Classification mode `{global_classifier_mode}`")


def handle_default(msg):
    # DEBUG
    print(f"Unhandled topic: {msg.topic}")

### -------------------------------------------------------------------------------- Serial functions
# Sirve tanto para el ángulo como para el modo
def send_serial_msg(serial_conn, prefix, msg):
    serial_message = prefix + str(msg) + "\n" 
    serial_conn.write(serial_message.encode())  # Codifica y envía el mensaje
    
    # DEBUG
    print("PYTHON: Mensaje enviado:", serial_message.strip())

def receive_cycle_finished(serial_conn):
    serial_message = serial_conn.readline().decode().strip()  # Lee una línea completa del puerto serie y la decodifica a una cadena
    if serial_message == CLASSIFICATION_CYCLE_FINISHED:
        return True
    return False   

### -------------------------------------------------------------------------------- Live video
def gen_frames():  
    while True:
        success, frame = camera.read()  # read the camera frame
        if not success:
            break
        else:
            ret, buffer = cv2.imencode('.jpg', frame)
            frame = buffer.tobytes()
            yield (b'--frame\r\n'
                   b'Content-Type: image/jpeg\r\n\r\n' + frame + b'\r\n')  # concat frame one by one and show result

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/video_feed')
def video_feed():
    return Response(gen_frames(), mimetype='multipart/x-mixed-replace; boundary=frame')

def run_flask_app():
    app.run(host="192.168.1.5", port=5000)

### -------------------------------------------------------------------------------- Image Classification
# Define VideoStream class to handle streaming of video from webcam in separate processing thread
# Source - Adrian Rosebrock, PyImageSearch: https://www.pyimagesearch.com/2015/12/28/increasing-raspberry-pi-fps-with-python-and-opencv/
class VideoStream:
    """Camera object that controls video streaming from the Picamera"""
    def __init__(self,resolution=(640,480),framerate=30):
        # Initialize the PiCamera and the camera image stream
        self.stream = cv2.VideoCapture(0)
        ret = self.stream.set(cv2.CAP_PROP_FOURCC, cv2.VideoWriter_fourcc(*'MJPG'))
        ret = self.stream.set(3,resolution[0])
        ret = self.stream.set(4,resolution[1])
            
        # Read first frame from the stream
        (self.grabbed, self.frame) = self.stream.read()

	# Variable to control when the camera is stopped
        self.stopped = False

    def start(self):
	# Start the thread that reads frames from the video stream
        Thread(target=self.update,args=()).start()
        return self

    def update(self):
        # Keep looping indefinitely until the thread is stopped
        while True:
            # If the camera is stopped, stop the thread
            if self.stopped:
                # Close camera resources
                self.stream.release()
                return

            # Otherwise, grab the next frame from the stream
            (self.grabbed, self.frame) = self.stream.read()

    def read(self):
	# Return the most recent frame
        return self.frame

    def stop(self):
	# Indicate that the camera and thread should be stopped
        self.stopped = True

### -------------------------------------------------------------------------------- Main
if __name__ == '__main__':    
    # Inicializaciones
    # client = mqtt_run() # Mqtt config
    
    # flask_thread = Thread(target=run_flask_app)
    # flask_thread.daemon = True  # Permite que el thread se cierre al terminar el programa principal
    # flask_thread.start()

    
    ### /* ----- Image classification
    # Define and parse input arguments
    parser = argparse.ArgumentParser()
    parser.add_argument('--modeldir', help='Folder the .tflite file is located in',
                        required=True)
    parser.add_argument('--graph', help='Name of the .tflite file, if different than detect.tflite',
                        default='detect.tflite')
    parser.add_argument('--labels', help='Name of the labelmap file, if different than labelmap.txt',
                        default='labelmap.txt')
    parser.add_argument('--threshold', help='Minimum confidence threshold for displaying detected objects',
                        default=0.5)
    parser.add_argument('--resolution', help='Desired webcam resolution in WxH. If the webcam does not support the resolution entered, errors may occur.',
                        default='1280x720')
    parser.add_argument('--edgetpu', help='Use Coral Edge TPU Accelerator to speed up detection',
                        action='store_true')

    args = parser.parse_args()

    MODEL_NAME = args.modeldir
    GRAPH_NAME = args.graph
    LABELMAP_NAME = args.labels
    min_conf_threshold = float(args.threshold)
    resW, resH = args.resolution.split('x')
    imW, imH = int(resW), int(resH)
    use_TPU = args.edgetpu

    # Import TensorFlow libraries
    # If tflite_runtime is installed, import interpreter from tflite_runtime, else import from regular tensorflow
    # If using Coral Edge TPU, import the load_delegate library
    pkg = importlib.util.find_spec('tflite_runtime')
    if pkg:
        from tflite_runtime.interpreter import Interpreter
        if use_TPU:
            from tflite_runtime.interpreter import load_delegate
    else:
        from tensorflow.lite.python.interpreter import Interpreter
        if use_TPU:
            from tensorflow.lite.python.interpreter import load_delegate

    # If using Edge TPU, assign filename for Edge TPU model
    if use_TPU:
        # If user has specified the name of the .tflite file, use that name, otherwise use default 'edgetpu.tflite'
        if (GRAPH_NAME == 'detect.tflite'):
            GRAPH_NAME = 'edgetpu.tflite'       

    # Get path to current working directory
    CWD_PATH = os.getcwd()

    # Path to .tflite file, which contains the model that is used for object detection
    PATH_TO_CKPT = os.path.join(CWD_PATH,MODEL_NAME,GRAPH_NAME)

    # Path to label map file
    PATH_TO_LABELS = os.path.join(CWD_PATH,MODEL_NAME,LABELMAP_NAME)

    # Load the label map
    with open(PATH_TO_LABELS, 'r') as f:
        labels = [line.strip() for line in f.readlines()]

    # Have to do a weird fix for label map if using the COCO "starter model" from
    # https://www.tensorflow.org/lite/models/object_detection/overview
    # First label is '???', which has to be removed.
    if labels[0] == '???':
        del(labels[0])

    # Load the Tensorflow Lite model.
    # If using Edge TPU, use special load_delegate argument
    if use_TPU:
        interpreter = Interpreter(model_path=PATH_TO_CKPT,
                                experimental_delegates=[load_delegate('libedgetpu.so.1.0')])
        print(PATH_TO_CKPT)
    else:
        interpreter = Interpreter(model_path=PATH_TO_CKPT)

    interpreter.allocate_tensors()

    # Get model details
    input_details = interpreter.get_input_details()
    output_details = interpreter.get_output_details()
    height = input_details[0]['shape'][1]
    width = input_details[0]['shape'][2]

    floating_model = (input_details[0]['dtype'] == np.float32)

    input_mean = 127.5
    input_std = 127.5

    # Check output layer name to determine if this model was created with TF2 or TF1,
    # because outputs are ordered differently for TF2 and TF1 models
    outname = output_details[0]['name']

    if ('StatefulPartitionedCall' in outname): # This is a TF2 model
        boxes_idx, classes_idx, scores_idx = 1, 3, 0
    else: # This is a TF1 model
        boxes_idx, classes_idx, scores_idx = 0, 1, 2

    # Initialize frame rate calculation
    frame_rate_calc = 1
    freq = cv2.getTickFrequency()

    # Initialize video stream
    videostream = VideoStream(resolution=(imW,imH),framerate=30).start()
    time.sleep(1)
    ### ----- Image classification */


    # Loop principal
    while True:
        ### /* ----- Image classification
        # Start timer (for calculating frame rate)
        t1 = cv2.getTickCount()

        # Grab frame from video stream
        frame1 = videostream.read()

        # Acquire frame and resize to expected shape [1xHxWx3]
        frame = frame1.copy()
        frame_rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        frame_resized = cv2.resize(frame_rgb, (width, height))
        input_data = np.expand_dims(frame_resized, axis=0)

        # Normalize pixel values if using a floating model (i.e. if model is non-quantized)
        if floating_model:
            input_data = (np.float32(input_data) - input_mean) / input_std

        # Perform the actual detection by running the model with the image as input
        interpreter.set_tensor(input_details[0]['index'],input_data)
        interpreter.invoke()

        # Retrieve detection results
        boxes = interpreter.get_tensor(output_details[boxes_idx]['index'])[0] # Bounding box coordinates of detected objects
        classes = interpreter.get_tensor(output_details[classes_idx]['index'])[0] # Class index of detected objects
        scores = interpreter.get_tensor(output_details[scores_idx]['index'])[0] # Confidence of detected objects

        # Loop over all detections and draw detection box if confidence is above minimum threshold
        for i in range(len(scores)):
            if ((scores[i] > min_conf_threshold) and (scores[i] <= 1.0)):

                # Get bounding box coordinates and draw box
                # Interpreter can return coordinates that are outside of image dimensions, need to force them to be within image using max() and min()
                ymin = int(max(1,(boxes[i][0] * imH)))
                xmin = int(max(1,(boxes[i][1] * imW)))
                ymax = int(min(imH,(boxes[i][2] * imH)))
                xmax = int(min(imW,(boxes[i][3] * imW)))
                
                cv2.rectangle(frame, (xmin,ymin), (xmax,ymax), (10, 255, 0), 2)

                # Draw label
                object_name = labels[int(classes[i])] # Look up object name from "labels" array using class index
                label = '%s: %d%%' % (object_name, int(scores[i]*100)) # Example: 'person: 72%'
                labelSize, baseLine = cv2.getTextSize(label, cv2.FONT_HERSHEY_SIMPLEX, 0.7, 2) # Get font size
                label_ymin = max(ymin, labelSize[1] + 10) # Make sure not to draw label too close to top of window
                cv2.rectangle(frame, (xmin, label_ymin-labelSize[1]-10), (xmin+labelSize[0], label_ymin+baseLine-10), (255, 255, 255), cv2.FILLED) # Draw white box to put label text in
                cv2.putText(frame, label, (xmin, label_ymin-7), cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 0, 0), 2) # Draw label text

                if (scores[i]*100) > 90: 
                    # print(f'Detected object: {object_name}, Confidence: {scores[i] 100:.2f}%')
                    object_identified_name = object_name

        # Draw framerate in corner of frame
        cv2.putText(frame,'FPS: {0:.2f}'.format(frame_rate_calc),(30,50),cv2.FONT_HERSHEY_SIMPLEX,1,(255,255,0),2,cv2.LINE_AA)

        # All the results have been drawn on the frame, so it's time to display it.
        cv2.imshow('Object detector', frame)

        # Calculate framerate
        t2 = cv2.getTickCount()
        time1 = (t2-t1)/freq
        frame_rate_calc= 1/time1
        ### ----- Image classification */
        
        # Las imagenes se deben mostrar y publicar de forma constante. Ver el tema de los threads?

        # Si está en RUN, mandar las posiciones de los motores
        # Se debe verificar el modo para ver que mover o que no
        # Contar las piezas, ir incrementando de a uno. La variables es global_objects_qty
        if global_mode == Modes.RUN.value or (global_mode == Modes.STOP.value and global_cycle_finished == False): 
            if object_identified_name == "sphere_red":
                # send_serial_msg(arduino, RAMP_SERVO_MOTOR_PREFIX, RAMP_SERVO_MOTOR_OPEN_ANGLE)
                print(RAMP_SERVO_MOTOR_PREFIX + RAMP_SERVO_MOTOR_OPEN_ANGLE)
            else:
                # send_serial_msg(arduino, RAMP_SERVO_MOTOR_PREFIX, RAMP_SERVO_MOTOR_CLOSE_ANGLE)
                sleep(10)
                print(RAMP_SERVO_MOTOR_PREFIX + RAMP_SERVO_MOTOR_CLOSE_ANGLE)
                # send_serial_msg(arduino, CLASSIFIER_SERVO_MOTOR_PREFIX, global_classifier_motor_angles[global_classifier_mode][object_identified_name])
                print(CLASSIFIER_SERVO_MOTOR_PREFIX + global_classifier_motor_angles[global_classifier_mode][object_identified_name])

            # código de ML. Cuando detecta algo, mover los motores según corresponda.
            # El ángulo dependerá del modo del clasificador
            None
        
        # Espero a que finalice el ciclo de la cinta y no hago nada
        if global_mode == Modes.STOP.value:
            if global_cycle_finished == False:
                global_cycle_finished = receive_cycle_finished(arduino)

        # Press 'q' to quit
        if cv2.waitKey(1) == ord('q'):
            break
    
    # Clean up
    cv2.destroyAllWindows()
    videostream.stop()