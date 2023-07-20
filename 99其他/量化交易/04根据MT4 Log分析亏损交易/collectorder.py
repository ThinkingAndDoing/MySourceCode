#!/usr/bin/python3
# -*- coding: UTF-8 -*-

import os
import re
import pandas as pd
import numpy as np

# _order = {"Ticket":"", "Tradetype":"", "Volumn":"", "Pendingtime":"", "Tradetime":"", "Closetime":""}


def loadLogFromLocal(fn):
    f = open(fn, "r")
    data = f.readlines()
    f.close()
    return data


def loadHistoryFromLocal(fn):
    """
    For example:
    <TICKER>,<DTYYYYMMDD>,<TIME>,<OPEN>,<HIGH>,<LOW>,<CLOSE>,<VOL>
    EURUSD,20190125,165700,1.13960,1.13960,1.13960,1.13960,4
    """
    df = pd.read_csv(fn, dtype={"<TIME>": np.str})
    # print(df[960:961])
    del df["<TICKER>"]
    df[["<DTYYYYMMDD>", "<TIME>"]] = df[["<DTYYYYMMDD>", "<TIME>"]].astype(str)
    df["<TIME>"] = df["<TIME>"].map(lambda x: x[:-4] + ":" + x[-4:-2] + ":" + x[-2:])
    df["<TIME>"] = df["<DTYYYYMMDD>"] + " " + df["<TIME>"]
    # df['<TIME>'] = df['<TIME>'].map(lambda x:parse(x))
    del df["<DTYYYYMMDD>"]
    df[["<VOL>"]] = df[["<VOL>"]].astype(int)
    df[["<OPEN>", "<HIGH>", "<LOW>", "<CLOSE>"]] = df[
        ["<OPEN>", "<HIGH>", "<LOW>", "<CLOSE>"]
    ].astype(float)
    df.set_index("<TIME>", inplace=True)
    return df


def addLineToDic(orderDic, oi, data):
    if oi not in orderDic.keys():
        orderDic[oi] = []
    orderDic[oi].append(data)


def collectOrder(fn):
    orderDic = {}

    if os.path.exists(fn):
        lines = loadLogFromLocal(fn)
        for line in lines:
            searchObj = re.search(r".*(?<!modify )(#\d+).*", line, re.M | re.I)
            if searchObj is not None:
                addLineToDic(orderDic, searchObj.group(1), line)
    return orderDic


def analyzeOrder(orderDic):
    orderList = []

    for oi in sorted(orderDic.keys()):
        oneOrder = {}
        for item in orderDic[oi]:
            oneOrder["Ticket"] = oi
            searchObj = re.search(
                "\S+\s+\S+\s+(\S+\s+\S+).*open " + oi, item, re.M | re.I
            )
            if searchObj is not None:
                oneOrder["Pendingtime"] = searchObj.group(1)
                continue
            searchObj = re.search(
                "\S+\s+\S+\s+(\S+\s+\S+).*order " + oi + ", (\w+) (\S+)",
                item,
                re.M | re.I,
            )
            if searchObj is not None:
                oneOrder["Tradetime"] = searchObj.group(1)
                oneOrder["Tradetype"] = searchObj.group(2)
                oneOrder["Volumn"] = searchObj.group(3)
                continue
            searchObj = re.search(
                "\S+\s+\S+\s+(\S+\s+\S+).*close " + oi, item, re.M | re.I
            )
            if searchObj is not None:
                oneOrder["Closetime"] = searchObj.group(1)
                continue
            searchObj = re.search(
                "\S+\s+\S+\s+(\S+\s+\S+).*stop loss " + oi + " at (\S+)",
                item,
                re.M | re.I,
            )
            if searchObj is not None:
                oneOrder["Closetime"] = searchObj.group(2)
                continue
            # print("order["+oi+"] is unknown!"+item)
        if len(oneOrder.keys()) == 6:
            oneOrder["Pendingtime"] = (
                oneOrder["Pendingtime"].replace(".", "")[:-2] + "00"
            )
            oneOrder["Tradetime"] = oneOrder["Tradetime"].replace(".", "")[:-2] + "00"
            oneOrder["Closetime"] = oneOrder["Closetime"].replace(".", "")[:-2] + "00"
            orderList.append(oneOrder)
    return orderList


if __name__ == "__main__":
    fn = "20190708.log"
    theDict = collectOrder(fn)
    theList = analyzeOrder(theDict)
    print(theList[0])
