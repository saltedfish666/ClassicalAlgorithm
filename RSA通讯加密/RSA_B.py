#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
@project: RSA通讯加密
@file: RSA_B.py
@ide: PyCharm
@time: 2019-03-25 21:01:44
@author: Mr.Li
Copyright © 2019—2019 Mr.Li. All rights reserved.
"""

import rsa
from socket import *

def CA_client():
    global pub
    global privateKey
    s = socket(AF_INET, SOCK_STREAM)
    try:
        s.connect(('127.0.0.1', 7777))
    except BaseException:
        exit("Error: Connect with CA fail")
    else:
        print "Connect with CA successful"
    n = '1024'
    s.send(n)
    pub = s.recv(1024)
    #publicKey = rsa.PublicKey.load_pkcs1(pub)
    pri = s.recv(1024)
    privateKey = rsa.PrivateKey.load_pkcs1(pri)
    print "Receive CA successful"
    s.close()

def IM_server():    #Instant Messaging
    s = socket(AF_INET, SOCK_DGRAM)
    s.bind(('127.0.0.1', 8000))
    while 1:
        data, addr = s.recvfrom(1024)
        s.sendto(pub, addr)
        print "Send publicKey successful"
        message, addr = s.recvfrom(1024)
        decrypt_message = rsa.decrypt(message, privateKey)
        print "Message: ", decrypt_message

if __name__ == '__main__':
    CA_client()
    IM_server()
