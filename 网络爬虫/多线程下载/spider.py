'''
1.Sample Python 3.x
'''
# -*- coding: UTF-8 -*-
import socket
import urllib.request
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
            reqconf = urllib.request.Request(url, headers = headers)
            request = urllib.request.urlopen(reqconf)
            data = request.read()
            request.close()
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
