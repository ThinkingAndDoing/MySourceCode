#!/usr/bin/env python3
#-*- coding:utf-8 -*-


import sys 
import xlrd
import codecs
import xml.dom.minidom
import GeneratorConmonConfig as Config

'''
global variable
'''

#variable to access to WarningHelper
_StrategyName = {'WarningStrategy':1,'AddNewWarningPolicy':2,'SelectNextWarningPolicy':3}

_DispatcherNm_pos = (1,2)  # dispatcher name position

_WarningType = {'WarningTypes':1,'Name':2,'TypeID':3,'Generate':4,'Value0':5}

_WarningLinesStart = (4,2) # warning Line start
_WarningLinesEnd = (5,2)   # warning Line End

_WarningTypesStart = (10,2) # warning Type Line start
_WarningTypesEnd = (11,2)    # warning Type Line End

_WarningStrategyStart = (7,2) # warning strategy Line start
_WarningStrategyEnd = (8,2)   # warning strategy Line End

'''
functions
'''

class Helper:
	def __init__(self, sheetHelper):
		self.sheet = sheetHelper
		self.propertyMap = []
		self.propertiesList = []
		self.wrnLinesStart = 0
		self.wrnLinesEnd = 0
		self.wrnTypesStart = 0
		self.wrnTypesEnd = 0
		self.wrnStrategyStart = 0
		self.wrnStrategyEnd = 0
	
	def initKeyPos(self):
		
		self.wrnLinesStart = int(self.sheet.cell_value(_WarningLinesStart[0],_WarningLinesStart[1]))-1
		self.wrnLinesEnd = int(self.sheet.cell_value(_WarningLinesEnd[0],_WarningLinesEnd[1]))
		if(self.wrnLinesStart > self.wrnLinesEnd):
			AddRunLog('warning', 'input configure files,configure warning strategy error,start > end !\n', thisFile, sys._getframe().f_lineno)
			return 1
			
		self.wrnTypesStart = int(self.sheet.cell_value(_WarningTypesStart[0],_WarningTypesStart[1]))-1
		self.wrnTypesEnd = int(self.sheet.cell_value(_WarningTypesEnd[0],_WarningTypesEnd[1]))
		if(self.wrnTypesStart > self.wrnTypesEnd):
			print('Warning: input configure files,configure warning type error,start > end !\n')
			return 1

		self.wrnStrategyStart = int(self.sheet.cell_value(_WarningStrategyStart[0],_WarningStrategyStart[1]))-1
		self.wrnStrategyEnd = int(self.sheet.cell_value(_WarningStrategyEnd[0],_WarningStrategyEnd[1]))
		if(self.wrnStrategyStart > self.wrnStrategyEnd ):
			print('Warning: input configure files,configure warning lines error,start > end !\n')
			return 1
		return 0

	def getHelperProperties(self):
		self.initKeyPos()

		for row in range(self.wrnTypesStart, self.wrnTypesEnd):
			if self.sheet.cell(row, _WarningType['Generate']).value!='Yes':
				continue
			
			properties = []
			i = _WarningType['WarningTypes']
			while i< self.sheet.ncols and self.sheet.cell(row, i).value != "":
				properties.append(self.sheet.cell(row, i).value)
				i = i+1
				
			self.propertiesList.append(properties)
			
			keyName = self.sheet.col_values(1)
			for item in properties[_WarningType['Generate']:]:
				itemRow = keyName.index(item)
				mapItem = {"PropertyName":self.sheet.cell(itemRow, 1).value ,"ValueType":self.sheet.cell(itemRow, 2).value ,"IndexNameOfWarningConfig":self.sheet.cell(itemRow, 3).value}
				if self.propertyMap.count(mapItem) == 0:
					self.propertyMap.append(mapItem)

	def getDispatcherName(self):
		dispatchername = self.sheet.cell_value(_DispatcherNm_pos[0],_DispatcherNm_pos[1])
		print('Dispatcher name',dispatchername)
		return dispatchername

def test(InputExcel):
	Data = xlrd.open_workbook(InputExcel)
	sheet = Data.sheet_by_name(u'WarningHelper')
	
	helper = Helper(sheet)
	helper.getHelperProperties()
	print("******************\n")
	for i in helper.propertyMap:
		print(i)
	print("******************\n")
	for i in helper.propertiesList:
		print(i)

if __name__ == "__main__":
	test("WarningConfiguration.xlsm")
	
	
	
	
	