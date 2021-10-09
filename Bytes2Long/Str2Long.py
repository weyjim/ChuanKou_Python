str='pwm=123.543'
data=float(str[4:])
print(data)

Bytes_Str = 'PWM=26.2387'

i=0
count=0

str = "h3110 23 cat 444.4 rabbit 11 2 dog"
[int(s) for s in str.split() if s.isdigit()]


import re
s = 'speed=210.65,angle=150'
m = re.findall(r'(\w*[0-9]+)\w*',s)
print(m)
