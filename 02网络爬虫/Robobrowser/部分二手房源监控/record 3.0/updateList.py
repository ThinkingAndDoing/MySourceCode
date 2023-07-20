#!/usr/bin/python3
# -*- coding: UTF-8 -*-

import re
import os
from robobrowser import RoboBrowser

_FileName = "urllist.txt"
_StartUrlList = [
    "http://esf.nanjing.fang.com/house-a0268-b020963/c2130-d2190-g23-j270-k290-l3100/",
    "http://esf.nanjing.fang.com/house-a0268-b02891/c2130-d2190-g23-j270-k290-l3100/",
    "http://esf.nanjing.fang.com/house-a0268-b0601/c2130-d2190-g23-j270-k290-l3100/",
    "http://esf.nanjing.fang.com/house-a0268-b0606/c2130-d2190-g23-j270-k290-l3100/",
]


def getUrlList(fn):
    f = open(fn, "r", encoding="utf-8")
    urlList = f.read().split("\n")
    f.close()
    return urlList


def has_logr(tag):
    """
    http://nj.58.com/zufang/	content = b.find_all(has_logr)
    http://zu.nanjing.fang.com/house-a0268/	content = b.find_all(class_='info rel')
    http://nj.ganji.com/fang1/	content = b.find_all(class_='f-list-item')
    """
    return tag.has_attr("logr")


def writeListToFile(file, list):
    list.sort()
    while "" in list:
        list.remove("")
    f = open(file, "w", encoding="utf-8")
    for item in list:
        f.write(str(item) + "\n")
    f.close()


def readList(url):
    user_agent = (
        "Mozilla/5.0 (Windows NT 10.0; WOW64; rv:47.0) Gecko/20100101 Firefox/47.0"
    )
    b = RoboBrowser(history=True, user_agent=user_agent, parser="html.parser")

    listOutput = []
    while url != "":
        b.open(url)
        print(url)
        # get url list
        content = b.select('dt[class="img rel floatl"] a')
        for link in content:
            listOutput.append("http://esf.nanjing.fang.com" + link.get("href"))
        # get the url of the next page
        url = ""
        nextPage = b.find_all("a", id="PageControl1_hlk_next")
        for link in nextPage:
            url = "http://esf.nanjing.fang.com" + link.get("href")
    return listOutput


def mergeList(listA, listB):
    mergedlist = list(set(listA).union(set(listB)))
    return mergedlist


def updateUrlList():
    newList = []
    for starturl in _StartUrlList:
        templ = readList(starturl)
        newList = mergeList(templ, newList)
    oldList = getUrlList(_FileName)
    mergedlist = list(set(newList).union(set(oldList)))
    writeListToFile(_FileName, mergedlist)


if __name__ == "__main__":
    updateUrlList()
