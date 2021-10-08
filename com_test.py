import serial
 
ser = serial.Serial()   #这里可以直接初始化
ser.baudrate = 115200   #波特率
ser.port = 'COM5'       #串口号
print(ser)
ser.open()
print(ser.is_open)      #成功打开会显示True

while(1):
    Bytes = serial.readline()
    Bytes_Str = Bytes.decode('utf-8')    #byte转字符
    print(Bytes_Str)
