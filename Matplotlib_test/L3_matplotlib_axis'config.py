import matplotlib.pyplot as plt     
import numpy as np

x = np.linspace(-3, 3, 50)    
y1 = 2*x + 1
y2 = x**2

plt.figure()   
plt.plot(x, y2)                    
plt.plot(x, y1, color='red', linewidth=2.3, linestyle='--')

plt.xlim((-1, 2))        #默认视图里x，y的展示范围
plt.ylim((-2, 3))

plt.xlabel('Time')      #xy轴侧边标签
plt.ylabel('Value')

new_ticks = np.linspace(-1, 2, 5)       
print(new_ticks)
plt.xticks(new_ticks)       #将newticks设为x取值
plt.yticks([-2, -1.8, -1, 1.22, 3],     #直接指定y取值
           ['really bad', 'bad', 'nomal alpha', 'good', r'$really\ good\ \alpha$'])
            #按列表序号一一对应，可用正则r''

'''
以下改变坐标原点和坐标轴在视图里的位置，目的是转换成方便的数学坐标系
'''

ax = plt.gca()      #gca:"get current axis"

#为了显示横竖坐标轴出现在视图中心，屏蔽掉四个边框中的两个
ax.spines['right'].set_color('none')        #隐藏右边框
ax.spines['top'].set_color('none')          #隐藏上边框

#由于默认轴是随机四个边去两个，这里要指定以哪个线为标准xy轴
ax.xaxis.set_ticks_position('bottom')
ax.yaxis.set_ticks_position('left')

#更改两条spine的位置
ax.spines['bottom'].set_position(('data', 0))       #(通过数据方式改变，数据)
ax.spines['left'].set_position(('data', 0))         #其他方式：outward，axes






plt.show()
