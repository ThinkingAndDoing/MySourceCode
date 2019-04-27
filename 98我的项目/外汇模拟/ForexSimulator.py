#!/usr/bin/python3
# -*- coding: UTF-8 -*-
import matplotlib.pyplot as plt
import numpy as np
import sys

sys.setrecursionlimit(1000000)

dicCol={'TICKER':0,'DTYYYYMMDD':1,'TIME':2,'OPEN':3,'HIGH':4,'LOW':5,'CLOSE':6,'VOL':7}


class GlobalVariable:
	_aDataBase = [] #all the history data
	#strCurrencyPair = ""
	_lSegment = []
	_iThreshold = 5
	_iRow = 0
	_dicDiff={}

class Order:
	startPrice = 0
	startNum = 0

class Broker:
	orders = [] #持有的单子
	stoploss = 0
	takeprofit = 0
	accoundbalance = 0 #结余
	equity = 0#净值
	
	def buy():
		print("buy")
	
	def sell():
		print("sell")
	
	def run(start, end):
		#测试从start到end的历史数据
		print("run")

def countDiff(iDiff):
	global GV
	
	#print(str(iDiff))
	if str(iDiff) in GV._dicDiff:
		GV._dicDiff[str(iDiff)] += 1
	else:
		GV._dicDiff[str(iDiff)] = 1
	
def loadFromLocal(filename):
	hFile = open(filename, "r")
	lRecords = hFile.readlines()
	hFile.close()
	return lRecords
	
def getSegment(iStart, iCurClose, boIsUp):
	global GV
	
	#print(_iRow)
	if boIsUp==False:# fall down
		iEnd = iCurClose
		GV._iRow += 1
		while GV._iRow < len(GV._aDataBase):
			iCurClose = float(GV._aDataBase[GV._iRow][dicCol["CLOSE"]])
			if iCurClose < iEnd:
				iEnd = iCurClose
			elif iCurClose-iEnd > GV._iThreshold:# reverse
				GV._lSegment.append([iStart, iEnd])
				getSegment(iEnd, iCurClose, True)
			else:
				GV._iRow += 1
	else:# go up
		iEnd = iCurClose
		GV._iRow += 1
		while GV._iRow < len(GV._aDataBase):
			iCurClose = float(GV._aDataBase[GV._iRow][dicCol["CLOSE"]])
			if iCurClose > iEnd:
				iEnd = iCurClose
			elif iEnd-iCurClose > GV._iThreshold:# reverse
				GV._lSegment.append([iStart, iEnd])
				getSegment(iEnd, iCurClose, False)
			else:
				GV._iRow += 1
		
def getSegments():
	global GV
	
	GV._iRow = 1
	iStart = float(GV._aDataBase[0][dicCol["CLOSE"]])	
	iEnd = 0
	while GV._iRow < len(GV._aDataBase):
		iCurClose = float(GV._aDataBase[GV._iRow][dicCol["CLOSE"]])
		if abs(iStart - iCurClose) > GV._iThreshold:
			if iStart > iCurClose:
				getSegment(iStart, iCurClose, False)
			else:
				getSegment(iStart, iCurClose, True)
		else:
			GV._iRow += 1

def initDataBase():
	global GV

	lTemp = loadFromLocal("XAUUSD.txt")
	for strLine in lTemp[1:]:
		#print(strLine.replace("\n", "").split(","))
		GV._aDataBase.append(strLine.replace("\n", "").split(","))

def playPlot():
	global GV
	
	lX = []
	lY = []
	iIndex = 1
	for lLine in GV._lSegment:
		lX.append(lLine[0])
		lY.append(iIndex)
		iIndex += 1
		lX.append(lLine[1])
		lY.append(iIndex)
		iIndex += 1
	plt.plot(lY, lX)
	plt.show()

if __name__ == '__main__':
	global GV
	
	GV = GlobalVariable()

	initDataBase()
	getSegments()
	
	print(GV._lSegment)
	for line in GV._lSegment:
		countDiff(int(abs(float(line[0])-float(line[1]))))
		#print(int(abs(float(line[0])-float(line[1]))))
	#print(len(GV._lSegment))
	#print(sorted(GV._dicDiff))
		
	for i in range(0,70):
		if str(i) in GV._dicDiff:
			print(str(i)+":"+str(GV._dicDiff[str(i)]))
		else:
			print(str(i)+":0")
	
	