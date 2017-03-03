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
import xlrd
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

class GetUrlList:
	def __init__(self):
		self.spider = Spider(5, "utf-8", 5)
		self.nextPage = ""
		self.list = []

	def saveDataOfOnePage(self, url):
		data = self.getDataOfOnePage(url)
		for i in data:
			self.list.append([i[0], i[1]])

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

class AnJuKe:
	def __init__(self):
		self.spider = Spider(5, "utf-8", 5)
		self.outputList = []

	def getPages(self, urlList):
		for i in urlList:
			self.saveDataOfOnePage(i[1])

	def saveDataOfOnePage(self, url):
		rex = '<dl><dt>面积：</dt><dd>(.*?)</dd></dl>.*?<dl><dt>房屋单价：</dt><dd>(.*?)</dd></dl>.*?<em class="houseTitle">(.*?)</em>'
		data = self.getDataOfOnePage(url, rex)
		if data!=[]:
			self.outputList.append([data[0][0], data[0][1], data[0][2]])

	def getDataOfOnePage(self, url, Rex):
		page = self.spider.getDecodeResponseData(url)
		f = open("text.txt","w",encoding='utf-8')
		f.write(page)
		pattern = re.compile(Rex,re.S)
		items = re.findall(pattern,page)
		return items

def writeTable(content, fileName):
	try:
		workbook = xlwt.Workbook() #注意Workbook的开头W要大写
		sheet1 = workbook.add_sheet('sheet1',cell_overwrite_ok=True)
		row = 0
		for i in content:
			col = 0
			for j in i:
				sheet1.write(row, col, ''.join(list(j)))
				col = col + 1
			row = row + 1
		if fileName!="":
			timeTag = time.strftime('(%Y%m%d)%H-%M-%S',time.localtime(time.time()))
			fileName = timeTag+'OutputExcel.xls'
		workbook.save(fileName)
	except:
		print("Exception:",e)

def readTable(fileName):
	try:
		list = []
		sourcewb = xlrd.open_workbook(fileName)
		sourcews = sourcewb.sheet_by_name('sheet1')
		for i in range(0, sourcews.row):
			list.append([sourcews.cell(i,0).value, sourcews.cell(i,1).value])
		return list
	except:
		print("Exception:",e)

getList = GetUrlList()
url = "http://nanjing.anjuke.com/sale/?from=navigation"
url = "http://nanjing.anjuke.com/sale/p6/#"
getList.saveDataOfOnePage(url)
writeTable(getList.list, "list.xls")

urlList = readTable("list.xls")
c = AnJuKe()
c.getPages(urlList)
writeTable(c.outputList, "")


'''
2.相关知识点
'''












'''
3.扩展
'''
