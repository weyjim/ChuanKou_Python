import serial
import re
 
ser = serial.Serial()
ser.baudrate = 9600   #波特率
ser.port = '/dev/ttyUSB0'       #串口号
print(ser)              #打印串口信息
ser.open()
if(ser.is_open):
    print("串口打开成功") 

while(1):
    Bytes = ser.readline()              #读取字符串至\n或\r(注意timeout)
    Bytes_Str = Bytes.decode('unicode_escape')   #byte转字符
    print(Bytes_Str , end='\0')         #字符串中已包含\n，故pirnt不换行
    Bytes_float = re.findall(r"\d+\.?\d*",Bytes_Str)    #正则转换为纯数字字符串列表
    PWM = float(Bytes_float[0])         #得到float变量
    
    print("PWM=" , PWM , type(PWM) , '\n')
#    print(type(Bytes_Str))