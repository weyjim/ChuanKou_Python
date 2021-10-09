import serial
 
ser = serial.Serial()   #这里可以直接初始化
ser.baudrate = 115200   #波特率
ser.port = 'COM5'       #串口号
print(ser)
ser.open()
print(ser.is_open)      #成功打开会显示True

Str_flag = 0               #字符串转数据标志位
i = 0                   

while(1):
    Bytes = ser.readline()              #读取字符串至\n或\r(注意timeout)
    Bytes_Str = Bytes.decode('utf-8')   #byte转字符
    print(Bytes_Str , end='\0')         #字符串中已包含\n，故pirnt不换行
            
