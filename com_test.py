import serial
import easygui
import time
 
ser = serial.Serial()
ser.baudrate = 9600
ser.port = 'COM5'
print(ser)
ser.open()
print(ser.is_open)
i=1

while(1):
    demo=b"1"
    ser.write(demo)
    s = ser.read(1)
    print(s)
    time.sleep(0.1)
    demo = b"2"
    ser.write(demo)
    s = ser.read(1)
    print(s)
    time.sleep(0.1)
