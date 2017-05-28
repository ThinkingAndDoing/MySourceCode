# -*- coding: UTF-8 -*-
import au99price
import au99parse
#import sqliteDB
import sendemail
import time
import datetime
import sys

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
		auPrice = au99price.AuPrice()
		auPrice.setStartDate(getDate(localtime.tm_year-i-1, localtime.tm_mon, localtime.tm_mday))
		auPrice.setEndDate(getDate(localtime.tm_year-i, localtime.tm_mon, localtime.tm_mday))
		auPrice.run()

		auParse = au99parse.AuParse()
		auParse.setRecords(auPrice.getHistoryRecods())

		f = open("Analyse.txt", "a")
		f.write("起始日期："+getDate(localtime.tm_year-i-1, localtime.tm_mon, localtime.tm_mday)+"结束日期："+getDate(localtime.tm_year-i, localtime.tm_mon, localtime.tm_mday)+"\n")
		f.write("平均成交价"+str(auParse.getAverageFinalPrice())+"\n")
		f.write("中间成交价"+auParse.getMidFinalPrice()+"\n")
		f.write("最高成交价"+auParse.getHighestPrice()+"\n")
		f.write("最低交价"+auParse.getLowestPrice()+"\n")

def saveHistoryPriceToDB():
	localtime = time.localtime(time.time())
	auPrice = au99price.AuPrice()
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

def SendEmail(header="", content=""):
	smpt = sendemail.sendemail()
	smpt.login()
	smpt.setHeader(header)
	smpt.setContent(content)
	smpt.send()
	smpt.close()

def getAuPrice():
	localtime = time.localtime(time.time())
	auPrice = au99price.AuPrice()
	auPrice.setStartDate(getDate(localtime.tm_year-1, localtime.tm_mon, localtime.tm_mday))
	auPrice.setEndDate(getDate(localtime.tm_year, localtime.tm_mon, localtime.tm_mday))
	auPrice.run()
	auParse = au99parse.AuParse()
	auParse.setRecords(auPrice.getHistoryRecods())
	#saveHistoryPriceToDB()
	if float(auParse.getMidFinalPrice()) >float(auParse.getLastDayPrice()):
		SendEmail("Au Price", auParse.getLastDayPrice())

#getAuPrice()

