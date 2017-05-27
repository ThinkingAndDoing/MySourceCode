# -*- coding: UTF-8 -*-
import au99data
import time
import datetime

class AuParse:
	def __init__(self):
		self.header = ["日期","合约","开盘价","最高价","最低价","收盘价","涨跌额","涨跌幅","加权平均价","成交量（公斤）","成交金额（元）"]
		self.recordlist = []
		self.sortIndex = 5
		
	def setRecords(self, list):
		self.recordlist = list
	
	def writeToText(self):
		f = open("out.txt", "w")
		f.write(str(self.header)+'\n')
		for item in self.recordlist:
			f.write(str(item)+'\n')
		f.close()
	
	def getAverageFinalPrice(self):
		'''
		Get the average price of last period.
		'''
		length = float(len(self.recordlist))
		if length==0:
			return 0
		sum = 0
		for i in self.recordlist:
			sum += float(i[5])
		return sum/length
		
	def getMidFinalPrice(self):
		'''
		Get the mid price of last period.
		'''
		self.sort()
		index = int(len(self.recordlist)/2)
		return self.recordlist[index][5]

	def sort(self):
		try:
			self.recordlist = self.quickSort(self.recordlist, 0, len(self.recordlist)-1)
		except RecursionError:
			import sys
			sys.setrecursionlimit(1000000)
			self.recordlist = self.quickSort(self.recordlist, 0, len(self.recordlist)-1)
		
	def quickSort(self, L, low, high):
		i = low 
		j = high
		if i >= j:
			return L
		key = L[i]
		while i < j:
			while i < j and L[j][self.sortIndex] >= key[self.sortIndex]:
				j = j-1                                                             
			L[i] = L[j]
			while i < j and L[i][self.sortIndex] <= key[self.sortIndex]:
				i = i+1 
			L[j] = L[i]
		L[i] = key 
		self.quickSort(L, low, i-1)
		self.quickSort(L, j+1, high)
		return L

def getStartDate():
	localtime = time.localtime(time.time())
	return str(datetime.date(localtime.tm_year-10, localtime.tm_mon, localtime.tm_mday))

def getEndDate():
	localtime = time.localtime(time.time())
	return str(datetime.date(localtime.tm_year-9, localtime.tm_mon, localtime.tm_mday))

auPrice = au99data.AuPrice()
auPrice.setStartDate(getStartDate())
auPrice.setEndDate(getEndDate())
auPrice.run()

auParse = AuParse()
auParse.setRecords(auPrice.getHistoryRecods())
auParse.sort()
auParse.writeToText()
print(auParse.getAverageFinalPrice())
print(auParse.getMidFinalPrice())

f = open("Analyse.txt", "a")
f.write("起始日期："+getStartDate()+"结束日期："+getEndDate()+"\n")
f.write("平均成交价"+str(auParse.getAverageFinalPrice())+"\n")
f.write("中间成交价"+auParse.getMidFinalPrice()+"\n")

#sendmail



