"""
Created on Sep 23, 2016

@author: uidp8103
"""

import xlrd
import sys
import io
import os
import xlwt
import stringfuzzmatch


def initGlobalVar():
    global _OutputFile
    global _SourceFile1
    global _SourceFile2
    global _SheetName

    _OutputFile = ".\\output.xls"
    _SourceFile1 = ".\\old.xlsx"
    _SourceFile2 = ".\\new.xlsx"
    _SheetName = "Res"


def removeSpace(list):
    for num in range(0, list.count("")):
        list.remove("")


def openWorkBook():
    try:
        book1 = xlrd.open_workbook(_SourceFile1)
        sheet1 = book1.sheet_by_name(_SheetName)
        book2 = xlrd.open_workbook(_SourceFile2)
        sheet2 = book2.sheet_by_name(_SheetName)
    except Exception as e:
        print("Exception:", e)
        sys.exit()
    else:
        matchlist = readSheets(sheet1, sheet2)
        return matchlist


def readSheets(sheet1, sheet2):
    # 3.read data from input file.
    col_valuesA = []
    for i in range(0, sheet1.ncols):
        if sheet1.cell_value(0, i) == "KeyWord":
            col_valuesA = sheet1.col_values(i)

    col_valuesB = []
    for i in range(0, sheet2.ncols):
        if sheet2.cell_value(0, i) == "KeyWord":
            col_valuesB = sheet2.col_values(i)

    # 4.data collection
    removeSpace(col_valuesA)
    removeSpace(col_valuesB)
    fuzz = stringfuzzmatch.StringFuzzMatch()
    matchedlist = fuzz.fuzzy_match_array(col_valuesA, col_valuesB, -1)
    return matchedlist


def writeWorkBook(matchedlist):
    workbook = xlwt.Workbook()
    sheetOutput = workbook.add_sheet(_SheetName, cell_overwrite_ok=True)
    i = 0
    for item in matchedlist:
        sheetOutput.write(i, 0, item[0])
        sheetOutput.write(i, 1, item[1])
        sheetOutput.write(i, 2, item[2])
        i = i + 1
    workbook.save(_OutputFile)


def run():
    try:
        # 1.init workbook
        initGlobalVar()
        # 2.open input file.
        matchedlist = openWorkBook()
        # 3.output
        writeWorkBook(matchedlist)
    except Exception as e:
        print(e)
    else:
        print("finished!")


run()
