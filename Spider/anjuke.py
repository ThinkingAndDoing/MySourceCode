'''
1.例子源代码 Python 3.x
'''
# -*- coding: UTF-8 -*-
import urllib.request
import re
import sys
import socket
import os
from urllib.parse import quote

#basic class
class Spider:
   def __init__(self, retryTimes=5, decodeCode="gbk", timeOut=5):
      self.timesOfRetry = retryTimes
      self.targetCodeFormat = decodeCode
      socket.setdefaulttimeout(timeOut)

   def encodeUrl(self, url):
      try:
          return quote(url, safe='/:?=')
      except Exception as e:
         print(Exception,"in encodeUrl:",e)

   #get response data from http request
   def getResponseData(self,url):
      url = self.encodeUrl(url)
      attempts = 0
      success = False
      data = b"0"
      while attempts < self.timesOfRetry and not success:
         try:
            headers = { 'User-Agent' : 'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/54.0.2837.0 Safari/537.36' }
            req = urllib.request.Request(url, headers = headers)
            data = urllib.request.urlopen(req).read()
            success = True
         except Exception as e:
            print(Exception,"in getResponseData:",e)
            attempts += 1
      return data

   #get decoded response data
   def getDecodeResponseData(self,url):
      try:
         data = self.getResponseData(url)
         dataDecode=data.decode(self.targetCodeFormat)
         return dataDecode
      except Exception as e:
         print(Exception,"in getDecodeResponseData:",e)

class AnJuKe:
   def __init__(self):
      self.spider = Spider(5, "utf-8", 5)
      self.nextPage = ""

   def saveDataOfOnePage(self, url):
      print(url)
      data = self.getDataOfOnePage(url)
      f = open("out.txt","a",encoding='utf-8')
      for item in data:
         iss = item[0].split("<em>|</em>")
         for i in iss:
            f.write(i+",")
         f.write(item[1].replace("<strong>","").replace("</strong>",",").replace("\n",""))
      if self.nextPage!="":
         self.saveDataOfOnePage(self.nextPage)

   def getDataOfOnePage(self,url):
      page = self.spider.getDecodeResponseData(url)
      pattern = re.compile('<a href="([^\"]*?)" class="aNxt">下一页 &gt;</a>',re.S)
      items = re.findall(pattern,page)
      self.nextPage = items[0]
      pattern = re.compile('<li class="list-item " data-from="">.*?<div class="details-item">(.*?)</div>.*?<span class="price-det">(.*?)</span>',re.S)
      items = re.findall(pattern,page)
      contents = []
      for item in items:
         contents.append([item[0].replace("<span>","").replace("</span>",""),item[1]])
      return contents

   def saveOneImg(self, imageURL, imgName):
      data = self.getResponseData(imageURL)
      f = open(imgName, 'wb')
      f.write(data)
      f.close()

c = AnJuKe()
url = "http://nanjing.anjuke.com/sale/p1/#filtersort"
c.saveDataOfOnePage(url)



'''
2.相关知识点
'''












'''
3.扩展
'''

