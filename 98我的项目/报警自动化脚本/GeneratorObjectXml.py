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
import GeneratorCommonConfig as Config
from GeneratorCommonConfig import AddRunLog


'''
global variable
'''
thisFile = sys._getframe().f_code.co_filename

Config.requestConfig()

InputExcel = Config._FileList['_InputExcelName']

outputFile = Config._FileList['_WarningObjectFile']

WrnObjConf = Config._WrnObjConf

TypeName = {'empty':0,'string':1,'number':2,'date':3,'boolean':4,'error':5}

'''
functions
'''

def is_number(s):
    try:
        float(s)
        return True
    except ValueError:
        pass
 
    try:
        import unicodedata
        unicodedata.numeric(s)
        return True
    except (TypeError, ValueError):
        pass
 
    return False

class WarningObject:
	def __init__(self, sheetcfg):
		self._sheetCfg = sheetcfg
		impl = xml.dom.minidom.getDOMImplementation() 
		self._dom = impl.createDocument(None,'Objects',None)
		self._rootElement = self._dom.documentElement
		self.wrnLinesStart = 1
		self.wrnLinesEnd = self._sheetCfg.nrows
		
	def getValueType(self, value):
		if is_number(str(value)):
			return "Constant"
		else:
			return "Resource"

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
		for key in WrnObjConf.keys():
			if WrnObjConf[key][2] != 'Yes':
				continue
			print(key) #WarningExtensionSupportType[]
			child = self._dom.createElement('Array')
			child.setAttribute('Name', WrnObjConf[key][0])
			child.setAttribute('ID', WrnObjConf[key][1])
			child.setAttribute('Type', key)
			self._rootElement.appendChild(child)
			
			print("start from " + str(self.wrnLinesStart) + " to "+ str(self.wrnLinesEnd))
			for row in range(self.wrnLinesStart, self.wrnLinesEnd):
				if WrnObjConf[key][1] == str(int(self._sheetCfg.cell(row, self.getIndexByName("Type")).value)):
					child1 = self._dom.createElement('Object')
					child.appendChild(child1)
					child2 = self._dom.createElement('Properties')
					child1.appendChild(child2)
					for propertyName in WrnObjConf[key][3:]: 
						col = self.getIndexByName(propertyName)
						if self._sheetCfg.cell(row, col).value!='-':
							child3 = self._dom.createElement('Property')
							child3.setAttribute('Name',propertyName)
							child2.appendChild(child3)
							
							valueType = self.getValueType(self._sheetCfg.cell(row, col).value)
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
	_sheetCfg = Data.sheet_by_name(u'WarningConfig')
	
	wo = WarningObject(_sheetCfg)
	ret = wo.writeToXML()
	return ret

if __name__ == "__main__":
	Main_GeneratedObject()
