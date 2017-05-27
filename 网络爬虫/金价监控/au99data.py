# -*- coding: UTF-8 -*-
import spider
import os
import re
import time
import datetime

class AuPrice:
	def __init__(self, retryTimes=5, decodeCode="gbk", timeOut=5):
		self.startDate = "2017-05-20"
		self.endDate = "2017-06-20"
		self.history = []
		self.currentPrice = 100
		self.spider = spider.Spider(retryTimes,decodeCode,timeOut)

	def setStartDate(self, time):
		self.startDate = time

	def setEndDate(self, time):
		self.endDate = time

	def getHistoryUrl(self, num):
		return "http://vip.stock.finance.sina.com.cn/q/view/vGold_History.php?page="+str(num)+"&breed=AU9999&start="+self.startDate+"&end="+self.endDate+"&jys=0&pz=6&name=Au99.99"

	def getCurrentPriceUrl(self):
		return ""

	def run(self):
		homepage = self.getHistoryUrl(1)  #start from the first page
		data = self.spider.getDecodeResponseData(homepage)
		pattern = re.compile('当前页面是第1页,共(.*?)页',re.S)
		pages = re.findall(pattern, data)
		pageNum = 1
		if pages!=[]:
			pageNum = int(pages[0])
		historyPageList = []
		for i in range(1, pageNum+1):
			historyPageList.append(self.getHistoryUrl(i))
		recordList = []
		for url in historyPageList:
			recordList += self.getPartOfHistory(url)
		self.history = recordList
		#print(recordList)

	def getPartOfHistory(self, url):
		data = self.spider.getDecodeResponseData(url)
		#pattern = re.compile('<a data-from="" data-company=""  title="([^\"]*?)" href="([^\"]*?)"',re.S)
		pattern = re.compile('<tr >(.*?)</tr>',re.S)
		items1 = re.findall(pattern, data)
		pattern = re.compile('<tr class="tr_2">(.*?)</tr>',re.S)
		items2 = re.findall(pattern, data)
		for item in items2:
			items1.append(item)

		items2 = []
		for item in items1:
			item = item.replace("<td class=\"tdr\">","").replace("<td>","").replace("<div align=\"center\">","") \
			.replace("</div></td>", "\n").replace("\t","").replace(" ","").replace("\n\n","\n")
			list = item.split("\n")
			for i in range(0,list.count("")):
				list.remove("")
			items2.append(list)
		print("One page is finished! " +url)
		return items2
		

	def getAveragePriceOfLastyear(self):
		return ""

	def getLatestPrice(self):
		return self.currentPrice
	
	def getHistoryRecods(self):
		return self.history

