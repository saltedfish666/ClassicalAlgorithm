#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
@project: n后问题（回溯法）
@file: nqueen_bt.py
@ide: PyCharm
@time: 2018-12-21 15:30:07
@author: Mr.Li
Copyright © 2018—2018 Mr.Li. All rights reserved.
"""

#只输出解的个数而不输出所有解，速度会快很多，输出结果很耗时间

import time

n = int(raw_input("please input the number of queen:"))
sum = 0
x = [i for i in range(n)]
y = [0 for i in range(n+1)]    #记录被占用的列
y1 = [0 for i in range(2*n+1)]
y2 = [0 for i in range(2*n)]    #记录被占用的斜线

def place(k):
    for j in range(1,k):
        if abs(k-j) == abs(x[j-1]-x[k-1]) or x[j-1] == x[k-1]:
            return 0
    return 1

def backtrack(t):
    global sum
    if t > n:
        sum += 1
        print x
    else:
        for i in range(1,n+1):
            x[t-1] = i
            if place(t):
                backtrack(t+1)

def bt_v2(t):
    global sum
    if t > n:
        sum += 1
        print x
    else:
        for i in range(1,n+1):
            if y[i] == 0 and y1[t + i] == 0 and y2[t - i + n] == 0:
                x[t - 1] = i
                y[i] = 1
                y1[t + i] = 1
                y2[t - i + n] = 1
                bt_v2(t+1)
                y[i] = 0
                y1[t + i] = 0
                y2[t - i + n] = 0

def bt_v3_0(t):
    global sum
    if t > n:
        sum += 2
        print x
        x_2 = [(n + 1 - a) for a in x]
        print x_2
    else:
        for i in range(1,n+1):
            if y[i] == 0 and y1[t + i] == 0 and y2[t - i + n] == 0:
                x[t - 1] = i
                y[i] = 1
                y1[t + i] = 1
                y2[t - i + n] = 1
                bt_v3_0(t+1)
                y[i] = 0
                y1[t + i] = 0
                y2[t - i + n] = 0

def bt_v3():
    global sum
    for i in range(1,n/2+1):
        x[0] = i
        y[i] = 1
        y1[1 + i] = 1
        y2[1 - i + n] = 1
        bt_v3_0(2)
        y[i] = 0
        y1[1 + i] = 0
        y2[1 - i + n] = 0
    if n % 2 == 1:
        x[0] = n/2+1
        y[n/2+1] = 1
        y1[n/2 + 2] = 1
        y2[n/2 + 1] = 1
        bt_v2(2)
        y[n/2+1] = 0
        y1[n/2 + 2] = 0
        y2[n/2 + 1] = 0

if __name__ == '__main__':
    start = time.clock()
    #backtrack(1)
    #bt_v2(1)
    bt_v3()
    end = time.clock()
    print sum
    print('Running time: %s Seconds' % (end - start))