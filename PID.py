class tank:

    def __init__(self, P=0.2, I=0.01, D=0.1):#初始化
        self.Kp = P
        self.Ki = I
        self.Kd = D
        self.clear()

    def clear(self):
        self.SetLevel = 0.0#期望水位
        self.PTerm = 0.0
        self.ITerm = 0.0
        self.DTerm = 0.0
        self.last_error = 0.0
        self.windup_guard = 100.0
        self.output = 0.0

    def update(self, feedback_value):
        error = self.SetLevel - feedback_value
        #比例环
        self.PTerm = self.Kp * error
        #积分环
        self.ITerm += error
        if (self.ITerm < -self.windup_guard):
            self.ITerm = -self.windup_guard
        elif (self.ITerm > self.windup_guard):
            self.ITerm = self.windup_guard
        #微分环
        delta_error = error-self.last_error
        self.DTerm = delta_error
        self.last_error = error
        #输出
        self.output = self.PTerm + (self.Ki * self.ITerm) + (self.Kd * self.DTerm)


import time
import matplotlib.pyplot as plt
import random

#实例化“水缸”类
tank1 = tank(0.5, 0.2, 0.01)
#当前水位
current_level = 20
#期望水位
tank1.SetLevel = 100
#漏水量
water_loss = 10
#用于储存水位变化的列表
levels=[20]
for i in range(100):
    #可将漏水量设置成随机变量
    water_loss = random.randint(10,15)
    tank1.update(current_level)
    #应加水量
    water_gain = tank1.output
    #更新当前水位
    current_level = current_level+water_gain-water_loss
    levels.append(current_level)
    print(current_level, time.time())
plt.plot(levels)
plt.grid(True)
print(max(levels))
plt.show()