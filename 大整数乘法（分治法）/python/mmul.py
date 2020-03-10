#!/usr/bin/env python
# -*- coding: utf-8 -*-

import math

def multiply(x,y,n):
	if x==0 or y==0:
		return 0
	elif n==1:
		return x*y
	else:
		a=x//math.pow(10,n//2)
		b=x-a*math.pow(10,n//2)
		c=y//math.pow(10,n//2)
		d=y-c*math.pow(10,n//2)
		ac = multiply(a,c,n-n//2)
		bd = multiply(b,d,n//2)
		abcd = multiply((a-b),(d-c),n-n//2)+ac+bd
		return (ac * math.pow(10, 2*(n//2)) + abcd * math.pow(10, n // 2) + bd)

def multiply_un(x,y,n,m):
	if x==0 or y==0:
		return 0
	elif n==1 or m==1:
		return x*y
	else:
		a=x//math.pow(10,n//2)
		b=x-a*math.pow(10,n//2)
		c=y//math.pow(10,m//2)
		d=y-c*math.pow(10,m//2)
		ac=multiply_un(a,c,n-n//2,m-m//2)
		bd=multiply_un(b,d,n//2,m//2)
		abcd=multiply_un(a*math.pow(10,n//2)-b,d-c*math.pow(10,m//2),n-n//2,m-m//2)+bd
		return (2*ac * math.pow(10, (n//2+m//2)) + abcd + bd)

if __name__=='__main__':
	n=0
	x=int(raw_input('请输入两个大整数：X='))
	y=int(raw_input('Y='))
	n = len(str(x))
	m = len(str(y))
	if m==n:
		sum = int(multiply(x,y,n))
	else:
		sum = int(multiply_un(x,y,n,m))
	print '普通乘法:X*Y=',x*y
	print '分治乘法:X*Y=',x*y