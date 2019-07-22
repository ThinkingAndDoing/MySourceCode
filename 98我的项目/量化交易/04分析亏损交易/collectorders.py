#!/usr/bin/python3
# -*- coding: UTF-8 -*-

import os
import re
import matplotlib.pyplot as plt

import pandas as pd
import numpy as np

#将log文件转换为CSV，画出曲线，标记点

# 加这个两句 可以显示中文
plt.rcParams['font.sans-serif'] = [u'SimHei']
plt.rcParams['axes.unicode_minus'] = False
colname = '<CLOSE>'

_orderDic = {}
_orderList = []
#_order = {"订单号":"", "交易类型":"", "交易量":"", "挂单时刻":"", "交易时刻":"", "平仓时刻":""}

def drawCurve(array, legend_=colname, label_="XAUUSD"):
	array.plot(figsize=(12,6), grid=True, legend=legend_, label=label_)
    
def loadLogFromLocal(fn):
    f = open(fn, "r")
    data = f.readlines()
    f.close()
    return data

def loadHistoryFromLocal(fn):
	df = pd.read_csv(fn,dtype={'<TIME>': np.str})
	#print(df[960:961])
	del df['<TICKER>']
	df[['<DTYYYYMMDD>', '<TIME>']] = df[['<DTYYYYMMDD>', '<TIME>']].astype(str)
	df['<TIME>'] = df['<TIME>'].map(lambda x:x[:-4]+":"+x[-4:-2]+":"+x[-2:])
	df['<TIME>'] = df['<DTYYYYMMDD>']+" "+df['<TIME>']
	#df['<TIME>'] = df['<TIME>'].map(lambda x:parse(x))
	del df['<DTYYYYMMDD>']
	df[['<VOL>']] = df[['<VOL>']].astype(int)
	df[['<OPEN>','<HIGH>','<LOW>','<CLOSE>']] = df[['<OPEN>','<HIGH>','<LOW>','<CLOSE>']].astype(float)
	df.set_index('<TIME>',inplace=True)
	return df
    
def addLineToDic(oi, data):
	if oi not in _orderDic.keys():
		_orderDic[oi] = []
	_orderDic[oi].append(data)

def collectRecourds():
	fn = "20190708.log"
	if os.path.exists(fn):
		lines = loadLogFromLocal(fn)
		for line in lines:
			searchObj = re.search( r'.*(?<!modify )(#\d+).*', line, re.M|re.I)
			if searchObj is not None:
				addLineToDic(searchObj.group(1), line)
        
def analyzeOrder():
    for oi in sorted(_orderDic.keys()):
        oneOrder = {}
        for item in _orderDic[oi]:
            oneOrder["订单号"] = oi
            searchObj = re.search("\S+\s+\S+\s+(\S+\s+\S+).*open "+oi, item, re.M|re.I)
            if searchObj is not None:
                oneOrder["挂单时刻"] = searchObj.group(1)
                continue
            searchObj = re.search("\S+\s+\S+\s+(\S+\s+\S+).*order "+oi+", (\w+) (\S+)", item, re.M|re.I)
            if searchObj is not None:
                oneOrder["交易时刻"] = searchObj.group(1)
                oneOrder["交易类型"] = searchObj.group(2)
                oneOrder["交易量"] = searchObj.group(3)
                continue
            searchObj = re.search("\S+\s+\S+\s+(\S+\s+\S+).*close "+oi, item, re.M|re.I)
            if searchObj is not None:
                oneOrder["平仓时刻"] = searchObj.group(1)
                continue
            searchObj = re.search("\S+\s+\S+\s+(\S+\s+\S+).*stop loss "+oi+" at (\S+)", item, re.M|re.I)
            if searchObj is not None:
                oneOrder["平仓时刻"] = searchObj.group(2)
                continue
            #print("order["+oi+"] is unknown!"+item)
        if len(oneOrder.keys())==6:
            _orderList.append(oneOrder)

def saveToLocal(data, fn):
    f = open(fn, "w")
    f.write(data)
    f.close()
    

if __name__=="__main__":

    collectRecourds()
    analyzeOrder()
    print(_orderList[0])

    curOrder = _orderList[0]
    df = loadHistoryFromLocal('XAUUSD.txt')
    df = df.loc[curOrder["挂单时刻"]:curOrder["平仓时刻"]]
    drawCurve(df[colname], "X", "K")
    plt.show()
    
    
    
    