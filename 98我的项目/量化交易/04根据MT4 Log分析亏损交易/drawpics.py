#!/usr/bin/python3
# -*- coding: UTF-8 -*-

import time
import matplotlib.pyplot as plt

import collectorder as co
#将log文件转换为CSV，画出曲线，标记点 done
#在图中加入Label = buy or sell
#将前面数据也打印到图上


# 加这个两句 可以显示中文
plt.rcParams['font.sans-serif'] = [u'SimHei']
plt.rcParams['axes.unicode_minus'] = False
colname = '<CLOSE>'


#_order = {"Ticket":"", "Tradetype":"", "Volumn":"", "Pendingtime":"", "Tradetime":"", "Closetime":""}

def drawCurve(array, legend_=colname, label_="EURUSD"):
    '''
	plt.title("Matplotlib demo") 
	plt.xlabel("x axis caption") 
	plt.ylabel("y axis caption") 
	plt.plot(array.index, array[colname])
	'''
    if label_.find("-")!=-1:
        array.plot(figsize=(12,6), color='red', grid=True, legend=legend_, label=label_)
    else:
        array.plot(figsize=(12,6), color='green', grid=True, legend=legend_, label=label_)

def getRangeY(df, curOrder):
    theMinY = min(float(df.loc[curOrder["Pendingtime"]]["<CLOSE>"]), float(df.loc[curOrder["Tradetime"]]["<CLOSE>"]), float(df.loc[curOrder["Closetime"]]["<CLOSE>"]))
    theMaxY = max(float(df.loc[curOrder["Pendingtime"]]["<CLOSE>"]), float(df.loc[curOrder["Tradetime"]]["<CLOSE>"]), float(df.loc[curOrder["Closetime"]]["<CLOSE>"]))
    return (theMinY, theMaxY)
    
def getPreTime(curtime, shifttime = 20):
    timestamp = time.mktime(time.strptime(curtime,"%Y%m%d %H:%M:%S"))
    return time.strftime("%Y%m%d %H:%M:%S", time.localtime(timestamp - shifttime*60))

def draw(df, curOrder):
    print(curOrder)
    print("Pendingtime："+curOrder["Pendingtime"]+", Closetime："+curOrder["Closetime"])
    #print(df)
    
    strEC = 'g'
    profit = 0
    suffixOfLabel = ""
    if curOrder["Tradetype"]=="buy":
        strEC = 'b'
        suffixOfLabel = "Buy"
        profit=round(df.loc[curOrder["Closetime"]]["<CLOSE>"] - df.loc[curOrder["Tradetime"]]["<CLOSE>"], 5)
    elif curOrder["Tradetype"]=="sell":
        strEC = 'r'
        suffixOfLabel = "Sell"
        profit=round(df.loc[curOrder["Tradetime"]]["<CLOSE>"] - df.loc[curOrder["Closetime"]]["<CLOSE>"], 5)
    df = df.loc[getPreTime(curOrder["Pendingtime"]):curOrder["Closetime"]]
    drawCurve(df[colname], "X", suffixOfLabel+", profit=%.5f" % profit)
    #plt.ylim(getRangeY(df, curOrder))
    plt.scatter(list(df.index.values).index(curOrder["Pendingtime"]), df.loc[curOrder["Pendingtime"]]["<CLOSE>"], marker='o', c='', edgecolors=strEC)
    plt.scatter(list(df.index.values).index(curOrder["Tradetime"]), df.loc[curOrder["Tradetime"]]["<CLOSE>"], marker='o', c='', edgecolors=strEC)
    plt.scatter(list(df.index.values).index(curOrder["Closetime"]), df.loc[curOrder["Closetime"]]["<CLOSE>"], marker='o', c='', edgecolors=strEC)
    plt.savefig("pics\\"+curOrder["Ticket"]+'.png',bbox_inches='tight')
    #plt.show()
    plt.clf()

if __name__=="__main__":

    dictOrders = co.collectOrder("20190708.log")
    listOrders = co.analyzeOrder(dictOrders)
    #print(_orderList[0])
    #exit()
    
    df = co.loadHistoryFromLocal('EURUSD.txt')
    for curOrder in listOrders[:10]:
    #for curOrder in listOrders:
        draw(df, curOrder)
        try:
            pass
            #draw(df, curOrder)
        except:
            print("Exception!Please check!")
	