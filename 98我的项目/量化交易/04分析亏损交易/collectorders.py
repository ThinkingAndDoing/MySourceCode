#!/usr/bin/python3
# -*- coding: UTF-8 -*-

import os
import re

#将log文件转换为CSV，画出曲线，标记点

_orderDic = {}
_orderList = []
#_order = {"订单号":"", "交易类型":"", "交易量":"", "挂单时刻":"", "交易时刻":"", "平仓时刻":""}

def loadFromLocal(fn):
    f = open(fn, "r")
    data = f.readlines()
    f.close()
    return data
    
def addLineToDic(oi, data):
	if oi not in _orderDic.keys():
		_orderDic[oi] = []
	_orderDic[oi].append(data)

def collectRecourds():
	fn = "20190708.log"
	if os.path.exists(fn):
		lines = loadFromLocal(fn)
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
            print("order["+oi+"] is unknown!")
        if len(oneOrder.keys())==6:
            _orderList.append(oneOrder)

def saveToLocal(data, fn="output.txt"):
    f = open(fn, "w")
    f.write(data)
    f.close()
    

if __name__=="__main__":

	collectRecourds()
	analyzeOrder()
	print(_orderList)
    

    
    
    
    
    