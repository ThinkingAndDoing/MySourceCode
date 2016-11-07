'''
Created on Sep 23, 2016

@author: uidp8103
'''

import xlrd
import sys
import io
import os
import xlwt
from fuzzywuzzy import fuzz

def get_script_path():
    path = sys.path[0]
    if os.path.isdir(path):
        return path
    elif os.path.isfile(path):
        return os.path.dirname(path)

def removeSpace(list):
    for num in range(0,list.count("")):
        list.remove("")

# fuzzy_match between two strings
def fuzzy_match(stringA, stringB):
    #remove all space, tab and \n
    stringA = stringA.replace('\n', '')
    stringA = stringA.replace(' ', '')
    stringA = stringA.replace('    ', '')
    stringA = stringA.lower()
    stringB = stringB.replace('\n', '')
    stringB = stringB.replace(' ', '')
    stringB = stringB.replace('    ', '')
    stringB = stringB.lower()
    if stringA==stringB:
        print("string matched!")
        return True
    else:
        print("string isn't matched!")
        return False

# fuzzy_match between two strings Array
def fuzzy_match_array(ListA, ListB, matchDegree):
    matchedAtoB = []
    matchedBtoA = []
    for stringA in ListA:
        mostmath=0
        for value in ListB:
            if mostmath<fuzz.ratio(value,stringA):
                mostmath = fuzz.ratio(value,stringA)
        if mostmath>matchDegree:
            for value in ListB:
                if mostmath==fuzz.ratio(value,stringA):
                    matchedAtoB.append([value,stringA,str(mostmath)])
    for stringB in ListB:
        mostmath=0
        for value in ListA:
            if mostmath<fuzz.ratio(value,stringB):
                mostmath = fuzz.ratio(value,stringB)
        if mostmath>matchDegree:
            for value in ListA:
                if mostmath==fuzz.ratio(value,stringB):
                    matchedBtoA.append([stringB,value,str(mostmath)])
    matchedList = [val for val in matchedAtoB if val in matchedBtoA]
    return matchedList

#1.change the default encode of stdout to gb18030(simplified chinese)
sys.stdout = io.TextIOWrapper(sys.stdout.buffer,encoding='gb18030')

#2.open input file.
infile1= get_script_path() + "\\old.xlsx"
infile2= get_script_path() + "\\new.xlsx"
try:
    book1 = xlrd.open_workbook(infile1)
    sheet1 = book1.sheet_by_name("Res")
    book2 = xlrd.open_workbook(infile2)
    sheet2 = book2.sheet_by_name("Res")
except Exception as e:
    print("Exception:",e)
    sys.exit()

#3.read data from input file.
col_valuesA=[]
for i in range(0,sheet1.ncols):
    if sheet1.cell_value(0,i)=="Tobecompaired":
        col_valuesA = sheet1.col_values(i)

col_valuesB=[]
for i in range(0,sheet2.ncols):
    if sheet2.cell_value(0,i)=="Tobecompaired":
        col_valuesB = sheet2.col_values(i)

# fuzz.ratio("this is a test", "this is a test!")
# fuzz.partial_ratio("this is a test", "this is a test!")

#4.data collection
removeSpace(col_valuesA)
removeSpace(col_valuesB)
matchedlist=fuzzy_match_array(col_valuesA,col_valuesB, -1)

#5.output
workbook = xlwt.Workbook()
sheetOutput = workbook.add_sheet('Res',cell_overwrite_ok=True)
i=0
for item in matchedlist:
    sheetOutput.write(i,0,item[0])
    sheetOutput.write(i,1,item[1])
    sheetOutput.write(i,2,item[2])
    i = i+1
workbook.save(get_script_path()+'\\output.xls')
print('finished!')


