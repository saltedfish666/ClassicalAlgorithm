#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
@project: Hash谜题
@file: temp.py
@ide: PyCharm
@time: 2019-04-08 21:10:37
@author: Mr.Li
Copyright © 2019—2019 Mr.Li. All rights reserved.
"""

import hashlib
from binascii import a2b_hex, b2a_hex

def HASH(data):
    sha1 = hashlib.sha1()
    sha1.update(data)
    return sha1.hexdigest()

a = HASH("161530002710917762")

print a
