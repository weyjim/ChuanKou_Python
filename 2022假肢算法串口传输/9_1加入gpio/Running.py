# -*- coding: utf-8 -*-
"""
Created on Thu Jul 28 14:00:36 2022

@author:  xushunzhang gaoshuai wangenyuan
"""
#import joblib
import serial
import re
import numpy as np
#import matplotlib.pyplot as plt
import sys
import tensorflow as tf
import RPi.GPIO as GPIO
import time

import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'

GPIO.setmode(GPIO.BCM)
GPIO.setup(14,GPIO.OUT)
GPIO.setup(15,GPIO.OUT)

np.set_printoptions(threshold=sys.maxsize)
data_x=[]

number_max=0.0
number_min=10000.0
model1 = tf.keras.models.load_model("Finall1.h5")



# def norm(x,max1,min1):
    # for w in range(len(x)):
    
    
    
def recognization(x,p,number_max,number_min,Bytes_float):
    EMG = [float(Bytes_float[5])]       # 得到float变量        
    EMG = np.array(EMG)
    # print(PWM[0])
    # print(len(x))
    if EMG[0]>=100 or p==1:
        if EMG[0]>=100:
            x.append(EMG)
            p=1
        if EMG[0]<100:
            x.append(float(0))
        if len(x)==164:
            for i in range(164):
                x[i]=float(x[i])
                if number_max<x[i]:
                    number_max=x[i]
                if number_min>x[i]:
                    number_min=x[i]
            x=list(x)
            print(x)
            for i in range(164):
                x[i]=round((x[i]-number_min)/(number_max-number_min),11)
               
            x=np.array(x)
            x=x.reshape(1,164)
            predict = model1.predict(x)
            results = []
            sum1=0
            sum2=0
            for i in range(len(predict)):
                if predict[i][0] > 0.5:
                    p = '1'
                    sum1=sum1+1
                else:
                    p = '0'
                    sum2 = sum2 + 1
                results.append(p)
            print(results[0])
            
            if results[0]=='0':
                GPIO.output(14,GPIO.HIGH)
                GPIO.output(15,GPIO.LOW)
                print('000')
            elif results[0]=='1':
                GPIO.output(14,GPIO.LOW)
                GPIO.output(15,GPIO.HIGH)
                print('111')

           
            # print("hi")
            p=0
            
            while(True):
                Bytes_float = readinglines()
                EMG = [float(Bytes_float[5])]     # 检测张开手臂
                if EMG[0]>200:
                    print('breaking')
                    GPIO.output(14,GPIO.LOW)
                    GPIO.output(15,GPIO.LOW)

                    break
            while(EMG[0]>50):
                Bytes_float = readinglines()
                EMG = [float(Bytes_float[5])]  # 吞掉波峰一上一下        
            print('where extension')
            GPIO.output(14,GPIO.LOW)
            GPIO.output(15,GPIO.LOW)
            
            
            x=[]
    else:
        x=[]
    return x,p




ser = serial.Serial()
ser.baudrate = 9600   #波特率
ser.port = '/dev/ttyUSB0'       #串口号
print(ser)              #打印串口信息
ser.open()
if(ser.is_open):
    print("串口打开成功")

def readinglines():
    Bytes = ser.readline()              #读取字符串至\n或\r(注意timeout)
    Bytes_Str = Bytes.decode('unicode_escape')   #win平台UTF-8,linux平台unicode_escape
    # print(Bytes_Str , end='\0')         
    Bytes_float = re.findall(r"\d+\.?\d*",Bytes_Str)    #正则，变为字符串序列
    # print(Bytes_float , end='\0')        
    return Bytes_float



recog_p=0
flag_enxtension=0

while(1):
    Bytes_float = readinglines()
    
    if len(Bytes_float)==6:             # Pi收到不满6的序列
        (data_x,recog_p) = recognization(data_x,recog_p,number_max,number_min,Bytes_float)
        #print(data_x)
    else:
        time.sleep(0.57)
        print(Bytes_float)
