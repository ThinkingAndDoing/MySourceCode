#!/usr/bin/python3
# -*- coding: UTF-8 -*-

import chardet

_encoding = 'gbk'
_filename = 'GBK.txt'

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
		f = open(filename, "w", encoding='utf8')
		f.write(data)
		f.close()
	except:
		print("Failed to save file: " + filename)

if __name__ == '__main__':

	saveToLocal(_filename, loadFromLoacl(_filename))
