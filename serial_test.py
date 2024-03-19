import time

import serial

ser = serial.Serial("COM10")

while True:
    print(ser.readline().decode("ascii"))

ser.close()