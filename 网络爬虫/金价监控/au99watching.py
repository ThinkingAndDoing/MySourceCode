# -*- coding: UTF-8 -*-
import au99data
import sqliteDB
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

def getDate(year, month, day):
	return str(datetime.date(year, month, day))

def getLastTenYearsAnalyse():
	'''
	Get the analyse data of last ten years
	'''
	for i in range(0,10):
		localtime = time.localtime(time.time())
		auPrice = au99data.AuPrice()
		auPrice.setStartDate(getDate(localtime.tm_year-i-1, localtime.tm_mon, localtime.tm_mday))
		auPrice.setEndDate(getDate(localtime.tm_year-i, localtime.tm_mon, localtime.tm_mday))
		auPrice.run()

		auParse = AuParse()
		auParse.setRecords(auPrice.getHistoryRecods())

		f = open("Analyse.txt", "a")
		f.write("起始日期："+getDate(localtime.tm_year-i-1, localtime.tm_mon, localtime.tm_mday)+"结束日期："+getDate(localtime.tm_year-i, localtime.tm_mon, localtime.tm_mday)+"\n")
		f.write("平均成交价"+str(auParse.getAverageFinalPrice())+"\n")
		f.write("中间成交价"+auParse.getMidFinalPrice()+"\n")
		f.write("最高成交价"+auParse.getHighestPrice()+"\n")
		f.write("最低交价"+auParse.getLowestPrice()+"\n")

def saveHistoryPriceToDB():
	localtime = time.localtime(time.time())
	auPrice = au99data.AuPrice()
	auPrice.setStartDate(getDate(localtime.tm_year-10, localtime.tm_mon, localtime.tm_mday))
	auPrice.setEndDate(getDate(localtime.tm_year, localtime.tm_mon, localtime.tm_mday))
	auPrice.run()

	mydb = sqliteDB.SqliteDB()
	mydb.openDB('AuPrice.db')
	#["日期","合约","开盘价","最高价","最低价","收盘价","涨跌额","涨跌幅","加权平均价","成交量（公斤）","成交金额（元）"]
	mydb.runSQL('''CREATE TABLE AUPRICE
       (DATE	TEXT PRIMARY KEY     NOT NULL,
       CONTRACT	TEXT	NOT NULL,
       STARTPRICE	TEXT	NOT NULL,
       HIGHESTPRICE	TEXT	NOT NULL,
       LOWESTPRICE	TEXT	NOT NULL,
       ENDPRICE	TEXT	NOT NULL,
       FLUCTUATION	TEXT	NOT NULL,
       PRICECHANGERATIO	TEXT	NOT NULL,
       WAP	TEXT	NOT NULL,
       TRADINGVOLUME	TEXT	NOT NULL,
       AMO           TEXT    NOT NULL);''')
	
	for item in auPrice.getHistoryRecods():
		insertSQL = "INSERT INTO AUPRICE (DATE,CONTRACT,STARTPRICE,HIGHESTPRICE,LOWESTPRICE,ENDPRICE,FLUCTUATION,PRICECHANGERATIO,"+\
		"WAP,TRADINGVOLUME,AMO) VALUES ('" +item[0]+"','"+item[1]+"','"+item[2]+"','"+item[3]+"','"+item[4]+"','"+item[5]+"','"\
		+item[6]+"','"+item[7]+"','"+item[8]+"','"+item[9]+"','"+item[10]+"')"
		mydb.runSQL(insertSQL)

#saveHistoryPriceToDB()
#sendmail



