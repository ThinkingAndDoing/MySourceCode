#!/usr/bin/python3
# -*- coding: UTF-8 -*-

import re
import os
import xlwt
import time
from robobrowser import RoboBrowser
import updateList

_InputFile = "urllist.txt"
_HistoryRecords = ".\\historyrecords\\"
_Result = "result.txt"
_OutputFile = _HistoryRecords + time.strftime("%Y%m%d", time.localtime())

class HousePriceWatching:
	"""
	Get the prices by the urlList
	"""
	def __init__(self):
		self.watchList = []
		self.summaryArray = []

	def setWatchList(self, list):
		self.watchList = list

	def getLatestData(self):
		retList = self.getPricesByUrlList(self.watchList)
		#print(retList)
		for line in retList:
			self.summaryArray.append(line)

	def getPricesByUrlList(self, urllist):
		user_agent = 'Mozilla/5.0 (Windows NT 10.0; WOW64; rv:47.0) Gecko/20100101 Firefox/47.0'
		b = RoboBrowser(history=True, user_agent=user_agent, parser='html.parser', timeout=5)

		contentList = []
		for url in urllist:
			if url=='':
				continue

			try:
				b.open(url)
				print(url)
			except Exception as e:
				print(e)
				self.printUrlAccessFail(url)
				continue
			else:
				content = b.find_all(class_='trl-item sty1') + b.find_all(class_='trl-item1')
				if content==[]:
					self.printUrlAccessFail(url)
					continue

			content.append(url)
			contentList.append(content)
		return contentList
	
	def printUrlAccessFail(self, url):
		print('Failed to get html tag. at ' + url)
		self.watchList.remove(url)

		
def writeStrToLocal(fn, str):
	f = open(fn, "w", encoding='utf-8')
	f.write(str)
	f.close()

def writeListToLocal(file, list):
	list.sort()
	while '' in list:
		list.remove('')
	f = open(file, "w", encoding='utf-8')
	for item in list:
		f.write(str(item)+"\n")
	f.close()

def writeMatrixToLocal(output, list):
	f = open(output, "w")
	for line in list:
		for value in line:
			f.write(str(value) + ",")
		f.write("\n")
	f.close()

def getRecordsFromLocal(file):
	dictPrice = {}
	f = open(_HistoryRecords + file, "r")
	for line in f.readlines():
		tempL = line.split(",")
		dictPrice.update({tempL[7]:tempL[0]})
	f.close()
	return dictPrice

def getComparedResult(start, to):
	result = "**********************************************" + "\n"
	result += "From: " + start + ", To: " + to + "\n"
	
	dictStart = getRecordsFromLocal(start)
	dictTo = getRecordsFromLocal(to)
	sum = 0
	for key in dictStart.keys():
		if key in dictTo:
			sum += 1
	result += str(sum) + " house is wathced!" + "\n"
	
	for key in dictStart.keys():
		if key in dictTo:
			toKey = re.sub(r'\D', "", str(dictTo[key]))
			startKey = re.sub(r'\D', "", str(dictStart[key]))
			if int(toKey) == int(startKey):
				continue
			if int(toKey) > int(startKey):
				result += key + ":Price Rise." + "\n"
			else:
				result += key + ":Price Fall." + "\n"
			result += "The previous price is " + startKey + ", the current price is " + toKey + "\n"
	return result

def getListFromLocal():
	f = open(_InputFile, "r", encoding='utf-8')
	retList = f.readlines()
	f.close()
	list = []
	for item in retList:
		if item!="" and item!="\n":
			list.append(item.replace("\n", ""))
	return list

def getPricesFromMatrix(list):
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

def printResult():
	l2 = os.listdir(_HistoryRecords)
	l2.sort()
	result = ""
	for i in range(0, len(l2)-1):
		result += getComparedResult(l2[i], l2[i+1])
	print(result)
	writeStrToLocal(_Result, result)

if __name__ == "__main__":

	#get the latest urllist
	updateList.updateUrlList()
	
	#get the prices by the latest urllist
	watcher = HousePriceWatching()
	watcher.setWatchList(getListFromLocal())
	watcher.getLatestData()

	recordlist = getPricesFromMatrix(watcher.summaryArray)
	writeMatrixToLocal(_OutputFile, recordlist)

	#print the result of the compared house price
	printResult()
	
	#write new list back to _InputFile
	writeListToLocal(_InputFile, watcher.watchList)



	


"""
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
"""