#!/usr/bin/python3
# -*- coding: UTF-8 -*-

import os
import sys
import xlrd
import xlwt

_strLength = 18

def initGlobalVar():
	global _DstWorkBook
	global _DstWorkSheet
	global _SrcWorkBook
	global _SrcWorkSheet

	_DstWorkBook	="out.xls"
	_DstWorkSheet	="Sheet1"
	_SrcWorkBook	="input.xlsx"
	_SrcWorkSheet	="Sheet1"

def getTableIndex(table, key):
	keyName = table.row_values(0)
	indexKey = keyName.index(key)
	return indexKey

def convert(src, dst):
	startcol = getTableIndex(src, "SrcTable")
	
	for j in range(startcol+1, src.ncols):
		for i in range(0, src.nrows):
			srcstr = src.cell(i,j).value
			dststr = cutString(srcstr)
			dst.write(i, j, dststr)

def cutString(srcstr):
	if len(srcstr)> _strLength:
		return srcstr[:_strLength] + "..."
	else:
		return srcstr

def generate():
	try:
		sourcewb = xlrd.open_workbook(_SrcWorkBook)
		sourcews = sourcewb.sheet_by_name(_SrcWorkSheet)
		distwb = xlwt.Workbook()
		distws = distwb.add_sheet(_DstWorkSheet,cell_overwrite_ok=True)
	except Exception as e:
		print("Exception:",e)
	else:
		convert(sourcews,distws)
		distwb.save(_DstWorkBook)

if __name__=='__main__':

	initGlobalVar()
	generate()
	
	