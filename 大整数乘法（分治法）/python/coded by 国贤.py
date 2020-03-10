#!/usr/bin/env python 
#coding=utf-8
import math
 
# 计算符号
def sign(x):
    if x<0:
        return -1
    else:
        return 1
    
def divideConquer(x, y, n):
    s = sign(x)*sign(y)
    x = abs(x) #绝对值函数
    y = abs(y)
 
    if x==0 or y==0:    # 如果其中有一个为0 直接返回0
        return 0
    elif n==1 :     # 递归结束条件 n=1
        return x*y*s
    else:
        A = x // math.pow(10, n//2)    # 获得第一个数的前半部分
        B = x - A*math.pow(10, n//2)   # 获得第一个数的后半部分
        C = y // math.pow(10, n//2)    # 获得第二个数的前半部分
        D = y - C*math.pow(10, n//2)   # 获得第二个数的后半部分
        AC = divideConquer(A, C, n-n//2)    # AC相乘的结果
        BD = divideConquer(B, D, n//2)    # BD相乘的结果
        ABCD = divideConquer(A-B, D-C, n-n//2)+AC +BD    
		# 计算中间量AD+BC的结果 实际的计算方式是(a-b)(d-c)+ac+db
        return s * (AC*math.pow(10, (n//2+n//2))+ABCD*math.pow(10, n//2)+BD)

def divideConquer_1(x, y,n,m):
    s = sign(x)*sign(y)
    x = abs(x) #绝对值函数
    y = abs(y)
 
    if x==0 or y==0:    # 如果其中有一个为0 直接返回0
        return 0
    elif n==1 or m==1:     # 递归结束条件 n=1
        return x*y*s
    else:
        A = x // math.pow(10, n//2)    # 获得第一个数的前半部分
        B = x - A*math.pow(10, n//2)   # 获得第一个数的后半部分
        C = y // math.pow(10, m//2)    # 获得第二个数的前半部分
        D = y - C*math.pow(10, m//2)   # 获得第二个数的后半部分
        AC = divideConquer_1(A, C, n-n//2,m-m//2)    # AC相乘的结果
        BD = divideConquer_1(B, D, n//2,m//2)    # BD相乘的结果
        ABCD = divideConquer_1(A*math.pow(10, n//2)-B, D-C*math.pow(10, m//2), n-n//2,m-m//2)
		# 计算中间量AD+BC的结果 实际的计算方式是(a-b)(d-c)+ac+db
        return s * (2*AC*math.pow(10,(n//2+m//2))+ABCD+2*BD)
if __name__ =='__main__':
	x = input('Please input the multiplicand:')#multiplicand > multiplier
	y = input('Please input the multiplier:')
	n = len(str(x))
	m = len(str(y))
	if m==n:
		print(int(divideConquer(x,y,n)))
	else:
		print(int(divideConquer_1(x,y,n,m)))