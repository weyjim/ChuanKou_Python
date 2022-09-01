# -*- coding: utf-8 -*-
"""
Created on Thu Jun  9 13:08:37 2022

@author: TKWAY
"""

# UART Tx/Rx demo
import tkinter as tk
from tkinter import ttk
import serial
import threading

# A simple Information Window
class InformWindow:
    def __init__(self,informStr):
        self.window = tk.Tk()
        self.window.title("Information")
        self.window.geometry("220x60")
        label = tk.Label(self.window, text=informStr)
        buttonOK = tk.Button(self.window,text="OK",command=self.processButtonOK)
        label.pack(side = tk.TOP)
        buttonOK.pack(side = tk.BOTTOM)
        self.window.mainloop()

    def processButtonOK(self):
        self.window.destroy()



Stop_Rcount=20
Stop_minute=0
Stop_hour=0

class mainGUI:
    def __init__(self):
        window = tk.Tk()
        window.title("智能时钟上位机")
        self.uartState = False # is uart open or not

        # a frame contains COM's information, and start/stop button
        frame_COMinf = tk.Frame(window)
        frame_COMinf.grid(row = 1, column = 1)

        labelCOM = tk.Label(frame_COMinf,text="串口: ")
        self.COM = tk.StringVar(value = "COM4")
        ertryCOM = tk.Entry(frame_COMinf, textvariable = self.COM)
        labelCOM.grid(row = 1, column = 1, padx = 5, pady = 3)
        ertryCOM.grid(row = 1, column = 2, padx = 5, pady = 3)

        labelBaudrate = tk.Label(frame_COMinf,text="波特率: ")
        self.Baudrate = tk.IntVar(value = 9600)
        ertryBaudrate = tk.Entry(frame_COMinf, textvariable = self.Baudrate)
        labelBaudrate.grid(row = 1, column = 3, padx = 5, pady = 3)
        ertryBaudrate.grid(row = 1, column = 4, padx = 5, pady = 3)

        labelParity = tk.Label(frame_COMinf,text="校验: ")
        self.Parity = tk.StringVar(value ="NONE")
        comboParity = ttk.Combobox(frame_COMinf, width = 17, textvariable=self.Parity)
        comboParity["values"] = ("NONE","ODD","EVEN","MARK","SPACE")
        comboParity["state"] = "readonly"
        labelParity.grid(row = 2, column = 1, padx = 5, pady = 3)
        comboParity.grid(row = 2, column = 2, padx = 5, pady = 3)

        labelStopbits = tk.Label(frame_COMinf,text="停止位: ")
        self.Stopbits = tk.StringVar(value ="1")
        comboStopbits = ttk.Combobox(frame_COMinf, width = 17, textvariable=self.Stopbits)
        comboStopbits["values"] = ("1","1.5","2")
        comboStopbits["state"] = "readonly"
        labelStopbits.grid(row = 2, column = 3, padx = 5, pady = 3)
        comboStopbits.grid(row = 2, column = 4, padx = 5, pady = 3)
        
        self.buttonSS = tk.Button(frame_COMinf, text = "Start", command = self.processButtonSS)
        self.buttonSS.grid(row = 8, column = 4, padx = 5, pady = 3, sticky = tk.E)
        
        #按键显示
        labelKEY = tk.Label(frame_COMinf,text="按键: ")
        self.KEY = tk.StringVar(value = "COM4")
        labelKEY.grid(row = 4, column = 1, padx = 5, pady = 3)
                
        self.buttonKEY1 = tk.Button(frame_COMinf, text = "KEY1", command = self.processButtonKEY1)
        self.buttonKEY1.grid(row = 5, column = 1, padx = 5, pady = 3, sticky = tk.E)
        self.buttonKEY2 = tk.Button(frame_COMinf, text = "KEY2", command = self.processButtonKEY2)
        self.buttonKEY2.grid(row = 5, column = 2, padx = 5, pady = 3, sticky = tk.E)
        self.buttonKEY3 = tk.Button(frame_COMinf, text = "KEY3", command = self.processButtonKEY3)
        self.buttonKEY3.grid(row = 6, column = 1, padx = 5, pady = 3, sticky = tk.E)
        self.buttonKEY4 = tk.Button(frame_COMinf, text = "KEY4", command = self.processButtonKEY4)
        self.buttonKEY4.grid(row = 6, column = 2, padx = 5, pady = 3, sticky = tk.E)
        self.buttonKEY5 = tk.Button(frame_COMinf, text = "KEY5", command = self.processButtonKEY5)
        self.buttonKEY5.grid(row = 7, column = 1, padx = 5, pady = 3, sticky = tk.E)
        self.buttonKEY6 = tk.Button(frame_COMinf, text = "KEY6", command = self.processButtonKEY6)
        self.buttonKEY6.grid(row = 7, column = 2, padx = 5, pady = 3, sticky = tk.E)
        
        #音乐界面
        labelMusicSelect = tk.Label(frame_COMinf,text="音乐选择: ")
        self.MusicSelect = tk.StringVar(value ="NONE")
        comboMusicSelect = ttk.Combobox(frame_COMinf, width = 17, textvariable=self.MusicSelect)
        comboMusicSelect["values"] = ("音乐1","音乐2","音乐3","NONE")
        comboMusicSelect["state"] = "readonly"
        labelMusicSelect.grid(row = 4, column = 3, padx = 5, pady = 3)
        comboMusicSelect.grid(row = 4, column = 4, padx = 5, pady = 3)
        
        #定时设置
        labelTimer = tk.Label(frame_COMinf,text="定时时间")
        self.Timer = tk.IntVar(value = "00:00:01")
        ertryTimer = tk.Entry(frame_COMinf, textvariable = self.Timer)
        labelTimer.grid(row = 6, column = 4, padx = 5, pady = 3)
        ertryTimer.grid(row = 7, column = 4, padx = 5, pady = 3)


        # serial object
        self.ser = serial.Serial()
        # serial read threading
        self.ReadUARTThread = threading.Thread(target=self.ReadUART)
        self.ReadUARTThread.start()

        frameRecv = tk.Frame(window)
        frameRecv.grid(row = 2, column = 1)
        labelOutText = tk.Label(frameRecv,text="来自nRF24L01的数据:")
        labelOutText.grid(row = 1, column = 1, padx = 3, pady = 2, sticky = tk.W)
        frameRecvSon = tk.Frame(frameRecv)
        frameRecvSon.grid(row = 2, column =1)
        scrollbarRecv = tk.Scrollbar(frameRecvSon)
        scrollbarRecv.pack(side = tk.RIGHT, fill = tk.Y)
        self.OutputText = tk.Text(frameRecvSon, wrap = tk.WORD, width = 60, height = 20, yscrollcommand = scrollbarRecv.set)
        self.OutputText.pack()

        frameTrans = tk.Frame(window)
        frameTrans.grid(row = 3, column = 1)
        labelInText = tk.Label(frameTrans,text="发送数据:")
        labelInText.grid(row = 1, column = 1, padx = 3, pady = 2, sticky = tk.W)
        frameTransSon = tk.Frame(frameTrans)
        frameTransSon.grid(row = 2, column =1)
        scrollbarTrans = tk.Scrollbar(frameTransSon)
        scrollbarTrans.pack(side = tk.RIGHT, fill = tk.Y)
        self.InputText = tk.Text(frameTransSon, wrap = tk.WORD, width = 60, height = 5, yscrollcommand = scrollbarTrans.set)
        self.InputText.pack()
        self.buttonSend = tk.Button(frameTrans, text = "Send", command = self.processButtonSend)
        self.buttonSend.grid(row = 3, column = 1, padx = 5, pady = 3, sticky = tk.E)
        
        window.mainloop()
        
    #按键功能函数
    def processButtonKEY1(self):
        global Stop_Rcount
        global Stop_minute
        global Stop_hour
        Stop_Rcount+=1
        infromStr = "KEY1 Pressed!  second++"
        InformWindow(infromStr)
        list_use = []
        for i in range(5):
            list_use.append(Stop_Rcount,Stop_minute,Stop_hour)
        data = bytes(list_use)
        self.SerialPort.write(data)

    def processButtonKEY2(self):
        global Stop_Rcount
        Stop_Rcount-=1
        infromStr = "KEY2 Pressed!  second--"
        InformWindow(infromStr)
        
    def processButtonKEY3(self):
        global Stop_minute
        Stop_minute+=1
        infromStr = "KEY3 Pressed!  显示温度"
        InformWindow(infromStr)
        
    def processButtonKEY4(self):
        global Stop_minute
        Stop_minute-=1
        infromStr = "KEY4 Pressed!  显示湿度"
        InformWindow(infromStr)
        
    def processButtonKEY5(self):
        global Stop_hour
        Stop_hour+=1
        infromStr = "KEY5 Pressed!  播放音乐"
        InformWindow(infromStr)
        
    def processButtonKEY6(self):
        global Stop_hour
        Stop_hour-=1
        infromStr = "KEY6 Pressed!  停止播放"
        InformWindow(infromStr)
        

    def processButtonSS(self):
        # print(self.Parity.get())
        if (self.uartState):
            self.ser.close()
            self.buttonSS["text"] = "Start"
            self.uartState = False
        else:
            # restart serial port
            self.ser.port = self.COM.get()
            self.ser.baudrate = self.Baudrate.get()
            
            strParity = self.Parity.get()
            if (strParity=="NONE"):
                self.ser.parity = serial.PARITY_NONE
            elif(strParity=="ODD"):
                self.ser.parity = serial.PARITY_ODD
            elif(strParity=="EVEN"):
                self.ser.parity = serial.PARITY_EVEN
            elif(strParity=="MARK"):
                self.ser.parity = serial.PARITY_MARK
            elif(strParity=="SPACE"):
                self.ser.parity = serial.PARITY_SPACE
                
            strStopbits = self.Stopbits.get()
            if (strStopbits == "1"):
                self.ser.stopbits = serial.STOPBITS_ONE
            elif (strStopbits == "1.5"):
                self.ser.stopbits = serial.STOPBITS_ONE_POINT_FIVE
            elif (strStopbits == "2"):
                self.ser.stopbits = serial.STOPBITS_TWO
            
            try:
                self.ser.open()
            except:
                infromStr = "Can't open "+self.ser.port
                InformWindow(infromStr)
            
            if (self.ser.isOpen()): # open success
                self.buttonSS["text"] = "Stop"
                self.uartState = True

    def processButtonSend(self):
        if (self.uartState):
            strToSend = self.InputText.get(1.0,tk.END)
            bytesToSend = strToSend[0:-1].encode(encoding='ascii')
            self.ser.write(bytesToSend)
            print(bytesToSend)
        else:
            infromStr = "Not In Connect!"
            InformWindow(infromStr)
                   

    def ReadUART(self):
        # print("Threading...")
        while True:
            if (self.uartState):
                try:
                    ch = self.ser.read().decode(encoding='ascii')
                    print(ch,end='')
                    self.OutputText.insert(tk.END,ch)
                except:
                    infromStr = "Something wrong in receiving."
                    InformWindow(infromStr)
                    self.ser.close() # close the serial when catch exception
                    self.buttonSS["text"] = "Start"
                    self.uartState = False
                    

mainGUI()