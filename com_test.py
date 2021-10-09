import serial
import re
 
ser = serial.Serial()
ser.baudrate = 115200   #波特率
ser.port = 'COM5'       #串口号
print(ser)              #打印串口信息
ser.open()
if(ser.is_open):
    print("串口打开成功") 

while(1):
    Bytes = ser.readline()              #读取字符串至\n或\r(注意timeout)
    Bytes_Str = Bytes.decode('utf-8')   #byte转字符
    print(Bytes_Str , end='\0')         #字符串中已包含\n，故pirnt不换行
    Bytes_float = re.findall(r"\d+\.?\d*",Bytes_Str)    #正则转换为
    PWM = float(Bytes_float[0])
    
    print("PWM=" , PWM , type(PWM) , '\n')
    
