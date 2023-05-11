#!/usr/bin/python3
# -*- coding: UTF-8 -*-
import sys
from decimal import Decimal
from decimal import getcontext



sys.setrecursionlimit(1000000)

dicCol={'TICKER':0,'DTYYYYMMDD':1,'TIME':2,'OPEN':3,'HIGH':4,'LOW':5,'CLOSE':6,'VOL':7}


class GlobalVariable:
	_aDataBase = []
	#strCurrencyPair = ""
	_iRow = 0
	_dicDiff={}

def countDiff(iDiff):
	global GV
	
	if str(iDiff) in GV._dicDiff:
		GV._dicDiff[str(iDiff)] += 1
	else:
		GV._dicDiff[str(iDiff)] = 1
	
def loadFromLocal(filename):
	hFile = open(filename, "r")
	lRecords = hFile.readlines()
	hFile.close()
	return lRecords
	
def countDiffIn60Secs():
	global GV
	
	for i in range(1, len(GV._aDataBase)):
		fDiff = abs(Decimal(GV._aDataBase[i][dicCol["CLOSE"]])-Decimal(GV._aDataBase[i-1][dicCol["CLOSE"]]))
		countDiff(fDiff)
		if abs(int(GV._aDataBase[i][dicCol["TIME"]])-int(GV._aDataBase[i-1][dicCol["TIME"]]))==100:
			if int(fDiff)>6:
				print(GV._aDataBase[i][dicCol["DTYYYYMMDD"]]+":"+GV._aDataBase[i][dicCol["TIME"]]+":"+GV._aDataBase[i][dicCol["CLOSE"]]+":"+GV._aDataBase[i-1][dicCol["CLOSE"]]+"  Diff="+str(fDiff))

def initDataBase():
	global GV

	lTemp = loadFromLocal("XAUUSD.txt")
	for strLine in lTemp[1:]:
		#print(strLine.replace("\n", "").split(","))
		GV._aDataBase.append(strLine.replace("\n", "").split(","))


if __name__ == '__main__':
	global GV
	
	GV = GlobalVariable()
	
	initDataBase()
	countDiffIn60Secs()
	
	#print(GV._dicDiff)
	print("次数：点差")
	for i in sorted(GV._dicDiff.keys()):
		print(str(GV._dicDiff[i])+":"+i)
	'''
	print(Decimal('4.20') + Decimal('2.10'))
	'''
	