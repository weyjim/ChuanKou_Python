import serial
import re
import matplotlib.pyplot as plt
import numpy as np
 
ser = serial.Serial()
ser.baudrate = 115200   #波特率
ser.port = 'COM5'       #串口号
print(ser)              #打印串口信息
ser.open()
if(ser.is_open):
    print("串口打开成功")

plt,ion()
plt.figure()

t = [0]

PWM_SAVE = 0

while(1):
    plt.clf()
    
    Bytes = ser.readline()              #读取字符串至\n或\r(注意timeout)
    Bytes_Str = Bytes.decode('utf-8')   #byte转字符
    print(Bytes_Str , end='\0')         #字符串中已包含\n，故pirnt不换行
    Bytes_float = re.findall(r"\d+\.?\d*",Bytes_Str)    #正则转换为纯数字字符串列表
    PWM = float(Bytes_float[0])         #得到float变量
    
    print("PWM=" , PWM , type(PWM) , '\n')

    t.append(PWM)
    plt.plot(PWM, PWM_SAVE, '-r')

    plt.pause(0.01)
    PWM_SAVE = PWM

