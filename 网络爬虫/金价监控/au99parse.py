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

if __name__=="__main__":

	historyRec = [['2017-05-09', 'Au99.99', '276.88', '276.88', '274.55', '275.27', '-0.23', '-0.08%', '275.16', '127,953.00', '35,207,660,000.00'], ['2017-05-05', 'Au99.99', '278.00', '278.00', '274.03', '275.80', '-0.39', '-0.14%', '275.19', '138,884.00', '38,219,708,000.00'], ['2017-05-03', 'Au99.99', '281.60', '281.60', '280.03', '280.45', '-0.49', '-0.17%', '280.41', '91,102.00', '25,545,968,000.00'], ['2017-05-10', 'Au99.99', '275.24', '275.24', '273.00', '273.90', '-1.30', '-0.47%', '273.89', '171,124.00', '46,869,372,000.00'], ['2017-05-08', 'Au99.99', '280.50', '280.50', '275.00', '275.70', '-0.17', '-0.06%', '275.52', '120,678.00', '33,249,200,000.00'], ['2017-05-04', 'Au99.99', '289.99', '289.99', '275.60', '276.12', '-4.25', '-1.52%', '277.06', '173,249.00', '48,000,536,000.00'], ['2017-05-02', 'Au99.99', '281.99', '281.99', '280.80', '280.86', '-2.59', '-0.91%', '281.09', '139,369.00', '39,175,288,000.00']]
	
	auParse = AuParse()
	auParse.setRecords(historyRec)
	print("MidFinalPrice = " + auParse.getMidFinalPrice())
	print("getLastDayPrice = " + auParse.getLastDayPrice())


