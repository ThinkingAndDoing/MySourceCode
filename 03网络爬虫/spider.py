'''
1.Sample Python 3.x
'''
# -*- coding: UTF-8 -*-
import socket
import urllib.request
from urllib.parse import quote
import string

#basic class
class Spider:
	def __init__(self, retryTimes=5, decodeCode="gbk", timeOut=5):
		self.timesOfRetry = retryTimes
		self.targetCodeFormat = decodeCode
		socket.setdefaulttimeout(timeOut)

	def encodeUrl(self, url):
		try:
			return quote(url, safe=string.printable)
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
				#headers = { 'User-Agent' : 'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/54.0.2837.0 Safari/537.36' }
				header = {
					'Connection': 'Keep-Alive',
					'Accept': 'text/html, application/xhtml+xml, */*',
					'Accept-Language': 'en-US,en;q=0.8,zh-Hans-CN;q=0.5,zh-Hans;q=0.3',
					'User-Agent': 'Mozilla/5.0 (Windows NT 6.3; WOW64; Trident/7.0; rv:11.0) like Gecko'
				}
				reqconf = urllib.request.Request(url, headers = header)
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
