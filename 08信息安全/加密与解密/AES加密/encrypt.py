#!/usr/bin/python3
# -*- coding: UTF-8 -*-
import myAES
import os
import time
import base64
import chardet

_distDir = '.\\base'
_encoding = 'utf8'

def detectEncode(filename):
	file = open(filename, "rb")#要有"rb"，如果没有这个的话，默认使用gbk读文件。          
	buf = file.read()
	result = chardet.detect(buf)
	return result["encoding"]

def loadFromLoacl(filename):
	global _encoding
	
	_encoding = detectEncode(filename)
	try:
		f = open(filename, "r", encoding=_encoding)
		data = f.read()
		f.close()
	except:
		print("Failed to load file: " + filename + ". Please create password.txt")
		return ""
	else:
		return data

def saveToLocal(filename, data):
	try:
		f = open(filename, "w")
		f.write(data)
		f.close()
	except:
		print("Failed to save file: " + filename)

def getPassword():
	password = loadFromLoacl('password.txt')
	if len(password)==16 or len(password)==24 or len(password)==32:
		return password
	else:
		return ""

def encryptByBase64(str):
	global _encoding
	
	return base64.b64encode(str.encode(_encoding)).decode('ascii')

if __name__ == '__main__':
	

	myaes = myAES.AEScrypt(getPassword())

	for root, dirs, files in os.walk(_distDir, topdown=False):
		for name in files:
			try:
				filename = os.path.join(root, name)
				d = loadFromLoacl(filename)
				de = encryptByBase64(d)
				e = myaes.encrypt(de)
				saveToLocal(filename, e)
			except Exception as e:
				print("Failed to encrypt file: " + filename + ". Please input the correct password, the length of password should be 16, 24 or 32")
				print(e)
			else:
				print("Encrypt success! File: " + filename)
	
	