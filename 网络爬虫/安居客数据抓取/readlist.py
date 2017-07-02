#!/usr/bin/python3
# -*- coding: UTF-8 -*-

import re
import os
import xlwt

_OutputExcel = 'output.xls'
_OutputFile = 'out.txt'
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

def writeToExcel(output, List):
	try:
		distwb = xlwt.Workbook()
		distws = distwb.add_sheet('records',cell_overwrite_ok=True)
	except:
		print("Exception:",e)
	else:
		writeLine(distws, List)
		distwb.save(output)

def writeStrToFile(fileName, content):
	f = open(fileName, "w", encoding='utf-8')
	f.write(content)
	f.close()

def writeListToFile(fileName, list):
	f = open(fileName, "w", encoding='utf-8')
	for item in list:
		f.write(str(item)+'\n')
	f.close()

def writeLine(distSheet, List):
	row = 0
	for line in List:
		col = 0
		for cell in line:
			distSheet.write(row, col, str(cell))
			col += 1
		row += 1

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
	listA = removeDuplicateItems(list)
	newList = []
	for line in listA:
		listArea = []
		listArea.append(line[6].split("  ")[0])
		listArea.append(line[6].split("  ")[1].split("-")[0])
		listArea.append(line[6].split("  ")[1].split("-")[1])
		listArea.append(line[6].split("  ")[1].split("-")[2])
		newList.append([line[0], line[1], line[2], line[3], line[4], line[5], listArea[0], listArea[1], listArea[2], listArea[3], line[7], line[8]])
	return newList

if __name__ == "__main__":
	try:
		if os.path.isfile(_OutputExcel):
			os.remove(_OutputExcel)
		f = open(_InputFile, "r", encoding='utf-8')
		value = f.read()

		#pattern = re.compile('<a data-from="" data-company=""  title="([^\"]*?)" href="([^\"]*?)"',re.S)
		pattern = re.compile('href="(.*?)" target="_blank" title="(.*?)">.*?<span>(.*?)</span>.*?<span>(.*?)</span>.*?<span>(.*?)</span>.*?<span>(.*?)</span>.*?title=(.*?)">.*?<span class="price-det"><strong>(.*?)</strong>万</span>.*?<span class="unit-price">(.*?)</span>',re.S)

		items = re.findall(pattern, value)
		writeToExcel(_OutputExcel, listFormat(items))
		#writeListToFile(_OutputFile, items)
	except Exception as e:
		print(e)
	



