#!/usr/bin/python3
# -*- coding: UTF-8 -*-

import xlwt

_OutputFile = 'output.xls'

def startRead():
	try:
		distwb = xlwt.Workbook()
		distws = distwb.add_sheet('records',cell_overwrite_ok=True)
	except:
		print("Exception:",e)
	else:
		writeToExcel(distws, List)
		distwb.save(_OutputFile)

def writeToFile(fileName, content):
	f = open(fileName, "w", encoding='utf-8')
	f.write(content)
	f.close()

def writeToExcel(distSheet, List):
	for i in range(0, len(List)):
		if i>=1:
			return
		distSheet.write(i, 3, str(List[i]))

f = open("list.txt", "r", encoding='utf-8')
value = f.read()

value = value.replace("houseListTitle", "")
value = value.replace("<div class=\"house-details\">", "")
value = value.replace("</div>", "")
value = value.replace("<div class=\"house-title\">", "")
value = value.replace("<div class=\"tags-bottom\">", "")
value = value.replace("<div class=\"details-item\">", "")

writeToFile('1.txt', value)









