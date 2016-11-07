#!/usr/bin/python
# -*- coding: UTF-8 -*-
import urllib.request
import re
import sys
import socket
import os
import socket

class Spider:        # 定义父类
   timesOfRetry = 5
   targetCodeFormat = 'gbk'
   debug = False
   def __init__(self):
      print("调用父类构造函数")

   def setTargetCodeFormat(self, format):
      Spider.targetCodeFormat = format

   def setDebug(self, debug):
      Spider.debug = debug

   def setTimeout(self, timeout):
      socket.setdefaulttimeout(timeout)

   #function trace
   def traceFunc(self,funName):
      if self.debug == True:
         print("step in "+funName)

   #get response data from http request
   def getResponseData(self,url):
      self.traceFunc(sys._getframe().f_code.co_name)
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
      self.traceFunc(sys._getframe().f_code.co_name)
      try:
         data = self.getResponseData(url)
         dataDecode=data.decode(self.targetCodeFormat)
         return dataDecode
      except Exception as e:
         print(Exception,"in getDecodeResponseData:",e)

   def saveOneImg(self, imageURL, imgName):
      self.traceFunc(self, sys._getframe().f_code.co_name)
      data = self.getResponseData(imageURL)
      f = open(imgName, 'wb')
      f.write(data)
      f.close()

class AnJuKe(Spider): # 定义子类
   def __init__(self):
      print("调用子类构造方法")
      Spider.setTargetCodeFormat(self, "utf-8")
	  #os.chdir()

   def childMethod(self):
      Spider.__init__(self)
      print('调用子类方法 child method')

   def saveDataOfOnePage(self, url):
      data = self.getDataOfOnePage(url)
      f = open("out.txt","w",encoding='utf-8')
      for item in data:
         iss = item[0].split("<em>|</em>")
         for i in iss:
            f.write(i+",")
         f.write(item[1].replace("<strong>","").replace("</strong>",",").replace("\n",""))

   def getDataOfOnePage(self,url):
      Spider.traceFunc(self, sys._getframe().f_code.co_name)

      page = Spider.getDecodeResponseData(self, url)
      pattern = re.compile('<li class="list-item " data-from="">.*?<div class="details-item">(.*?)</div>.*?<span class="price-det">(.*?)</span>',re.S)
      items = re.findall(pattern,page)
      contents = []
      for item in items:
         contents.append([item[0].replace("<span>","").replace("</span>",""),item[1]])
      return contents

   def saveOneImg(self, imageURL, imgName):
      Spider.traceFunc(self, sys._getframe().f_code.co_name)
      data = self.getResponseData(imageURL)
      f = open(imgName, 'wb')
      f.write(data)
      f.close()


c = AnJuKe()          # 实例化子类
url = "http://nanjing.anjuke.com/sale/p2/"
c.saveDataOfOnePage(url)      # 调用子类的方法
