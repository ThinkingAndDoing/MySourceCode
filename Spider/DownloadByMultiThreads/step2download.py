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
import threading
from urllib.parse import quote
from time import ctime,sleep
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

#basic class
class GetPhotos:
   def __init__(self):
      self.list = []
      self.distPath = "."
      self.spider = Spider(5,"gbk",5)

   def setUrlList(self,urls):
      self.list = urls

   def setUrlListAndPath(self,urls,path):
      self.list = urls
      self.distPath = path

   def mkdir(self,path):
      path = path.strip()
      isExists=os.path.exists(path)
      if not isExists:
         os.makedirs(path)
         return True
      else:
         return False

   def saveImg(self,imageURL,fileName):
      print(imageURL)
      data = self.spider.getResponseData(imageURL)
      f = open(fileName, 'wb')
      f.write(data)
      f.close()

   def saveImgs(self,urlList,path):
      self.mkdir(path)
      num=1
      for imgUrl in urlList:
         if imgUrl!="":
            self.saveImg(imgUrl,path+"\\"+str(num)+".jpg")
            num = num+1

   def startDownload(self):
      self.saveImgs(self.list,self.distPath)

def downloadList(list):
    try:
        gp = GetPhotos()
        for i in list:
            if i=="":
                continue
            logging.debug("break 1")
            args = i.split("--")
            imgurls = []
            templist = args[1].split("http:")
            for j in templist:
                if j!="":
                    imgurls.append("http:"+j)
            if args[0]=="" or os.path.exists(args[0].strip()):
                print("The folder is aready created ! Skip.")
                continue
            logging.debug("break 2")
            if imgurls!=[]:
                logging.debug("break 3")
                gp.setUrlListAndPath(imgurls, args[0])
                gp.startDownload()
    except Exception as e:
        print(Exception,"in downloadList:",e)

f = open("out.txt","r",encoding='utf-8')
data = f.read()
inputList = data.split("\n")

threadsNum = 1
subLen = int(len(inputList)/threadsNum)
threads = []
for i in range(0,threadsNum):
    if i!=threadsNum-1:
        t = threading.Thread(target=downloadList,args=(inputList[i*subLen:i*subLen+subLen],))
    else:
        t = threading.Thread(target=downloadList,args=(inputList[i*subLen:len(inputList)],))
    threads.append(t)

if __name__ == '__main__':
    for t in threads:
        t.setDaemon(True)
        t.start()
    t.join()  # wait all threads.
    print("all over %s" %ctime())


'''
2.相关知识点
'''












'''
3.扩展
'''
