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

def encryptByBase64(str):
	return base64.b64encode(str.encode('utf-8')).decode('utf-8')

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
	
	time.sleep(0.5)
	