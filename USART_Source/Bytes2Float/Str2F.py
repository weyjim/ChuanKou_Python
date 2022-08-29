#正则表达式提取浮点数
import re
string="PWM=234.433,angle=23.423"
floats=re.findall(r"\d+\.?\d*",string)
print(floats)

type(floats[0])

PWM=float(floats[0])        #提取后转换为浮点型

type(PWM)
print(PWM)
