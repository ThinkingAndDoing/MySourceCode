#!/usr/bin/python3
# -*- coding: UTF-8 -*-
import myAES
import os

_distDir = '.\\base'

def loadFromLoacl(filename):
	f = open(filename, "r")
	data = f.read()
	f.close()
	return data

def saveToLocal(filename, data):
	f = open(filename, "w")
	f.write(data)
	f.close()


if __name__ == '__main__':

	myaes = myAES.AEScrypt()

	for root, dirs, files in os.walk(_distDir, topdown=False):
		for name in files:
			try:
				filename = os.path.join(root, name)
				if filename.rfind('_encrypted')!=-1:
					e = loadFromLoacl(filename)
					d = myaes.decrypt(e)
					saveToLocal(filename[:-10], d)
					os.remove(filename)
			except Exception as e:
				continue
	
	
	