#!/usr/bin/python3
# -*- coding: UTF-8 -*-

import chardet

def getcharencode(f_input):
	f = open(f_input,'rb')
	content = f.read()
	fencoding=chardet.detect(content)
	#print(fencoding)
	f.close()
	return fencoding


if __name__=='__main__':
	getcharencode('base\\test.py')
	getcharencode('base\\test.txt')
	getcharencode('base\\BCompare.exe')

