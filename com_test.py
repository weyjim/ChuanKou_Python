import serial
import time
 
ser = serial.Serial()   #这里可以直接初始化
ser.baudrate = 115200   #波特率
ser.port = 'COM5'       #串口号
print(ser)
ser.open()
print(ser.is_open)      #成功打开会显示True

while(1):
    data = ser.read(1)  #读取 Byte
    print(data[1])
