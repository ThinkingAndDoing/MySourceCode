#!/usr/bin/python3
# -*- coding: UTF-8 -*-

import re
import os
import xlwt
import time
from robobrowser import RoboBrowser

_InputFile = "list.txt"
_HistoryRecords = ".\\historyrecords\\"
_OutputFile = _HistoryRecords + time.strftime("%Y%m%d", time.localtime())

def quickSortByIndex (L, low, high, index):
    i = low 
    j = high
    if i >= j:
        return L
    key = L[i][index]
    temp = L[i]
    while i < j:
        while i < j and L[j][index] >= key:
            j = j-1                                                             
        L[i] = L[j]
        while i < j and L[i][index] <= key:
            i = i+1 
        L[j] = L[i]
    L[i] = temp 
    quickSortByIndex (L, low, i-1, index)
    quickSortByIndex (L, j+1, high, index)
    return L

class HousePriceWatching:
	def __init__(self):
		self.watchList = []
		self.summaryArray = []

	def setWatchList(self, list):
		self.watchList = list

	def getLatestData(self):
		retList = self.readList(self.watchList)
		#print(retList)
		for line in retList:
			self.summaryArray.append(line)

	def readList(self, urllist):
		user_agent = 'Mozilla/5.0 (Windows NT 10.0; WOW64; rv:47.0) Gecko/20100101 Firefox/47.0'
		b = RoboBrowser(history=True, user_agent=user_agent, parser='html.parser')

		contentList = []
		for url in urllist:
			if url=='':
				continue

			b.open(url)
			#print(url)
			#content = b.find_all(has_logr)
			#content = b.find_all('dd', class_='info rel')
			content = b.find_all(class_='trl-item sty1') + b.find_all(class_='trl-item1')
			if content==[]:
				print('Failed to get html tag. at ' + url)
				continue

			#print(content)
			content.append(url)
			contentList.append(content)
		#print(contentList)
		return contentList

def getListFromRecord(file):
	dictPrice = {}
	f = open(_HistoryRecords + file, "r")
	for line in f.readlines():
		tempL = line.split(",")
		dictPrice.update({tempL[7]:tempL[0]})
	f.close()
	#print(dictPrice)
	return dictPrice

def printComparedResult(start, to):
	print("**********************************************")
	print("From: " + start + ", To: " + to)
	
	dictStart = getListFromRecord(start)
	dictTo = getListFromRecord(to)
	sum = 0
	for key in dictStart.keys():
		if key in dictTo:
			sum += 1		
	print(str(sum) + " house is wathced!")
	
	for key in dictStart.keys():
		if key in dictTo:
			toKey = re.sub(r'\D', "", str(dictTo[key]))
			startKey = re.sub(r'\D', "", str(dictStart[key]))
			if int(toKey) == int(startKey):
				continue
			if int(toKey) > int(startKey):
				print(key + ":Price Rise.")
			else:
				print(key + ":Price Fall.")
			print("The previous price is " + startKey + ", the current price is " + toKey)

def printResult():
	l2 = os.listdir(_HistoryRecords)
	l2.sort()
	for i in range(0, len(l2)-1):
		printComparedResult(l2[i], l2[i+1])

def getListFromInputfile():
	f = open(_InputFile, "r", encoding='utf-8')
	retList = f.readlines()
	
	list = []
	for item in retList:
		if item!="" and item!="\n":
			list.append(item.replace("\n", ""))
	#print(list)
	return list
	
def writeMatrixToTxt(output, list):
	f = open(output, "w")
	for line in list:
		for value in line:
			f.write(str(value) + ",")
		f.write("\n")
	f.close()
	
def dataFetchFromMatrix(list):
	mMatrix = []
	for line in list:
		mlist = []
		for value in line:
			strtemp = value
			strtemp = re.sub(r'<[^>]*>', "", str(strtemp))
			strtemp = re.sub(r'\n', "", str(strtemp))
			strtemp = re.sub(r'\r', "", str(strtemp))
			strtemp = re.sub(r' ', "", str(strtemp))
			mlist.append(strtemp)
		mMatrix.append(mlist)
	#print(mMatrix)
	return mMatrix

if __name__ == "__main__":
	'''
	if os.path.isfile(_OutputExcel):
		os.remove(_OutputExcel)
	'''
	watcher = HousePriceWatching()
	watcher.setWatchList(getListFromInputfile())
	watcher.getLatestData()

	recordlist = dataFetchFromMatrix(watcher.summaryArray)
	writeMatrixToTxt(_OutputFile, recordlist)

	
	printResult()


	




