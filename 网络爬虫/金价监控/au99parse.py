# -*- coding: UTF-8 -*-
import au99price
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

	def getHighestPrice(self):
		'''
		Get the highest price of last period.
		'''
		self.sort()
		return self.recordlist[len(self.recordlist)-1][5]
		
	def getLowestPrice(self):
		'''
		Get the lowest price of last period.
		'''
		self.sort()
		return self.recordlist[0][5]

	def getLastDayPrice(self):
		'''
		Get the lastday price of last period.
		'''
		self.sort(0)
		return self.recordlist[len(self.recordlist)-1][5]

	def sort(self, index=5):
		self.sortIndex = index
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


