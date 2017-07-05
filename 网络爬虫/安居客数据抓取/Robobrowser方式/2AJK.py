#!/usr/bin/python3
# -*- coding: UTF-8 -*-

'''
http://www.cnblogs.com/nbkhic/p/4216115.html
http://blog.csdn.net/abclixu123/article/details/38502993
https://robobrowser.readthedocs.io/en/latest/api.html#module-robobrowser.browser
不支持中文编码？Fuck！
'''
import re
import os
from robobrowser import RoboBrowser

FileName = 'list.txt'
UrlListName = 'urllist.txt'

def getUrlList():
	f = open(UrlListName, 'r', encoding='utf-8')
	return f.read().split('\n')

def has_logr(tag):
	'''
	http://nj.58.com/zufang/	content = b.find_all(has_logr)
	http://zu.nanjing.fang.com/house-a0268/	content = b.find_all(class_='info rel')
	http://nj.ganji.com/fang1/	content = b.find_all(class_='f-list-item')
	'''
	return tag.has_attr('logr')

def writeListToFile(file, list):
	f = open(file, "a", encoding='utf-8')
	for item in list:
		f.write(str(item))
	f.close()

def readList(urllist):
	user_agent = 'Mozilla/5.0 (Windows NT 10.0; WOW64; rv:47.0) Gecko/20100101 Firefox/47.0'
	b = RoboBrowser(history=True, user_agent=user_agent, parser='html.parser')
	
	for url in urllist:
		if url=='':
			continue

		b.open(url)
		print(url)
		#content = b.find_all(has_logr)
		#content = b.find_all('dd', class_='info rel')
		content = b.find_all(class_='f-list-item')
		if content==[]:
			print('Failed to get html tag.')
			return
		
		writeListToFile(FileName, content)

if __name__ == "__main__":
	if os.path.isfile(FileName):
		os.remove(FileName)
	readList(getUrlList())





	

	