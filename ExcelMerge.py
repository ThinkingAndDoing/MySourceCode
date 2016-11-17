import xlwt
import xlrd
import os
import sys
from xlutils.copy import copy

def initGlobalVar():
    global _OutputFile
    global _SourceDir
    _OutputFile=getScriptPath() +'\\destination.xls'
    _SourceDir=getScriptPath()+"\\"+"Input"

def getScriptPath():
    #获取脚本路径
    path = sys.path[0]
    if os.path.isdir(path):
        return path
    elif os.path.isfile(path):
        return os.path.dirname(path)

def fileMerge(path, fname):
    try:
        sourcewb = xlrd.open_workbook(path +'\\'+ fname)
        sourcews = sourcewb.sheet_by_name(u'Sheet1')
        distwb = xlrd.open_workbook(_OutputFile)
        distws = distwb.sheet_by_name(u'outcome')  
        wb = copy(distwb)  #修改Excel需要用到xlutils 的 copy
        ws = wb.get_sheet(0) 
    except Exception as e:
        print("Exception:",e)  #若当前Workbook中没有对应的sheet，跳过这个，继续处理后面的
    else:
        print(distws.col_values(0))
        sourcerow = sourcews.nrows
        distrow = distws.nrows  #保存结果的Workbook中第一个sheet的行数
        distcol = distws.ncols
        if distrow == 0: #保存结果的Workbook中第一个sheet是空表，直接将源表copy到目标表
            for i in range(sourcerow):
                ws.write(i,0,sourcews.col_values(0)[i])
                ws.write(i,1,sourcews.col_values(1)[i])
            wb.save(_OutputFile)
            return
        for i in range(sourcerow):
            if sourcews.col_values(1)[i] != "":
                written = False
                for j in range(distrow):
                    if distws.col_values(0)[j] == sourcews.col_values(0)[i]:
                        ws.write(j,distcol,sourcews.col_values(1)[i])
                        written = True
                if written == False:  #如果在目标sheet中没有找到对应的行，将此行加到sheet的最下面
                    ws.write(distrow,0,sourcews.col_values(0)[i])
                    ws.write(distrow,distcol,sourcews.col_values(1)[i])
                    distrow = distrow +1
        wb.save(_OutputFile)

#done
def checkDistWorkbook(distWB):
    try:
        distwb = xlrd.open_workbook(distWB)
        distws = distwb.sheet_by_name(u'outcome')
    except:
        distwb = xlwt.Workbook()
        distws = distwb.add_sheet('outcome')
        distwb.save(distWB)
#done
def filesMerge(path):
    checkDistWorkbook(_OutputFile)
    list = os.listdir(path)
    for fname in list:
        templist = fname.split('.')
        if templist[1] == 'xls' or templist[1] == 'xlsx':
            fileMerge(path, fname)

initGlobalVar()
filesMerge(_SourceDir)



