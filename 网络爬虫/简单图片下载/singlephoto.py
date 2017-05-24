'''
1.Sample Python 3.x
'''
# -*- coding: UTF-8 -*-
import spider
import os

'''
Save one picture from a picture url
'''
class SinglePhoto:
	def __init__(self, retryTimes=5, decodeCode="gbk", timeOut=5):
		self.url = ""
		self.distPath = "."
		self.spider = spider.Spider(retryTimes,decodeCode,timeOut)

	def setUrl(self, picurl):
		self.url = picurl

	def setUrlAndPath(self, picurl, path):
		self.url = picurl
		self.distPath = path

	def mkdir(self,path):
		path = path.strip()
		isExists=os.path.exists(path)
		if not isExists:
			os.makedirs(path)
			return True
		else:
			return False

	def saveImg(self,imageURL,fileName):
		print(imageURL)
		print(fileName)
		data = self.spider.getResponseData(imageURL)
		f = open(fileName, 'wb')
		f.write(data)
		f.close()

	def startDownload(self):
		strlist = self.url.split("/")
		filename = strlist[-1]
		self.saveImg(self.url, filename)

'''
2.Reference
'''












'''
3.Extension

'''
