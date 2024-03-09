import serial

ser = serial.Serial('COM9', 9600, timeout = 1)

while 1:
    print(ser.write(b'z'))
