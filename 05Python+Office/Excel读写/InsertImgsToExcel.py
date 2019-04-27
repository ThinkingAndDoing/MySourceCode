#!/usr/bin/python3
# -*- coding: UTF-8 -*-
import xlsxwriter
import xlrd
from PIL import Image
import os

_ImgSize = 36

def initGlobalVar():
	global _SourceFile
	global _SheetName

	_SourceFile	='.\\WarningConfiguration.xlsx'
	_SheetName	='WarningConfig'
	
	
def getTableIndex(table):
	global indexName
	global indexPIFLName
	global indexImage
	
	keyName = table.row_values(0)
	indexName = keyName.index("Name")
	indexPIFLName = keyName.index("PIFLName")
	indexImage = keyName.index("PopupBitmap")

def generateImgExcel(sourceSheet):
	getTableIndex(sourceSheet)

	lTable = []
	for i in range(1, sourceSheet.nrows):
		lTable.append([sourceSheet.cell(i,indexName).value, sourceSheet.cell(i,indexPIFLName).value, sourceSheet.cell(i,indexImage).value])
	
	outputImgExcel(lTable)
	
def outputImgExcel(srcTable):

	book = xlsxwriter.Workbook('output.xlsx')
	sheet = book.add_worksheet('WarningConfig')
	lImgToDel = []
	
	for i in range(0, len(srcTable)):
	
		strSubDir = ""
		sheet.write(i, 0, srcTable[i][0])
		sheet.write(i, 1, srcTable[i][1])
		if srcTable[i][2].find("Img_")!=-1:
			strPath = '..\\..\\Resources\\Bitmaps\\Warning\\Telltales\\'
		else:
			strPath = '..\\..\\Resources\\Bitmaps\\Warning\\Message\\'
			
		if os.path.exists(strPath+srcTable[i][2] + ".png")==True:
			theScale = getScaleOfImg(strPath, srcTable[i][2] + ".png")
			sheet.insert_image(i, 2,strPath + srcTable[i][2] + ".png", {'x_scale':1/theScale, 'y_scale':1/theScale})
			sheet.set_row(i, _ImgSize)
			
	book.close()

def getScaleOfImg(path, filename, mwidth=_ImgSize, mheight=_ImgSize):
	image = Image.open(path + filename)
	w,h = image.size
	if w<=mwidth and h<=mheight:
		return 1
	if (1.0*w/mwidth) > (1.0*h/mheight):
		scale = 1.0*w/mwidth
	else:
		scale = 1.0*h/mheight
	return scale

if __name__ == "__main__":

	
	initGlobalVar()
	
	try:
		sourcewb = xlrd.open_workbook(_SourceFile)
		sourcews = sourcewb.sheet_by_name(_SheetName)
	except Exception as e:
		print("Exception:",e)
	else:
		generateImgExcel(sourcews)
	
	
	
	
	
	
	