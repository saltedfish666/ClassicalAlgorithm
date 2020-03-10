#!/usr/bin/env python
# -*- coding: utf-8 -*-

#Knapsack
#n is the number of items,c is bag's capacity
def bag(n,c,w,v):
	m=[[0 for j in range(c+1)] for i in range(n+1)]
	for i in range(1,n+1):
		for j in range(1,c+1):
			m[i][j]=m[i-1][j]
			if j>=w[i-1] and m[i][j]<m[i-1][j-w[i-1]]+v[i-1]:
				m[i][j]=m[i-1][j-w[i-1]]+v[i-1]
	return m

#Traceback
def show(n,c,w,m):
	print 'Maximum value:',m[n][c]
	x=[0 for i in range(n)]
	j=c
	for i in reversed(range(1,n+1)):
		if m[i][j]>m[i-1][j]:
			x[i-1]=1
			j-=w[i-1]
	print 'item:'
	for i in range(n):
		if x[i]:
			print 'NO.',i+1

if __name__=='__main__':
	'''
	n=5
	c=10
	w=[2,2,6,5,4]
	v=[6,3,5,4,6]
	'''
	path=raw_input('please input the path:')
	with open(path,'r') as f:
		temp=f.readlines()
	for i in range(len(temp)):
		temp[i]=temp[i].rstrip('\n')
	n=int(temp[0])
	c=int(temp[1])
	w=map(int,temp[2].split(' '))
	v=map(int,temp[3].split(' '))
	
	m=bag(n,c,w,v)
	print m
	'''
	for i in range(n+1):    #换行打印
		print m[i]
		print '\n'
	'''
	show(n,c,w,m)
	#os.system("pause")