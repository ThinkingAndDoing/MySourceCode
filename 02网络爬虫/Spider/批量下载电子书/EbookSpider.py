"""
1.例子源代码 Python 3.x
"""
# -*- coding: UTF-8 -*-
import urllib.request
import re
import sys
import socket
import os
import http.cookiejar
import logging
from urllib.parse import quote

logging.basicConfig(
    level=logging.DEBUG,
    format="%(asctime)s %(filename)s[line:%(lineno)d] %(levelname)s %(message)s",
    datefmt="%a, %d %b %Y %H:%M:%S",
    filename="test.log",
    filemode="w",
)


# basic class
class Spider:
    def __init__(self, retryTimes=5, decodeCode="gbk", timeOut=5):
        self.timesOfRetry = retryTimes
        self.targetCodeFormat = decodeCode
        socket.setdefaulttimeout(timeOut)

    def encodeUrl(self, url):
        try:
            return quote(url, safe="/:?=")
        except Exception as e:
            print(Exception, "in encodeUrl:", e)

    # get response data from http request
    def getResponseData(self, url):
        url = self.encodeUrl(url)
        attempts = 0
        success = False
        data = b"0"
        while attempts < self.timesOfRetry and not success:
            try:
                headers = {
                    "User-Agent": "Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/54.0.2837.0 Safari/537.36"
                }
                req = urllib.request.Request(url, headers=headers)
                data = urllib.request.urlopen(req).read()
                success = True
            except Exception as e:
                print(Exception, "in getResponseData:", e)
                attempts += 1
        return data

    # get decoded response data
    def getDecodeResponseData(self, url):
        try:
            data = self.getResponseData(url)
            dataDecode = data.decode(self.targetCodeFormat)
            return dataDecode
        except Exception as e:
            print(Exception, "in getDecodeResponseData:", e)


# basic class
class GetText:
    def __init__(self):
        self.url = ""
        self.fileName = ""
        self.pattern = ""
        self.spider = Spider()

    def setPattern(self, Pattern):
        self.pattern = Pattern

    def setUrlAndFilename(self, textUrl, filename):
        self.url = textUrl
        self.fileName = filename

    def getDataOfOnePage(self, url):
        page = self.spider.getDecodeResponseData(url)
        items = re.findall(self.pattern, page)
        return items[0]

    def saveDataOfOnePage(self, url, filename):
        try:
            data = self.getDataOfOnePage(url)
            f = open(filename + ".txt", "w", encoding="utf-8")
            f.write(data)
        except Exception as e:
            print(e)
            print("Exception! File can't be save at " + url)

    def startDownload(self):
        self.saveDataOfOnePage(self.url, self.fileName)


class Traverse:
    def __init__(self):
        self.website = "http://www.gulongbbs.com/"
        self.fileName = ""
        self.thisPage = ""
        self.nextPage = ""
        self.spider = Spider()

    def readFilename(self, url):
        page = self.spider.getDecodeResponseData(url)
        pattern = re.compile(
            'main_ArticleTitle style="WORD-BREAK: break-all"><h3>(.*?)</h3>', re.S
        )
        title = re.findall(pattern, page)
        self.fileName = title[0]

    def readPage(self, url):
        self.thisPage = url
        self.readFilename(url)
        page = self.spider.getDecodeResponseData(url)
        pattern = re.compile("<a class='LinkNextArticle' href='([^']*?)'", re.S)
        items = re.findall(pattern, page)
        if items != []:
            if items[0] != "":
                if self.website + items[0] == url:
                    self.nextPage = ""
                else:
                    self.nextPage = self.website + items[0]
        else:
            logging.debug("Next page is not found!")


if __name__ == "__main__":
    url = "http://www.gulongbbs.com/jinyong/sdyxz/2867.htm"
    contentPattern = re.compile(
        '<span style="font-size:14px;line-height:25px;" zzz=".*?">(.*?)</table><div style="LINE-HEIGHT: 5px">',
        re.S,
    )
    t = Traverse()
    gt = GetText()
    while url != "":
        print(url)
        t.readPage(url)
        if t.fileName != "" and t.thisPage != []:
            gt.setPattern(contentPattern)
            gt.setUrlAndFilename(t.thisPage, t.fileName)
            gt.startDownload()
        url = t.nextPage
    print("抓取完成！")


"""
2.相关知识点
print(sys.getfilesystemencoding())
"""


"""
3.扩展
python 高级教程
http://www.liaoxuefeng.com/wiki/0014316089557264a6b348958f449949df42a6d3a2e542c000/001431917715991ef1ebc19d15a4afdace1169a464eecc2000
"""
