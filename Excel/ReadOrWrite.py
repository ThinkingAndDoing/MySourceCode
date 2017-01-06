'''
1.例子源代码 Python 3.x
'''
# -*- coding: UTF-8 -*-
import os
import xlwt
import xlrd

os.chdir('C:\\Users\\uidp8103\\Desktop\\TextCompare\\python\\testing')

def initGlobalVar():
    global _OutputFile
    global _SourceFile
    global _SheetName

    _OutputFile='.\\TestCase.xls'
    _SourceFile=".\\Geely_FE6_WarningConfiguration.xlsm"
    _SheetName='WarningConfig'

def getTableIndex(table):
    global indexName
    global indexDisplayMode
    global indexWarningStrategy
    global indexActiveCondition
    global indexDeactiveCondition
	
    keyName = table.row_values(0)
    indexName = keyName.index("Name")
    indexDisplayMode = keyName.index("DisplayMode")
    indexWarningStrategy = keyName.index("WarningStrategy")
    indexActiveCondition = keyName.index("ActiveCondition")
    indexDeactiveCondition = keyName.index("DeactiveCondition")

def generateTestCase(sourceSheet, distSheet):
    getTableIndex(sourceSheet)
    for i in range(1,51):
        Name = sourceSheet.cell(i,indexName).value
        DisplayMode = sourceSheet.cell(i,indexDisplayMode).value
        WarningStrategy = sourceSheet.cell(i,indexWarningStrategy).value
        ActiveCondition = sourceSheet.cell(i,indexActiveCondition).value
        DeactiveCondition = sourceSheet.cell(i,indexDeactiveCondition).value
        
        distSheet.write(i, 0, Name+"_"+WarningStrategy)
        #distSheet.write(i, 1, sourceSheet.cell(i,indexDisplayMode).value)
        #distSheet.write(i, 2, sourceSheet.cell(i,indexWarningStrategy).value)
        inputSteps = "1."+"IgnOff, " + ActiveCondition + ", wait for 10s" + "\n"
        inputSteps += "2." + DeactiveCondition + "\n"
        inputSteps += "3."+"IgnOn, " + ActiveCondition + ", wait for 10s" + "\n"
        inputSteps += "4." + DeactiveCondition + "\n"
        distSheet.write(i, 3, inputSteps)
        WarningStrategy = WarningStrategy.replace("Pos", "")
        WarningStrategy = WarningStrategy.replace("WSTT", "Position")
        if DisplayMode=="IgnOFF" or DisplayMode=="IgnOFF_IgnON":
            expectResult = "1."+"The telltale " + Name + " will be displayed on screen in "+ WarningStrategy +" for 10s" + "\n"
            expectResult += "2."+"The telltale " + Name + " will disappear immediately" + "\n"
        else:
            expectResult = "1."+"The telltale " + Name + " will not be displayed" + "\n"
            expectResult += "2."+"No changes on screen" + "\n"
        if DisplayMode=="IgnON" or DisplayMode=="IgnOFF_IgnON":
            expectResult += "3."+"The telltale " + Name + " will be displayed on screen in "+ WarningStrategy +" for 10s" + "\n"
            expectResult += "4."+"The telltale " + Name + " will disappear immediately" + "\n"
        else:
            expectResult += "3."+"The telltale " + Name + " will not be displayed" + "\n"
            expectResult += "4."+"No changes on screen" + "\n"
        distSheet.write(i, 5, expectResult)


initGlobalVar()
try:
    sourcewb = xlrd.open_workbook(_SourceFile)
    sourcews = sourcewb.sheet_by_name(_SheetName)
    distwb = xlwt.Workbook()
    distws = distwb.add_sheet('WarningTestCase',cell_overwrite_ok=True)
except:
    print("Exception:",e)
else:
    generateTestCase(sourcews,distws)
    distwb.save(_OutputFile)

'''
2.相关知识点


特殊用例：

步骤：
1，触发AVASState，等待10s
2，触发PHEVModeEV，等待10s
3，触发PHEVModeHEV，等待20s
预期结果：
1，AVASState一直显示10s
2，AVASState显示4s后显示PHEVModeEV，PHEVModeEV显示4s后再显示AVASState，一直循环
3，AVASState显示2s后，按照PHEVModeHEV，AVASState，PHEVModeEV的顺序4s循环显示

步骤：
1.触发报警灯HighCoolantTemp，等待10s
2.取消报警灯HighCoolantTemp
期望结果：
1.报警灯HighCoolantTemp一直在屏幕上Position3闪烁显示，闪烁频率是1Hz
2.报警灯HighCoolantTemp立刻在屏幕上消失

步骤：
1.IgnOn，触发报警灯PositionLight，等待10s
2.IgnOff，等待10s
3.取消报警灯PositionLight
4.触发报警灯PositionLight，等待10s
5.IgnOn，等待10s
6.取消报警灯PositionLight
期望结果：
1.报警灯PositionLight显示10s
2.报警灯PositionLight继续显示10s
3.报警灯PositionLight消失
4.报警灯PositionLight在屏幕上显示10s
5.报警灯PositionLight继续显示10s
6.报警灯PositionLight消失

'''












'''
3.扩展
'''

