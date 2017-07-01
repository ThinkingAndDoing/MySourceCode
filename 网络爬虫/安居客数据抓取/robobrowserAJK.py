#!/usr/bin/python3
# -*- coding: UTF-8 -*-

'''
http://www.cnblogs.com/nbkhic/p/4216115.html
http://blog.csdn.net/abclixu123/article/details/38502993
'''
import re
import os
from robobrowser import RoboBrowser


FileName = 'out.txt'

def getUrlList():
	urllist = []
	urllist.append('https://nanjing.anjuke.com/sale/?from=navigation')
	for i in range(2, 10000):
		urllist.append('https://nanjing.anjuke.com/sale/p' + str(i) + '/#filtersort')
	return urllist

def readList(urllist):
	user_agent = 'Mozilla/5.0 (Windows NT 10.0; WOW64; rv:47.0) Gecko/20100101 Firefox/47.0'
	b = RoboBrowser(history=True, user_agent=user_agent, parser='html.parser')
	
	for url in urllist:
		b.open(url)
		print(url)
		content = b.find_all('li', class_='list-item')
		if content==[]:
			print('Failed to get html tag.')
			return
		f = open(FileName, "a", encoding='utf-8')
		for item in content:
			f.write(str(item))
		f.close()

if __name__ == "__main__":
	try:
		if os.path.isfile(FileName):
			os.remove(FileName)
		readList(getUrlList())
	except Exception as e:
		print(e)




	

	