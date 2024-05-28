### Estructura genérica del programa
import serial
import time
from enum import Enum
from flask import Flask, render_template, Response
import cv2
import threading

### -------------------------------------------------------------------------------- MQTT comm config
mqtt_config_dict = {
    "broker": 'broker.emqx.io', # IP addr
    "port": 1883, # Port, generalmente 1883
    "client_id": "RaspberryPiClient",
}

subscription_topics = [
    "/mode",
    # Classifier container setup
    # Reset
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
print("Serial port: {} - Serial BD: {}".format(serial_config_dict["port"], serial_config_dict["baud_rate"]))
# arduino = serial.Serial(serial_config_dict["port"], serial_config_dict["baud_rate"]) # Serial config

CLASSIFIER_SERVO_MOTOR_PREFIX = "smclass"
RAMP_SERVO_MOTOR_PREFIX = "smramp"
MODE_PREFIX = "mode"
CLASSIFICATION_CYCLE_FINISHED = "cycle_finished"

RAMP_SERVO_MOTOR_CLOSE_ANGLE = 0
RAMP_SERVO_MOTOR_OPEN_ANGLE = 180
CLASSIFIER_SERVO_MOTOR_INITIAL_ANGLE = 0

class Modes(Enum):
    STOP = 0
    RUN = 1
    SETUP = 2

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

global_classifier_mode = 1

global_classifier_motor_angles = {
    "1": {
        "cube_green": 22.5, # Harcodearlooooos
        "cube_red": 22.5*2,
        "sphere_green": 22.5*3,
    },
    "2": {
        "cube_green": 22.5, # Harcodearlooooos
        "cube_red": 22.5*2,
        "sphere_green": 22.5*3,
    },
    "3": {
        "cube_green": 22.5, # Harcodearlooooos
        "cube_red": 22.5*2,
        "sphere_green": 22.5*3,
    },
    "4": {
        "cube_green": 22.5, # Harcodearlooooos
        "cube_red": 22.5*2,
        "sphere_green": 22.5*3,
    },
}

### -------------------------------------------------------------------------------- Live video config
app = Flask(__name__)

camera = cv2.VideoCapture(0) # Cambiar por el correspondiente

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
    subscribe(client)
    client.loop_start()
    return client

def mqtt_subscribe(client):
    def on_message(client, userdata, msg):
        # DEBUG
        print(f"Received `{msg.payload.decode()}` from `{msg.topic}` topic")
        topic_handlers = {
            subscription_topics[0]: handle_mode_topic,
            subscription_topics[0]: handle_classifier_container_topic,
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
    print(f"Mode: `{global_mode}`")

def handle_reset_topic(msg):
    for object_ in global_objects_qty:
        global_objects_qty[object_] = 0
        # DEBUG
        print("Reset `{object_}` to `{global_objects_qty[object_]}`")

def handle_classifier_mode_topic(msg):
    global_classifier_mode = int(msg.payload.decode())
    print("Classification mode `{global_classifier_mode}`")


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

# TODO: Actualizar por fuera el container_num
def receive_classifier_containers_id(serial_conn, container_list, container_num):
    serial_message = serial_conn.readline().decode().strip()  # Lee una línea completa del puerto serie y la decodifica a una cadena
    if serial_message:  
        container_id = int(serial_message)  # Convierte la cadena a un número entero
        container_list[container_num] = container_id  # Agrega el número a la lista
        
        # DEBUG
        print("Número recibido:", container_id)
        print("Lista actualizada:", container_list)

        return True
    return False

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

### -------------------------------------------------------------------------------- Main
if __name__ == '__main__':    
    # Inicializaciones
    # client = mqtt_run() # Mqtt config
    
    flask_thread = threading.Thread(target=run_flask_app)
    flask_thread.daemon = True  # Permite que el thread se cierre al terminar el programa principal
    flask_thread.start()

    # Loop principal
    while True:
        # Las imagenes se deben mostrar y publicar de forma constante. Ver el tema de los threads?

        # Si está en RUN, mandar las posiciones de los motores
        # Se debe verificar el modo para ver que mover o que no
        # Contar las piezas, ir incrementando de a uno. La variables es global_objects_qty
        if global_mode == Modes.RUN.value or (global_mode == Modes.STOP.value and global_cycle_finished == False): 
            # código de ML. Cuando detecta algo, mover los motores según corresponda.
            # El ángulo dependerá del modo del clasificador
            None
        
        # Espero a que finalice el ciclo de la cinta y no hago nada
        if global_mode == Modes.STOP.value:
            if global_cycle_finished == False:
                global_cycle_finished = receive_cycle_finished(arduino)
