#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
@project: RSA通讯加密
@file: RSA_A.py
@ide: PyCharm
@time: 2019-03-25 21:00:39
@author: Mr.Li
Copyright © 2019—2019 Mr.Li. All rights reserved.
"""

import rsa
from socket import *
import random

def IM_client():
    s = socket(AF_INET, SOCK_DGRAM)
    data = '1'
    s.sendto(data, ('127.0.0.1', 8000))
    pub, addr = s.recvfrom(1024)
    publicKey = rsa.PublicKey.load_pkcs1(pub)
    print "Receive publicKey successful"
    #生成明文字符串
    message = ''.join(random.sample('zyxwvutsrqponmlkjihgfedcba', 16))
    print "message: ", message
    encrypt_message = rsa.encrypt(message, publicKey)
    print "Encrypt message successful"
    s.sendto(encrypt_message, ('127.0.0.1', 8000))

if __name__ == '__main__':
    IM_client()
    raw_input()