'''
1.Sample Python 3.x
'''
# -*- coding: UTF-8 -*-
import allpicsofurl
import os
from time import ctime
import threading
import logging
logging.basicConfig(level=logging.DEBUG,format='%(asctime)s %(filename)s[line:%(lineno)d] %(levelname)s %(message)s',datefmt='%a, %d %b %Y %H:%M:%S',filename='test.log',filemode='w')

def downloadList(list):
	try:
		gp = allpicsofurl.AllPicsOfUrl()
		for url in list:
			if url!="":
				gp.downloadAllPics(url)
	except Exception as e:
		print(Exception,"in downloadList:",e)

f = open("out.txt","r",encoding='utf-8')
data = f.read()
inputList = data.split("\n")
downloadList(inputList)

'''
2.Reference
'''












'''
3.Extension

'''
