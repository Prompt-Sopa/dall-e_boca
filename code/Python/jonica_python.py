### Estructura genérica del programa
import serial
import time
from enum import Enum

# TODO: El puerto estaría bueno detectarlo solo, o pasarlo como argumento. Ojo que en Ubuntu es distinto!!
serial_config_dict = {
    "baud_rate": 9600,
    "port": 'COM3',
}

mqtt_config_dict = {
    "broker": 'broker.emqx.io', # IP addr
    "port": 1883, # Port, generalmente 1883
    "client_id": "RaspberryPiClient",
}

subscription_topics = [
    "/mode",
    # Classifier container object
]

publishing_topics = {
    "green_bube": "/object/green/cube",
    "green_bube": "/object/green/cube",
    "green_bube": "/object/green/cube",
    "green_bube": "/object/green/cube",
}

CLASSIFIER_SERVO_MOTOR_PREFIX = "smclass"
RAMP_SERVO_MOTOR_PREFIX = "smramp"
MODE_PREFIX = "mode"
CLASSIFICATION_CYCLE_FINISHED = "cycle_finished"

RAMP_SERVO_MOTOR_CLOSE_ANGLE = 0
RAMP_SERVO_MOTOR_OPEN_ANGLE = 180
CLASSIFIER_SERVO_MOTOR_INITIAL_ANGLE = 0
# TODO: Faltaría, según la cantidad de contenedores, definir los ángulos. Esto se hace solo una vez al comienzo y se guardan en algún lado

CLASSIFIER_MAX_CONTAINERS = 8
CONTAINER_APERTURE = (int)(360 / CLASSIFIER_MAX_CONTAINERS)

class Modes(Enum):
    STOP = 0
    RUN = 1
    SETUP = 2

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


def mqtt_subscribe(client: mqtt_client):
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

def handle_mode_topic(data):
    mode = int(msg.payload.decode())
    # DEBUG
    print(f"Mode: `{mode}`")

# TODO: Completar
def handle_classifier_container_topic(data):
    None

def handle_default(msg):
    # DEBUG
    print(f"Unhandled topic: {msg.topic}")

### -------------------------------------------------------------------------------- Serial functions
# Sirve tanto para el ángulo como para el modo
def send_serial_msg(serial_conn: serial_conn, prefix: msg_prefix, msg: msg_data):
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
    if serial_message is CLASSIFICATION_CYCLE_FINISHED:
        return True
    return False   

def classification_angles_calculation(classifier_container_list):

    None

### -------------------------------------------------------------------------------- Main
if __name__ == '__main__':
    # Inicializaciones
    mqtt_run() # Mqtt config
    arduino = serial.Serial(serial_config_dict["port"], serial_config_dict["baud_rate"]) # Serial config

    classifier_container_list = [0, 0, 0, 0, 0, 0, 0, 0]
    container = 0

    # Loop principal
    while True:
        # Las imagenes se deben mostrar y publicar de forma constante. Ver el tema de los threads?

        # Si está en RUN, mandar las posiciones de los motores
        if mode == RUN or (mode == STOP and cycle_finished == False): 
            # Cuando detecta algo, mover los motores según corresponda
            None
        
        if mode == STOP:
            # Espera a que termine el ciclo de ejecución
            if cycle_finished == False:
                cycle_finished = receive_cycle_finished(arduino)
            
        if mode == PREPARE:
            # Lectura de los containers y ajuste de los ángulos según la detección
            if receive_classifier_containers_id(arduino, classifier_container_list, container) is True:
                if container == (CLASSIFIER_MAX_CONTAINERS - 1):
                    container = 0
                    classification_angles_calculation(classifier_container_list)
                else:
                    container = container + 1

