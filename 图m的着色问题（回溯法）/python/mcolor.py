# -*- coding: utf-8 -*-
'''
这个程序里面每个结点的序号都做了减1处理，避免出现例如a[0][]和a[][0]全都不需要用到的现象，避免空间浪费
'''
#全局变量必须在开头声明
#每个函数如果要用到全局变量的话要在函数内再一次声明，否则按局部变量处理
global n,m,a,x,sum

#read file
def rf():
	path=raw_input('please input the file path:')
	with open(path,'r') as f:
		temp=f.readlines()
	for i in range(len(temp)):
		temp[i]=temp[i].rstrip('\n')
	global n,m,a,x,sum
	n=int(temp[0])
	m=int(temp[1])
	a=[[0 for i in range(n)] for i in range(n)]    #a阵中值为0则说明两个结点没有相接，1则说明两个结点有相连接
	#声明二维数组的时候不能用a=[[0]*n]*n处理，因为a[0][1]=1的结果就是a=[[0,1,0][0,1,0],[0,1,0]]
	for i in range(2,len(temp)):
		node=map(int,temp[i].split(' '))
		a[node[0]-1][node[1]-1]=1
		a[node[1]-1][node[0]-1]=1
	x=[-1 for i in range(n)]    #因为结点序号中有0，所以给x初始化每个数据为-1
	sum=0

#颜色冲突检查
def ok(k):
	global n,m,a,x,sum
	for j in range(n):
		if a[k][j]==1 and x[j]==x[k]:
			return 0
	return 1

#回溯算法
def backtrack(t):
	global n,m,a,x,sum
	if t>=n:
		sum+=1
		print [i+1 for i in x]    #打印时候要+1才能打印出正确的序号
	else:
		for i in range(m):
			x[t]=i
			if ok(t):
				backtrack(t+1)
			x[t]=-1    #将死节点的x[i]重置，若得出一个解则重置整个x

if __name__ == '__main__':
	global sum
	rf()
	backtrack(0)
	#增加无结果情况下的输出
	if sum>0:
		print sum,'way(s)'
	else:
		print 'there is no solution'