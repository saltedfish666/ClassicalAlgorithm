#!/usr/bin/env python
# -*- coding: utf-8 -*-

def loading(w,n,c):
	num=0    #统计排序后入选物品的个数
	b=zip(w,range(n))
	b.sort(key=lambda x:x[0])
	wi=[x[0] for x in b]    #wi为排好序的物品列表
	d=[x[1] for x in b]    #d为wi元素对应的下标
	for i in range(n):    #实行贪心算法
		if wi[i]<=c:
			num+=1
			c-=wi[i]
	d=d[:num]    #将未入选物品的下标丢掉
	d.sort()    #入选物品的下标排序
	print 'item:'
	for i in range(num):
		print 'NO.',d[i]+1

if __name__=='__main__':
	path=raw_input('please input the path:')
	with open(path,'r') as f:
		temp=f.readlines()
	for i in range(len(temp)):
		temp[i]=temp[i].rstrip('\n')
	c=int(temp[0])
	w=map(int,temp[1].split(' '))
	n=len(w)
	
	loading(w,n,c)