import serial
import time

# Configura la comunicación serial
arduino = serial.Serial('COM3', 9600)  # Asegúrate de cambiar 'COM3' al puerto que estás utilizando

try:
    while True:
        # Envía el mensaje al Arduino
        mensaje = "m1p60\n"  # Formato del mensaje: m1p60, seguido de un salto de línea
        arduino.write(mensaje.encode())  # Codifica y envía el mensaje
        
        print("PYTHON: Mensaje enviado:", mensaje.strip())  # Imprime el mensaje enviado
        
        time.sleep(1)  # Espera 1 segundo antes de enviar el siguiente mensajes
except KeyboardInterrupt:
    arduino.close()  # Cierra la conexión serial cuando se interrumpe el programa
