#!/usr/bin/env python3
#-*- coding:utf-8 -*-

'''
author : zhu cuicui
date   : 2016-09-29 
input: Object.xls output: Object.xml
'''

import sys 
import xlrd
import codecs
import xml.dom.minidom
import GeneratorConmonConfig as Config
from GeneratorConmonConfig import AddRunLog
import GeneratorCommonHelper


'''
global variable
'''
thisFile = sys._getframe().f_code.co_filename

InputExcel = Config._InputExcelName

outputFile = Config._WarningObjectFile

WarningType = GeneratorCommonHelper._WarningType

TypeName = {'empty':0,'string':1,'number':2,'date':3,'boolean':4,'error':5}

'''
functions
'''
		
class WarningObject:
	def __init__(self, helper, sheetcfg):
		self._Helper = helper
		self._sheetCfg = sheetcfg
		impl = xml.dom.minidom.getDOMImplementation() 
		self._dom = impl.createDocument(None,'Objects',None)
		self._rootElement = self._dom.documentElement
		self.indexList = []


	def getIndexOfPropertyMapByName(self, indexOfName):
		name = self._sheetCfg.cell(0, indexOfName).value
		for i in range(0, len(self._Helper.propertyMap)):
			if self._Helper.propertyMap[i]["IndexNameOfWarningConfig"]==name:
				return i

	def getAllIndexOfConfiguration(self, properties):
		self.indexList = []
		keyName = self._sheetCfg.row_values(0)
		for name in properties[WarningType['Generate']:]:
			indexOfPropertyMap = 0
			for i in range(0, len(self._Helper.propertyMap)):
				if self._Helper.propertyMap[i]["PropertyName"]==name:
					indexOfPropertyMap = i
					break
			nameOfWarningConfig = self._Helper.propertyMap[indexOfPropertyMap]["IndexNameOfWarningConfig"]
			self.indexList.append(keyName.index(nameOfWarningConfig))

	def getIndexByName(self, name):
		keyName = self._sheetCfg.row_values(0)
		return keyName.index(name)
	
	def writeToXML(self):
		ret = self.addWarningObject()
		if(ret):
			return ret
		f= codecs.open(outputFile, 'w','utf-8')  
		self._dom.writexml(f, addindent='  ', newl='\n',encoding = 'utf-8')  
		f.close
		return 0

	def addWarningObject(self):
		print(self._Helper.propertyMap)
		for properties in self._Helper.propertiesList:
			print(properties) #['WarningExtensionSupportType[]', 'Warnings', 3.0, 'Yes', 'ID', 'Type', 'TextWList', 'TextWPopup', 'PopupBitmap', 'SoundId']
			self.getAllIndexOfConfiguration(properties)
			child = self._dom.createElement('Array')
			child.setAttribute('Name', properties[WarningType['Name']-1])
			child.setAttribute('ID', '%d'%properties[WarningType['TypeID']-1])
			child.setAttribute('Type', properties[WarningType['WarningTypes']-1])
			self._rootElement.appendChild(child)
			
			print("start from " + str(self._Helper.wrnLinesStart) + " to "+ str(self._Helper.wrnLinesEnd))
			for row in range(self._Helper.wrnLinesStart, self._Helper.wrnLinesEnd):
				if(properties[WarningType['TypeID']-1] == self._sheetCfg.cell(row, self.getIndexByName("TypeID")).value):
					child1 = self._dom.createElement('Object')
					child.appendChild(child1)
					child2 = self._dom.createElement('Properties')
					child1.appendChild(child2) 
					for i in range(0, len(self.indexList)):
						col = self.indexList[i]
						indexOfPropertyMap = self.getIndexOfPropertyMapByName(col)
						propertyName = self._Helper.propertyMap[indexOfPropertyMap]["PropertyName"]
						valueType = self._Helper.propertyMap[indexOfPropertyMap]["ValueType"]
						#self.addObjectsProperty(child2, propertyName, valueType, row, col)
						if self._sheetCfg.cell(row, col).value!='-':
							child3 = self._dom.createElement('Property')
							child3.setAttribute('Name',propertyName)
							child2.appendChild(child3)
	
							child4 = self._dom.createElement(valueType)
							textNodeName = ""
							if(self._sheetCfg.cell_type(row, col) == TypeName['number']):
								textNodeName = '%d'%self._sheetCfg.cell(row, col).value
							else:
								textNodeName = self._sheetCfg.cell(row, col).value
							_nameTxt = self._dom.createTextNode(textNodeName)
							child4.appendChild(_nameTxt)
							child3.appendChild(child4)
		return 0

def Main_GeneratedObject():
	Data = xlrd.open_workbook(InputExcel)
	_sheetHelper = Data.sheet_by_name(u'WarningHelper')
	_sheetCfg = Data.sheet_by_name(u'WarningConfig')
	
	helper = GeneratorCommonHelper.Helper(_sheetHelper)
	helper.getHelperProperties()
	wo = WarningObject(helper, _sheetCfg)
	ret = wo.writeToXML()
	return ret

if __name__ == "__main__":
	Main_GeneratedObject()
