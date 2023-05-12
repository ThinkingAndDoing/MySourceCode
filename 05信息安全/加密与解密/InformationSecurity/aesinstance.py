#!/usr/bin/python3
# -*- coding: UTF-8 -*-
import sys
from Crypto.Cipher import AES
from binascii import b2a_hex, a2b_hex

#pycrypto‎ required instead of pycrypto‎demo(Will get error: Object type <class 'str'> cannot be passed to C code)

class AEScrypt():
	def __init__(self, key='keyskeyskeyskeyskeyskeyskeyskeys'):#初始化密钥
		self.key = key
		self.mode = AES.MODE_CBC
    
	def encrypt(self, text):
		cryptor = AES.new(self.key, self.mode, IV=self.key[:16]) 
		"""
		AES算法需要两个不同的参数进行加密，分别是密钥和初始化向量（IV）。
		创建密钥文件的三个选择：
		1.将硬编码的IV嵌入应用程序中，并将密钥保存在密钥文件中。
		2.将硬编码的密钥嵌入应用程序中，并将IV保存在密钥文件中。
		3.将密钥和IV保存在密钥文件中。
		这里密钥key 长度必须为16（AES-128）、24（AES-192）、或32（AES-256）Bytes 长度.目前AES-128足够用
		"""
		length = 16
		count = len(text)
		add = length - (count % length)
		#加密函数，如果text不是16的倍数【加密文本text必须为16的倍数！】，那就补足为16的倍数
		text = text + ('\0' * add)
		self.ciphertext = cryptor.encrypt(text)
		#因为AES加密时候得到的字符串不一定是ascii字符集的，输出到终端或者保存时候可能存在问题
		#所以这里统一把加密后的字符串转化为16进制字符串
		return b2a_hex(self.ciphertext).decode('utf8')
	
	def decrypt(self, text):
		cryptor = AES.new(self.key, self.mode, IV=self.key[:16])
		plain_text = cryptor.decrypt(a2b_hex(text))
		#解密后，去掉补足的空格用strip() 去掉
		return plain_text.decode('utf8').rstrip('\0')
 
if __name__ == '__main__':
	pc = AEScrypt()
	e = pc.encrypt("00000")
	d = pc.decrypt(e)
	print('*****************')
	print(e, d)
	e = pc.encrypt("11111111")
	d = pc.decrypt(e)
	print('*****************')
	print(e, d)
	
	
	