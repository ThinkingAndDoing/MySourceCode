'''
1.例子源代码 Python 3.x
'''
# -*- coding: UTF-8 -*-
import urllib.request
import re
import sys
import socket
import os
import xlwt
import time
from urllib.parse import quote

#basic class
class Spider:
	def __init__(self, retryTimes=5, decodeCode="gbk", timeOut=5):
		self.timesOfRetry = retryTimes
		self.targetCodeFormat = decodeCode
		socket.setdefaulttimeout(timeOut)

	def encodeUrl(self, url):
		try:
			return quote(url, safe='/:?=')
		except Exception as e:
			print(Exception,"in encodeUrl:",e)

	#get response data from http request
	def getResponseData(self,url):
		url = self.encodeUrl(url)
		attempts = 0
		success = False
		data = b"0"
		while attempts < self.timesOfRetry and not success:
			try:
				headers = { 'User-Agent' : 'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/54.0.2837.0 Safari/537.36' }
				req = urllib.request.Request(url, headers = headers)
				data = urllib.request.urlopen(req).read()
				success = True
			except Exception as e:
				print(Exception,"in getResponseData:",e)
				attempts += 1
		return data

	#get decoded response data
	def getDecodeResponseData(self,url):
		try:
			data = self.getResponseData(url)
			dataDecode=data.decode(self.targetCodeFormat)
			return dataDecode
		except Exception as e:
			print(Exception,"in getDecodeResponseData:",e)

class AnJuKe:
	def __init__(self):
		self.spider = Spider(5, "utf-8", 5)
		self.nextPage = ""
		self.list = []
	  
	def writeTable(self, content):
		print("writeTable")
		workbook = xlwt.Workbook() #注意Workbook的开头W要大写
		sheet1 = workbook.add_sheet('sheet1',cell_overwrite_ok=True)
		row = 0
		for i in content:
			col = 0
			for j in i:
				sheet1.write(row, col, ''.join(list(j)))
				col = col + 1
			row = row + 1
		timeTag = time.strftime('(%Y%m%d)%H-%M-%S',time.localtime(time.time()))
		workbook.save(timeTag+'OutputExcel.xls')

	def saveDataOfOnePage(self, url):
		print(url)
		data = self.getDataOfOnePage(url)
		for i in data:
			print(i[1])
			page = self.spider.getDecodeResponseData(i[1])
			f = open("text.txt","w",encoding='utf-8')
			f.write(page)
			pattern = re.compile('<dl><dt>面积：</dt><dd>(.*?)</dd></dl>.*?<dl><dt>房屋单价：</dt><dd>(.*?)</dd></dl>.*?<em class="houseTitle">(.*?)</em>',re.S)
			items = re.findall(pattern,page)
			if items !=[]:
				self.list.append([items[0][0], items[0][1], items[0][2]])
			#print(items)
      
		if self.nextPage!="":
			self.saveDataOfOnePage(self.nextPage)

	def getDataOfOnePage(self,url):
		page = self.spider.getDecodeResponseData(url)
		pattern = re.compile('<a href="([^\"]*?)" class="aNxt">下一页 &gt;</a>',re.S)
		items = re.findall(pattern,page)
		if items==[]:
			print("No more pages!")
			self.writeTable(self.list)
			sys.exit(0)
		self.nextPage = items[0]
		pattern = re.compile('<a data-from="" data-company=""  title="([^\"]*?)" href="([^\"]*?)"',re.S)
		items = re.findall(pattern,page)
		contents = []
		for item in items:
			contents.append([item[0],item[1]])
		return contents

	def saveOneImg(self, imageURL, imgName):
		data = self.getResponseData(imageURL)
		f = open(imgName, 'wb')
		f.write(data)
		f.close()

c = AnJuKe()
url = "http://nanjing.anjuke.com/sale/?from=navigation"
url = "http://nanjing.anjuke.com/sale/p6/#"
c.saveDataOfOnePage(url)
c.writeTable(c.list)


'''
2.相关知识点
'''












'''
3.扩展
'''

