# -*- coding: utf-8 -*-

G = {1: { 2: 4, 3: 2,4:5},
	2: { 5: 7, 6: 5},
	3: {6: 9},
	4: {5: 2, 7: 7},
	5: {8: 4},
	6: {10:6},
	7: {9: 3},
	8: {10:7},
	9: {10:8},
	10:{}}
inf=9999
length=[0,inf,inf,inf,inf,inf,inf,inf,inf,inf]    #源点到各点的距离
q=[]    #扩展节点集合
prev=[0 for i in range(10)]    #记录到目前结点的最短路径的上一结点
path=[]

#FIFO分支限界法
def branch_FIFO(G,v0):    #v0为源点
	q.append(v0)
	while len(q)!=0:
		dict=G[q[0]]
		head=q[0]
		for key in dict:
			if length[head-1]+G[head][key]<length[key-1]:
				length[key-1]=length[head-1]+G[head][key]
				q.append(key)
				prev[key-1]=head
		del q[0]

#优先队列式分支限界法
def branch_best(G,v0):
	q.append(v0)
	while len(q)!=0:
		min=q[0]
		for i in q:
			if length[min-1]<length[i-1]:
				min=i
		dict=G[min]
		for key in dict:
			if length[min-1]+G[min][key]<length[key-1]:
				length[key-1]=length[min-1]+G[min][key]
				q.append(key)
		q.remove(min)

if __name__ == '__main__':
	branch_FIFO(G,1)
	#branch_best(G,1)
	print(length)
	print(prev)
	t=10
	path.append(t)
	while prev[t-1]:
		if prev[t-1]!=0:
			path.append(prev[t-1])
			t=prev[t-1]
	p=list(reversed(path))
	print p




