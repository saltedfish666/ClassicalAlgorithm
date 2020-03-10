#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
@project: Hash谜题
@file: hash谜题.py
@ide: PyCharm
@time: 2019-04-08 18:12:44
@author: Mr.Li
Copyright © 2019—2019 Mr.Li. All rights reserved.
"""

import hashlib
import time

def HASH(data):
    sha1 = hashlib.sha1()
    sha1.update(data)
    return sha1.hexdigest()

def SHR(h, k):
    return h >> k*4

if __name__ == '__main__':
    for d in range(6):
        start = time.time()
        n = SHR(pow(2, 160)-1, d+1)
        v = "1615300027"
        x = 1
        while True:
            data = v + str(x)
            if int(HASH(data), 16) <= n:
                print "d的值为", d+1, "时，x的值为:",x
                print "哈希值为:",HASH(data)
                break
            x += 1
        end = time.time()
        print "Running time: " + str(end - start)