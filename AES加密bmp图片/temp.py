#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
@project: AES加密bmp图片
@file: temp.py
@ide: PyCharm
@time: 2019-03-06 11:05:23
@author: Mr.Li
Copyright © 2019—2019 Mr.Li. All rights reserved.
"""
'''
此文件仅用于尝试十六进制转整型的代码
'''

from binascii import b2a_hex

with open('google.bmp', 'rb') as fp:
    temp = fp.read();
fp.close()

head_long = 0
for i in range(10, 13):
    head_long += pow(16, (i - 10) * 2) * int(b2a_hex(temp[i]), 16)
    #temp为str型，故先用b2a_hex()转为二进制数据，再转为整型

head_data = temp[0:head_long]
body_data = temp[head_long:len(temp)]

print len(body_data)