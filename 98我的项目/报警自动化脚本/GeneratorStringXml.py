#!/usr/bin/env python3
#-*- coding:utf-8 -*-


'''
author : zhu cuicui
date   : 2016-09-26 
input: String.xls output: String.xml
'''

import sys   
import xlrd
import codecs 
import xml.dom.minidom

global ColStart,ColNum
global ErrorValue,ListLan
import GeneratorCommonConfig as Config
from GeneratorCommonConfig import AddRunLog

'''
global variable
'''
thisFile = sys._getframe().f_code.co_filename

#SheetNumber = 1 #read sheet number
ErrorValue = 42 #==#N/A

Config.requestConfig()

ColNum = Config._LangSetting['_LangColNum'] + 1
ListLan = Config._LangSetting['_ListLan']
inputExcelName = Config._FileList['_InputExcelName']
outputFile = Config._FileList['_GenStrFile']

'''
functions
'''

def CellValue(table, row, col):
	value = ""
	try:
		value = str(table.cell(row, col).value)
	except:
		print("Cell value is not exist! row = "+ str(row) + ", col = " + str(col))
	return value



#function : Add warning display strings
def AddWrnString(keyvalue,elements):
    resElement = dom.createElement('Resource')
    resElement.setAttribute("Name",keyvalue)  #string remember modify name rule
    
    
    if len(elements) > len(ListLan):
        print('Warnings:Language attribute exceed the safe range ,len %d!'% len(elements))
        AddRunLog('warning', 'Language attribute exceed the safe range ,len'+str(len(elements)), thisFile, sys._getframe().f_lineno) #log record error message
        return 1
      
    for i in range(0,len(elements)):
        chElement = dom.createElement('Value')
        chElement.setAttribute("DependencyExpression",ListLan[i])
        nameTxt = dom.createTextNode(elements[i])
        chElement.appendChild(nameTxt)   
        resElement.appendChild(chElement)     
    root.appendChild(resElement)
    
    return 0

#function : Read input excel     
def ReadExcel():
    
    try:
        Data = xlrd.open_workbook(inputExcelName)  # input file name
    except:
        print("Open Error:excel file not exist !")
        
        AddRunLog('error','input string file(xls) open failed !\n', thisFile, sys._getframe().f_lineno) #log record error message
        return 1
    else:
        try:
            table = Data.sheet_by_name('WrnTextTobeGenerated') #input sheet name 
        except:
            print("Open Error:excel file not exist !")
        
            AddRunLog('error','input string file(xls) sheet number not exit !\n', thisFile, sys._getframe().f_lineno) #log record error message
            return 1
        else:
            stringGroupList = []
            for i in range(0, table.ncols): #Find all keyword = "Generate"
                if CellValue(table, 0, i)=="Generate":
                    stringGroupList.append(i)
            for k in stringGroupList:
                ColStart = k
                for i in range(0,table.nrows):
                    if CellValue(table, i,ColStart)=="Generate" or CellValue(table,i,ColStart)=="Tip" or CellValue(table,i,ColStart+1)=="":
                        continue # if the value is Generate or Tip or the string id is empty, this line will be skipped.
                    valueList = []
                    for j in range(ColStart+1,(ColStart+ColNum+1)):
                        valueList.append(CellValue(table, i, j))
                    keyvalue = valueList[0]                        #String Key word
                    if(keyvalue != ErrorValue and keyvalue !=''):  #check the key word whether invaild.
                        if keyvalue[0:0] != '#':                   # key word vaild ,delete key word,in order to filled string don't care string content.
                            del valueList[0]
                            #DEBUG print("valuelist is",valueList)
                            ret = AddWrnString( keyvalue,valueList) #Add string 
                            if(ret):
                                return ret 
                        else:
                            print("Warning:cell(%d,%d) key value invaild!"%(i,j+1-ColNum))
                            AddRunLog('warning','Cell('+str(i+1)+','+str(j+1-ColNum)+') key value invaild ! break1 \n', thisFile, sys._getframe().f_lineno) #log record error message
                    elif keyvalue =='':    #key value equal null,finish string add 
                        break
                    else:
                        print("Warning:cell(%d,%d) key value invaild!"%(i,j+1-ColNum))  
                        AddRunLog('warning','Cell('+str(i+1)+','+str(j+1-ColNum)+') key value invaild ! break2 \n', thisFile, sys._getframe().f_lineno) #log record error message
                    # Data.close()
    return 0

def startToGenerate():
    global dom 
    global root 
    impl = xml.dom.minidom.getDOMImplementation()  
    dom = impl.createDocument(None,'Resources',None)
    root = dom.documentElement
    typeElement = dom.createElement('Type')
    nameTxt = dom.createTextNode('Strings')
    typeElement.appendChild(nameTxt)
    root.appendChild(typeElement)
    ret = ReadExcel()
    if(ret):
        return ret 
    
    f= codecs.open(outputFile, 'w','utf-8')   #if xml encode manner is utf-8,you need open with utf-8 mode.
    dom.writexml(f, addindent='  ', newl='\n',encoding = 'utf-8')  
    f.close
    
    return 0


def Main_GeneratedString(): 
	ret = 0
	try:
		ret = startToGenerate()
	except Exception as e:
		AddRunLog('error',str(e), thisFile, sys._getframe().f_lineno)
		ret = 1
	return ret

if __name__ == "__main__":
	Main_GeneratedString()
