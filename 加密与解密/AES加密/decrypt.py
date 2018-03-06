#!/usr/bin/python3
# -*- coding: UTF-8 -*-
import myAES
import os
import time
import base64
import chardet

_distDir = '.\\base'
_encoding = 'utf8'

def loadFromLoacl(filename):
	try:
		f = open(filename, "r")
		data = f.read()
		f.close()
	except:
		print("Failed to load file: " + filename + ". Please create password.txt")
		return ""
	else:
		return data

def saveToLocal(filename, data):
	global _encoding
	
	try:
		f = open(filename, "w", encoding=_encoding)
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

def decryptByBase64(str):
	global _encoding
	
	data = base64.b64decode(str.encode('ascii'))
	result = chardet.detect(data)
	_encoding = result["encoding"]
	return data.decode(_encoding)


if __name__ == '__main__':

	myaes = myAES.AEScrypt(getPassword())

	for root, dirs, files in os.walk(_distDir, topdown=False):
		for name in files:
			try:
				filename = os.path.join(root, name)
				e = loadFromLoacl(filename)
				d = myaes.decrypt(e)
				ed = decryptByBase64(d)
				saveToLocal(filename, ed)
			except Exception as e:
				print("Password error! Failed to decrypt file: " + filename + ". The length of password should be 16, 24 or 32")
				print(e)
			else:
				print("Decrypt success! File: " + filename)
	
