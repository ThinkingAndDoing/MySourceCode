#!/usr/bin/python3
# -*- coding: UTF-8 -*-

import re
import os
import xlwt

_OutputExcel = 'output.xls'
_OutputFile = 'out.txt'
_InputFile = "list.txt"

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
		f.write(str(item).replace('<strong>', '').replace('</strong>', '')+'\n')
	f.close()

def writeLine(distSheet, List):
	row = 0
	for line in List:
		col = 0
		for cell in line:
			distSheet.write(row, col, str(cell).replace('<strong>', '').replace('</strong>', ''))
			col += 1
		row += 1


if __name__ == "__main__":
	try:
		if os.path.isfile(_OutputExcel):
			os.remove(_OutputExcel)
		f = open(_InputFile, "r", encoding='utf-8')
		value = f.read()

		#pattern = re.compile('<a data-from="" data-company=""  title="([^\"]*?)" href="([^\"]*?)"',re.S)
		pattern = re.compile('href="(.*?)" target="_blank" title="(.*?)">.*?<span>(.*?)</span>.*?<span>(.*?)</span>.*?<span>(.*?)</span>.*?<span>(.*?)</span>.*?title=(.*?)">.*?<span class="price-det">(.*?)</span>.*?<span class="unit-price">(.*?)</span>',re.S)

		items = re.findall(pattern, value)
		writeToExcel(_OutputExcel, items)
		#writeListToFile(_OutputFile, items)
	except Exception as e:
		print(e)
	






