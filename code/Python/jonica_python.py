### Estructura genérica del programa
import serial
import time
from enum import Enum

# TODO: El puerto estaría bueno detectarlo solo, o pasarlo como argumento. Ojo que en Ubuntu es distinto!!
serial_config_dict = {
    "baud_rate": 9600,
    "port": 'COM3',
}

CLASSIFIER_SERVO_MOTOR_PREFIX = "smclass"
RAMP_SERVO_MOTOR_PREFIX = "smramp"
MODE_PREFIX = "mode"

RAMP_SERVO_MOTOR_CLOSE_ANGLE = 0
RAMP_SERVO_MOTOR_OPEN_ANGLE = 180
CLASSIFIER_SERVO_MOTOR_INITIAL_ANGLE = 0
# TODO: Faltaría, según la cantidad de contenedores, definir los ángulos. Esto se hace solo una vez al comienzo y se guardan en algún lado

class Modes(Enum):
    STOP = 0
    RUN = 1
    SETUP = 2

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
    return container_list

if __name__ == '__main__':
    # Inicializaciones
    # Configura la comunicación serial
    arduino = serial.Serial(serial_config_dict["port"], serial_config_dict["baud_rate"]) 

    # Loop principal
    while True:
        # Si está en RUN, mandar las posiciones de los motores

        None

