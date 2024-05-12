import serial, time

try:
    lista_numeros = []  # Inicializa una lista vacía para almacenar los números recibidos
    while True:
        # Lee el número entero recibido del Arduino
        numero_str = arduino.readline().decode().strip()  # Lee una línea completa del puerto serie y la decodifica a una cadena
        if numero_str:  # Verifica si la cadena no está vacía
            numero = int(numero_str)  # Convierte la cadena a un número entero
            lista_numeros.append(numero)  # Agrega el número a la lista
            
            print("Número recibido:", numero)
            print("Lista actualizada:", lista_numeros)
except KeyboardInterrupt:
    ser.close()  # Cierra la conexión serial cuando se interrumpe el programa