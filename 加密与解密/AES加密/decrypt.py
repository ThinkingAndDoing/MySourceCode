#!/usr/bin/python3
# -*- coding: UTF-8 -*-
import myAES
import os
import time
import base64

_distDir = '.\\base'

def loadFromLoacl(filename):
	try:
		f = open(filename, "r", encoding='utf8')
		data = f.read()
		f.close()
	except:
		print("Failed to load file: " + filename + ". Please create password.txt")
		return ""
	else:
		return data

def saveToLocal(filename, data):
	try:
		f = open(filename, "w", encoding='utf8')
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
	return base64.b64decode(str.encode('utf-8')).decode('utf-8')


if __name__ == '__main__':

	myaes = myAES.AEScrypt(getPassword())

	for root, dirs, files in os.walk(_distDir, topdown=False):
		for name in files:
			try:
				filename = os.path.join(root, name)
				if filename.rfind('_encrypted')!=-1:
					e = loadFromLoacl(filename)
					d = myaes.decrypt(e)
					ed = decryptByBase64(d)
					saveToLocal(filename[:-10], ed)
					os.remove(filename)
			except:
				print("Password error! Failed to decrypt file: " + filename + ". The length of password should be 16, 24 or 32")
			else:
				print("Decrypt success! File: " + filename)
	time.sleep(0.5)
	