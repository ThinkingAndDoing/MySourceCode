#!/usr/bin/python3
# -*- coding: UTF-8 -*-

import re
import os
import xlwt
from robobrowser import RoboBrowser

_OutputExcel = 'output.xls'
_InputFile = "list.txt"

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

def removeDuplicateItems(list):
	ListA = quickSortByIndex (list, 0, len(list)-1, 1)
	i = 1
	while i<len(ListA):
		if ListA[i][1]==ListA[i-1][1] and ListA[i][2]==ListA[i-1][2] \
		and ListA[i][3]==ListA[i-1][3] and ListA[i][4]==ListA[i-1][4] \
		and ListA[i][5]==ListA[i-1][5] and ListA[i][6]==ListA[i-1][6] \
		and ListA[i][7]==ListA[i-1][7]:
			del ListA[i]

		else:
			i += 1
	return ListA

def listFormat(list):
	newList = []
	for line in list:
		listArea = []
		listArea.append(line[6].split(" ")[0].split("-")[0])
		listArea.append(line[6].split(" ")[0].split("-")[1])
		listArea.append(line[6].split(" ")[1])
		newList.append([line[0], line[1], line[2], line[3], line[4], line[5], listArea[0], listArea[1], listArea[2], line[7]])
	return newList
	
def has_logr(tag):
	'''
	http://nj.58.com/zufang/	content = b.find_all(has_logr)
	http://zu.nanjing.fang.com/house-a0268/	content = b.find_all(class_='info rel')
	http://nj.ganji.com/fang1/	content = b.find_all(class_='f-list-item')
	'''
	return tag.has_attr('logr')

class HousePriceWatching:
	def __init__(self):
		self.watchList = []
		self.summaryArray = []

	def setWatchList(self, list):
		self.watchList = list

	def getLatestData(self):
		#pattern = re.compile('<a data-from="" data-company=""  title="([^\"]*?)" href="([^\"]*?)"',re.S)
		pattern = re.compile('<a class="js-title value title-font".*?href="(.*?)".*?title="(.*?)".*?<span>(.*?)</span>.*?<span>(.*?)</span>.*?<span>(.*?)</span>.*?<span>(.*?)</span>.*?<span class="num">(.*?)</span>.*?<div class="time">(.*?)</div>',re.S)
		#pattern = re.compile('filterlist" href="(.*?)" target="_blank" title="(.*?)">.*?<p class="details-item tag">(.*?)<span>.*?</span>(.*?)<span>.*?</span>(.*?)<span>.*?</span>(.*?)</p>.*?［(.*?)］.*?<strong>(.*?)</strong>',re.S)

		items = re.findall(pattern, value)
		writeToExcel(_OutputExcel, removeDuplicateItems(items))

	def readList(self, urllist):
		user_agent = 'Mozilla/5.0 (Windows NT 10.0; WOW64; rv:47.0) Gecko/20100101 Firefox/47.0'
		b = RoboBrowser(history=True, user_agent=user_agent, parser='html.parser')

		for url in urllist:
			if url=='':
				continue

			b.open(url)
			print(url)
			#content = b.find_all(has_logr)
			#content = b.find_all('dd', class_='info rel')
			content = b.find_all(class_='f-list-item')
			if content==[]:
				print('Failed to get html tag.')
				return

			writeListToFile(FileName, content)

	def writeToExcel(output, List):
		try:
			distwb = xlwt.Workbook()
			distws = distwb.add_sheet('records',cell_overwrite_ok=True)
		except:
			print("Exception:",e)
		else:
			writeLine(distws, List)
			distwb.save(output)


def getListFromInputfile():
	f = open(_InputFile, "r", encoding='utf-8')
	retList = f.readlines()
	
	list = []
	for item in retList:
		if item!="" and item!="\n":
			list.append(item.replace("\n", ""))
	print(list)
	return list
	
if __name__ == "__main__":
	if os.path.isfile(_OutputExcel):
		os.remove(_OutputExcel)

	watcher = HousePriceWatching()
	watcher.setWatchList(getListFromInputfile())
	watcher.getLatestData()


	




