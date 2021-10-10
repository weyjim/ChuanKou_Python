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

y_axis = [0]            #定义y轴变量

#PWM_SAVE = 0            #定义PWM历史数据

for i in range(10):
    plt.clf()
    
    Bytes = ser.readline()              #读取字符串至\n或\r(注意timeout)
    Bytes_Str = Bytes.decode('utf-8')   #byte转字符
    print(Bytes_Str , end='\0')         #字符串中已包含\n，故pirnt不换行
    Bytes_float = re.findall(r"\d+\.?\d*",Bytes_Str)    #正则转换为纯数字字符串列表
    PWM = float(Bytes_float[0])         #得到float变量
    
    print("PWM=" , PWM , type(PWM) , '\n')

    y_axis.append(PWM)
#   plt.plot(PWM, PWM_SAVE, '-r')
#    PWM_SAVE = PWM
    
plt.plot(y_axis)
plt.grid(True)
plt.show()
