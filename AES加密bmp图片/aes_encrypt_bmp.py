#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
@project: AES加密bmp图片
@file: aes_encrypt_bmp.py
@ide: PyCharm
@time: 2019-03-05 18:49:57
@author: Mr.Li
Copyright © 2019—2019 Mr.Li. All rights reserved.
"""
"""
1、此程序只适用于bmp格式图片的加密，不适用于其他格式的图片
2、密钥已经写在程序里面，若需更改需要增加读取输入密钥部分或直接在程序中修改
3、未解决图片解密后 去除加密时尾部添加的0
"""

from Crypto.Cipher import AES
from binascii import b2a_hex, a2b_hex
from Crypto import Random

global head_data
global body_data
global file_name
global flag    #选择的模式的标记，顺便用于输出文件的命名

#图片分解部分
def split_bmp():
    global head_data
    global body_data
    global file_name
    file_name = 'p1'
    with open(file_name + '.bmp', 'rb') as fp1:
        temp = fp1.read()
    fp1.close()
    #获取头长度
    head_long = 0
    for i in range(10, 13):
        head_long += pow(16, (i - 10) * 2) * int(b2a_hex(temp[i]), 16)
        #temp为str型，故先用b2a_hex()转为二进制数据，再转为整型
    print 'head_long: ', head_long
    head_data = temp[0:head_long]
    body_data = temp[head_long:len(temp)]

#AES加密部分
class prpcrypt():
    def __init__(self, key):
        global flag
        self.key = key
        print '请选择加密模式：\n1、电话本（ECB）\n2、密码反馈（CFB）\n3、密码分组链接（CBC）\n4、输出反馈（OFB）'
        flag = 0
        while flag == 0:
            n = raw_input()
            if n == '1':
                self.mode = AES.MODE_ECB
                flag = '_ECB'
            elif n == '2':
                self.mode = AES.MODE_CFB
                flag = '_CFB'
            elif n == '3':
                self.mode = AES.MODE_CBC
                flag = '_CBC'
            elif n == '4':
                self.mode = AES.MODE_OFB
                flag = '_OFB'
            else:
                print "输入错误，请重新输入："

    #加密函数，并补足text为16的倍数
    def encrypt(self, text):
        iv = '\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0'
        cryptor = AES.new(self.key, self.mode, iv)
        length = 16
        count = len(text)
        if(count % length != 0):
            add = length - (count % length)
        else:
            add = 0
        text = text + ('\0' * add)
        #text = text + (str(add) * add)    #差几个就填补数字几，方便去除填补的数字
        self.ciphertext = cryptor.encrypt(text)
        return b2a_hex(self.ciphertext)

    '''
    #解密函数，填补的空用strip()去掉
    def decrypt(self, text):
        cryptor = AES.new(self.key, self.mode, self.key)
        plain_text = cryptor.decrypt(a2b_hex(text))
        return plain_text
        #return plain_text.rstrip('\0')
    '''

if __name__ == '__main__':
    #global flag
    split_bmp()
    pc = prpcrypt('keyskeyskeyskeys')    #设置密钥为keyskeyskeyskeys

    e = pc.encrypt(body_data)
    endata = head_data+e
    with open(file_name + flag + '.bmp', 'wb') as fp2:
        fp2.write(endata)
    fp2.close()
    '''
    d = pc.decrypt(e)
    dedata = head_data + d
    with open(file_name + '_dec.bmp', 'wb') as fp3:
        fp3.write(dedata)
    fp3.close()
    '''
