#!/usr/bin/env python
# -*- coding: utf-8 -*-

#KSA
def rc4_init(s,key,key_len):
	j=0
	k=[0]*256
	for i in range(256):
		k[i]=key[i%key_len]
	for i in range(256):	
		j=(j+ord(k[i])+s[i])%256
		s[i],s[j]=s[j],s[i]

#PRGA
def rc4_crypt(s,data,data_len):
	i=0
	j=0
	t=0
	out=[]
	for x in range(data_len):
		i=(i+1)%256
		j=(j+s[i])%256
		s[i],s[j]=s[j],s[i]
		t=(s[i]+s[j])%256
		out.append(chr(ord(data[x])^s[t]))
	return ''.join(out)

key_str="secret"
key=list(key_str)
data_str="inmethetigersniffstherose"
data=list(data_str)
box=list(range(256))
key_len=len(key)
data_len=len(data)
print 'key:%s'%key_str
print 'data:%s'%data_str

rc4_init(box,key,key_len)
encrypt=rc4_crypt(box,data,data_len)
print 'encrypt:%s'%encrypt

encrypt_len=len(encrypt)
box=list(range(256))
rc4_init(box,key,key_len)
decipher = rc4_crypt(box,encrypt,encrypt_len)
print 'decipher:%s'%decipher