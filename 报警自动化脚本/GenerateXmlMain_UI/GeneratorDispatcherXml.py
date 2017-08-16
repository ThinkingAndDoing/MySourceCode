#!/usr/bin/env python3
#-*- coding:utf-8 -*-

'''
author : zhu cuicui
date   : 2016-09-27 
input: dispatcher.xls output: dispatcher.xml
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

StrategyName = GeneratorCommonHelper._StrategyName


TypeName = {'empty':0,'string':1,'number':2,'date':3,'boolean':4,'error':5}

InputExcel = Config._InputExcelName

outputFile = Config._WarningDispatcherFile

'''
functions
'''

def getAllIndex(table):
	global indexName
	global indexPriority 
	global indexSubPrio
	global indexTimeSpanList
	global indexTypeID
	global indexDisplayMode
	global indexCategory
	global indexStrategyState
	global indexWarningStrategy

	keyName = table.row_values(0)
	indexName = keyName.index("Name")
	indexPriority = keyName.index("Priority")
	indexSubPrio = keyName.index("SubPrio")
	indexTimeSpanList = keyName.index("TimeSpanList")
	indexStrategyState = keyName.index("StrategyState")
	indexTypeID = keyName.index("TypeID")
	indexDisplayMode = keyName.index("DisplayMode")
	indexCategory = keyName.index("Category")
	indexWarningStrategy = keyName.index("WarningStrategy")

class WarningDispatcher:
	def __init__(self, helper, sheetcfg):
		self._Helper = helper
		self._sheetCfg = sheetcfg
		impl = xml.dom.minidom.getDOMImplementation() 
		self._dom = impl.createDocument(None,'WarningConfiguration',None)


	def writeToXML(self):
		ret = self.generateWarningDispatcher()
		if(ret):
			AddRunLog('error', 'Error!', thisFile, sys._getframe().f_lineno)
			return ret
		f= codecs.open(outputFile, 'w','utf-8')  
		self._dom.writexml(f, addindent='  ', newl='\n',encoding = 'utf-8')  
		f.close
		return 0

	def compareChildString(self, _FatherString, _ChildString):
		# print('debug len _fatherstring',_FatherString,len(_FatherString))
		# print('debug len _childstring',_ChildString,len(_ChildString))
		
		if(len(_FatherString) < len(_ChildString)):
			return -1
		
		list = _FatherString.split(";")
		index = 0
		for item in list:
			if item==_ChildString:
				return index
			index = index+1
		return -1 
	
	def generateWarningDispatcher(self):
		RootElement = self._dom.createElement('WarningDispatcher')
		if(self._Helper.getDispatcherName() == 1):
			AddRunLog('error', 'Error!', thisFile, sys._getframe().f_lineno)
			return 1
		RootElement.setAttribute("Name", self._Helper.getDispatcherName())
		RootElement.setAttribute("Type","WarningDispatcher")
		
		_contentEle = self._dom.createElement('Content')
		RootElement.appendChild(_contentEle)
		
		_rootElement = self._dom.documentElement
		_rootElement.appendChild(RootElement)
		
		self.addWrnObject(_contentEle)
		self.addWrnStrategy(_contentEle)
		return 0

	def addWrnObject(self, _contentEle):
		'''
		add warning objects of warningdispatcher
		'''

		for i in range(self._Helper.wrnLinesStart, self._Helper.wrnLinesEnd):
			child1 = self._dom.createElement('Warning')
			child1.setAttribute('Name', self._sheetCfg.cell(i, indexName).value)
			child1.setAttribute('Type',"HMI::WWS::WarningObject")
			_contentEle.appendChild(child1)
			
			child2 = self._dom.createElement('Properties')
			child1.appendChild(child2)
			
			child3 = self._dom.createElement('Property')
			child3.setAttribute('Name','ActiveModes')
			child2.appendChild(child3)
			
			child4 = self._dom.createElement('ListValue')
			child3.appendChild(child4)
			
			if(self._sheetCfg.cell(i,indexDisplayMode).value == 'IgnOFF_IgnON'):
				child5 = self._dom.createElement('Enum')
				nameTxt = self._dom.createTextNode('IgnOFF') 
				child5.appendChild(nameTxt)
				child4.appendChild(child5)

				child5 = self._dom.createElement('Enum')
				nameTxt = self._dom.createTextNode('IgnON') 
				child5.appendChild(nameTxt)
				child4.appendChild(child5)
				
			else:
				child5 = self._dom.createElement('Enum')
				nameTxt = self._dom.createTextNode(self._sheetCfg.cell(i,indexDisplayMode).value) 
				child5.appendChild(nameTxt)
				child4.appendChild(child5)


	def addWrnStrategy(self, _contentEle):
		for i in range(self._Helper.wrnStrategyStart, self._Helper.wrnStrategyEnd):

			_strategyname = self._Helper.sheet.cell(i,StrategyName['WarningStrategy']).value
			_addpolicy = self._Helper.sheet.cell(i,StrategyName['AddNewWarningPolicy']).value
			_selectpolicy = self._Helper.sheet.cell(i, StrategyName['SelectNextWarningPolicy']).value
		
			#add warning startegy for warningdispatcher
			childstrgy = self._dom.createElement('WarningStrategy'); 
			childstrgy.setAttribute('Name',_strategyname)
			childstrgy.setAttribute('Type','HMI::WSMS::WarningStrategy')
			_contentEle.appendChild(childstrgy)
			
			child2 = self._dom.createElement('Properties')
			childstrgy.appendChild(child2)
			
			child3 = self._dom.createElement('Property')
			child3.setAttribute('Name','AddNewWarningPolicy')
			child2.appendChild(child3)
			child4 = self._dom.createElement('Enum')
			nameTxt = self._dom.createTextNode(_addpolicy)
			child4.appendChild(nameTxt)
			child3.appendChild(child4)
			
			if(_selectpolicy != '-'):
				child3 = self._dom.createElement('Property')
				child3.setAttribute('Name','SelectNextWarningPolicy')
				child2.appendChild(child3)
				child4 = self._dom.createElement('Enum')
				nameTxt = self._dom.createTextNode(_selectpolicy)
				child4.appendChild(nameTxt)
				child3.appendChild(child4)

			wrnViewsEle = self._dom.createElement('Content')
			childstrgy.appendChild(wrnViewsEle)
            
			self.addWrnStrategyContent(wrnViewsEle, self._Helper.sheet.cell(i,StrategyName['WarningStrategy']).value)
       
	def addWrnStrategyContent(self, element, _strategyname):
		for j in range(self._Helper.wrnLinesStart, self._Helper.wrnLinesEnd):
			indexInsideCell = self.compareChildString(self._sheetCfg.cell(j,indexWarningStrategy).value, _strategyname)
			if(indexInsideCell!=-1):
				_wrnName = self._sheetCfg.cell(j,indexName).value
				print(_wrnName)
				_WSList = {}
				_WSList['WarningStrategy'] = _strategyname
				_WSList['TimeSpanList'] = self._sheetCfg.cell(j,indexTimeSpanList).value.split(";")[indexInsideCell]
				_WSList['StrategyState'] = _WSList['WarningStrategy'] + "_" + self._sheetCfg.cell(j,indexStrategyState).value.split(";")[indexInsideCell]
				if self._sheetCfg.cell_type(j,indexPriority) == TypeName['number']:
					_WSList['Priority'] = str(int(self._sheetCfg.cell(j,indexPriority).value))
				else:
					_WSList['Priority'] = str(int(self._sheetCfg.cell(j,indexPriority).value.split(";")[indexInsideCell]))
				if self._sheetCfg.cell_type(j,indexSubPrio) == TypeName['number']:
					_WSList['SubPriority'] = str(int(self._sheetCfg.cell(j,indexSubPrio).value))
				else:
					_WSList['SubPriority'] = str(int(self._sheetCfg.cell(j,indexSubPrio).value.split(";")[indexInsideCell]))

				child1 = self._dom.createElement('WarningView')
				child1.setAttribute('WarningName',_wrnName)
				child1.setAttribute('Type','HMI::WWS::WarningView')
				child1.setAttribute('TimeSpanList',_WSList['TimeSpanList'])
				element.appendChild(child1)
					
				child2 = self._dom.createElement('Properties')
				child1.appendChild(child2)
				child3 = self._dom.createElement('Property')
				child3.setAttribute('Name','StrategyState')
				child2.appendChild(child3)
				child4 = self._dom.createElement('Enum')
				nameTxt = self._dom.createTextNode(_WSList['StrategyState'])
				child4.appendChild(nameTxt)
				child3.appendChild(child4)          
					  
				child3 = self._dom.createElement('Property')
				child3.setAttribute('Name','Priority')
				child2.appendChild(child3)
				child4 = self._dom.createElement('Constant')
				nameTxt = self._dom.createTextNode(str(int(_WSList['Priority'])))
				child4.appendChild(nameTxt)
				child3.appendChild(child4)
					
				child3 = self._dom.createElement('Property')
				child3.setAttribute('Name','SubPriority')
				child2.appendChild(child3)
				child4 = self._dom.createElement('Constant')
				nameTxt = self._dom.createTextNode(str(int(_WSList['SubPriority'])))
				child4.appendChild(nameTxt)
				child3.appendChild(child4)

    
def Main_GeneratedDispatcher(): 
	
	Data = xlrd.open_workbook(InputExcel)
	_sheetHelper = Data.sheet_by_name(u'WarningHelper')
	_sheetCfg = Data.sheet_by_name(u'WarningConfig')
	
	getAllIndex(_sheetCfg)

	helper = GeneratorCommonHelper.Helper(_sheetHelper)
	helper.getHelperProperties()
	wd = WarningDispatcher(helper, _sheetCfg)
	ret = wd.writeToXML()
	return ret
	
if __name__ == "__main__":
	Main_GeneratedDispatcher()
