#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
@project: RSA通讯加密
@file: RSA_C.py
@ide: PyCharm
@time: 2019-03-24 12:53:23
@author: Mr.Li
Copyright © 2019—2019 Mr.Li. All rights reserved.
"""

import rsa
from socket import *

def CA_server():
    s = socket(AF_INET, SOCK_STREAM)    #建立TCP套接字
    s.bind(('127.0.0.1', 7777))
    while 1:
        s.listen(1)
        print "waiting for connection..."
        sock, addr = s.accept()
        print "Connect with", addr
        n = int(sock.recv(1024))    #密钥模数的长度为n，n由客户端的请求决定
        key = rsa.newkeys(n)
        publicKey = key[0].save_pkcs1()
        sock.send(publicKey)
        privateKey = key[1].save_pkcs1()
        sock.send(privateKey)
        print "Send successful"

if __name__ == '__main__':
    CA_server()
