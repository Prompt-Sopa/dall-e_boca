import serial
import time

# Configura la comunicación serial
arduino = serial.Serial('COM3', 9600)  # Asegúrate de cambiar 'COM3' al puerto que estás utilizando

def sendPos(pos):
    mensaje = "sm1p" + str(pos) + "\n"  # Formato del mensaje: m1p60, seguido de un salto de línea
    arduino.write(mensaje.encode())  # Codifica y envía el mensaje
    print("PYTHON: Mensaje enviado:", mensaje.strip())  # Imprime el mensaje enviado

try:
    while True:
        # Envía el mensaje al Arduino

        mensaje = "mode0"  # Formato del mensaje: m1p60, seguido de un salto de línea
        arduino.write(mensaje.encode())  # Codifica y envía el mensaje
        print("PYTHON: Mensaje enviado:", mensaje.strip())  # Imprime el mensaje enviado
        time.sleep(10)
        mensaje = "mode1"  # Formato del mensaje: m1p60, seguido de un salto de línea
        arduino.write(mensaje.encode())  # Codifica y envía el mensaje
        print("PYTHON: Mensaje enviado:", mensaje.strip())  # Imprime el mensaje enviado
        time.sleep(10)
except KeyboardInterrupt:
    arduino.close()  # Cierra la conexión serial cuando se interrumpe el programa
