bytes_data = b'message'

#str_data = str(bytes_data, encoding = 'utf-8')

str_data = bytes_data.decode('utf-8')       #两种方法均可

print(str_data)


#str 2 Bytes

str_data = 'message'
# 方法一：
bytes_data = bytes(str_data, encoding = 'utf-8')
# 方法二：
bytes_data = str_data.encode('utf-8')

