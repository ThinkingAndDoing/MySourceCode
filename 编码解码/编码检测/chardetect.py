#!/usr/bin/python3
# -*- coding: UTF-8 -*-

import chardet

def getcharencode(filename):
	file = open(filename, "rb")#要有"rb"，如果没有这个的话，默认使用gbk读文件。          
	buf = file.read()
	file.close()
	result = chardet.detect(buf)
	return result["encoding"]

if __name__=='__main__':
	getcharencode('base\\test.py')
	getcharencode('base\\test.txt')
	getcharencode('base\\BCompare.exe')

