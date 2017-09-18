#!/usr/bin/python3
# -*- coding: UTF-8 -*-

import os

_List1 = 'list1.txt'
_List2 = 'list2.txt'
_List = 'list.txt'

def getUrlList(fn):
	f = open(fn, 'r', encoding='utf-8')
	list = f.read().split('\n')
	f.close()
	return list

def writeListToFile(file, list):
	f = open(file, "w+", encoding='utf-8')
	for item in list:
		f.write(str(item)+"\n")
	f.close()

if __name__ == "__main__":
	list1 = getUrlList(_List1)
	list2 = getUrlList(_List2)
	list = list1 + list2
	while '' in list:
		list.remove('')
	print(list)
	writeListToFile(_List, list)




	

	
