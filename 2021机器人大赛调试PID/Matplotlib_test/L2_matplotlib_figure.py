import matplotlib.pyplot as plt     
import numpy as np

x = np.linspace(-1 , 10 , 50)    
y1 = 2*x + 1
y2 = x**2

plt.figure()            #每个figue对应一个窗口
plt.plot(x , y1)

plt.figure(num=3 , figsize=(8,5))   #标号与窗口大小
plt.plot(x , y2)                    #颜色，线宽，'--'为虚线
plt.plot(x , y1 , color='red' , linewidth=2.3 , linestyle='--')

plt.show()
