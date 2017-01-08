'''
1.例子源代码 Python 3.x
'''
# -*- coding: UTF-8 -*-
import urllib.request
import re
import sys
import socket
import os
import http.cookiejar
import logging
from urllib.parse import quote
logging.basicConfig(level=logging.DEBUG,format='%(asctime)s %(filename)s[line:%(lineno)d] %(levelname)s %(message)s',datefmt='%a, %d %b %Y %H:%M:%S',filename='test.log',filemode='w')

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

#test passed!
class Traverse:
   def __init__(self):
      self.website = "http://www.mmkao.net/XiuRen/201610/"
      self.imgPath = ""
      self.imgList = []
      self.nextPage = ""
      self.spider = Spider(5,"gbk",5)

   def readPathAndImgs(self,url):
      page = self.spider.getDecodeResponseData(url)
      pattern = re.compile('<title>(.*?)</title>',re.S)
      title = re.findall(pattern,page)
      self.imgPath = title[0]
      pattern = re.compile('<img src="([^"]*?)" alt="[^"]*?" />',re.S)
      self.imgList = re.findall(pattern,page)

   def readPage(self, url):
      self.readPathAndImgs(url)
      page = self.spider.getDecodeResponseData(url)
      pattern = re.compile('<a href="([^\"]*?)">下一页</a>',re.S)
      items = re.findall(pattern,page)
      if items!=[]:
         if items[0]!="":
            if self.website+items[0]==url:
               self.nextPage = ""
            else:
               self.nextPage = self.website+items[0]
      else:
         logging.debug("Next page is not found!")

url = "http://www.mmkao.net/XiuRen/201610/12074.html"
t = Traverse()
f = open("out.txt","a",encoding='utf-8')
imgs = ""
t.readPage(url)
imgs += t.imgPath+ "--" + "".join(t.imgList).replace("\r","")
url = t.nextPage
while url!="":
    print(url)
    t.readPage(url)
    if t.imgPath!="" and t.imgList!=[]:
        imgs += "".join(t.imgList).replace("\r","")
    else:
        print("path or imglist is empty")
        print(t.imgPath)
        print(t.imgList)
    url = t.nextPage
imgs += "\n"
f.write(imgs)
f.close()
print("抓取完成！")


'''
2.相关知识点
'''











'''
3.扩展
python 高级教程
http://www.liaoxuefeng.com/wiki/0014316089557264a6b348958f449949df42a6d3a2e542c000/001431917715991ef1ebc19d15a4afdace1169a464eecc2000
'''



