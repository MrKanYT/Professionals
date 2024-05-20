import serial
import time

if __name__ == '__main__':
    #ser = serial.Serial('/dev/ttyUSB0', 115200, timeout=3)
    ser = serial.Serial('COM5', 115200, timeout=3)
    '''while True:
        t = ser.readline()
        line = t.decode('utf-8').rstrip()
        print(line)'''
    ser.write("R90\n".encode("ascii"))
    while True:
            t = ser.readline()
            line = t.decode('ascii').rstrip()
            print(line)