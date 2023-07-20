# -*- coding: UTF-8 -*-
import spider
import re
import json
import logging
import time
import os


"""
input: album url list
output: albumset
"""

g_albumset = "albumset"

logging.basicConfig(
    level=logging.WARNING, format="%(message)s", filename="test.log", filemode="a"
)


def writeJson(fn, js):
    try:
        with open(fn, "w") as f:
            json.dump(js, f, indent=4, ensure_ascii=False)
    except:
        with open(str(time.time()), "w") as f:
            json.dump(js, f, indent=4, ensure_ascii=False)


def readJson(fn):
    with open(fn, "r") as f:
        data = json.load(f)
        return eval(str(data))


class Albumset:
    def __init__(self, list):
        self.urllist = list

    def saveInfoForAlbum(self, url):
        # print(url)
        theSpider = spider.Spider(5, "utf-8", 5)
        page = theSpider.getDecodeResponseData(url)

        theTitle = ""
        if page is not None:
            rex = "([^>]*?)</h1>"
            pattern = re.compile(rex, re.S)
            list = re.findall(pattern, page)
            if list == []:
                logging.warning(url)
                return
            else:
                theTitle = list[0].replace("?", " ").replace("!", " ").replace("*", "")
            # print(theTitle)

            rex = '<img src="([^"]*?)" border="0" onclick="if\(this.width>=1280\) window.open\('
            pattern = re.compile(rex, re.S)
            urllist = re.findall(pattern, page)
            # print(urllist)

            theDict = {}
            theDict["title"] = theTitle
            theDict["urllist"] = urllist
            print(theDict)
            writeJson(g_albumset + "\\" + theDict["title"] + ".json", theDict)
        else:
            print("Can't open url:" + url)

    def paraseSource(self, src):
        theSpider = spider.Spider(5, "utf-8", 5)
        page = theSpider.getDecodeResponseData(src)
        if page is not None:
            rex = '<a href="([^"]*?)" target="_blank" id="[^"]*?" class="subject">[^<]*?</a>&nbsp;'
            pattern = re.compile(rex, re.S)
            list = re.findall(pattern, page)
            for url in list:
                self.saveInfoForAlbum("http://xxx/" + url)
        else:
            print("Can't open url:" + src)

    def createAlbumset(self):
        if os.path.exists(g_albumset) == False:
            os.makedirs(g_albumset)

        for src in self.urllist:
            self.paraseSource(src)
