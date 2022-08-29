import matplotlib.pyplot as plt
import numpy as np
import time
import math

t_now = 0
m = [sin(t_now)]

def ImprovedMethod_Improve(point):    
    es_time = np.zeros([point]) 
    fig=plt.figure()
    ax=fig.add_subplot(1,1,1)

    ax.set_xlabel('Horizontal Position')
    ax.set_ylabel('Vertical Position')
    ax.set_title('Vessel trajectory')
    
    line = ax.plot([0,0],[4000,4000],'-g',marker='*')[0]
    plt.grid(True) #添加网格
    plt.ion()  #interactive mode on
    IniObsX=0000
    IniObsY=4000
    IniObsAngle=135
    IniObsSpeed=10*math.sqrt(2)   #米/秒
    print('开始仿真')
    obsX = [0,]
    obsY = [4000,]
    for t in range(point):
        t0 = time.time()
        #障碍物船只轨迹
        obsX.append(IniObsX+IniObsSpeed*math.sin(IniObsAngle/180*math.pi)*t)
        obsY.append(IniObsY+IniObsSpeed*math.cos(IniObsAngle/180*math.pi)*t)
        
        line.set_xdata(obsX)
        line.set_ydata(obsY)
        ax.set_xlim([-200,10*point+200])
        ax.set_ylim([3800-10*point,4200])
        #下面的图,两船的距离
        plt.pause(0.001)
        es_time[t] = 1000*(time.time() - t0)
    return es_time
