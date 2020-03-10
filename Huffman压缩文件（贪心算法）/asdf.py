# -*- coding:utf-8 -*-

class Node:
    def __init__(self):
        self.value = ''
        self.left = None
        self.right = None
        self.f = 0
        self.code = ''
		

a=Node()
a.value='qwe'
a.f=9
b=Node()
b.value='asd'
b.f=7
c=Node()
c.value='zxc'
c.f=8
nlist=[]
nlist.append(a)
nlist.append(b)
nlist.append(c)

print nlist[0].value,nlist[0].f
print nlist[1].value,nlist[1].f
print nlist[2].value,nlist[2].f

#nlist.sort(cmp=lambda x,y:cmp(x.f,y.f))

#nlist.sort(cmp=1)

nlist.sort(key=lambda x:x.f)

print nlist[0].value,nlist[0].f
print nlist[1].value,nlist[1].f
print nlist[2].value,nlist[2].f