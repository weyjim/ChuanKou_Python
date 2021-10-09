import matplotlib.pyplot as plt     #文件名不可以是matplotlib
import numpy as np

x = np.linspace(-1,10,50)    #(左上限，右上限，采样率)
#y = 2*x+1
y = x**2
plt.plot(x,y)       #(横坐标，纵坐标)
plt.show()
