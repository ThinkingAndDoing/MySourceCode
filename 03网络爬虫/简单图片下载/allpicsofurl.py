'''
1.Sample Python 3.x
'''
# -*- coding: UTF-8 -*-
import singlephoto
import spider
import re
import logging
logging.basicConfig(level=logging.DEBUG,format='%(asctime)s %(filename)s[line:%(lineno)d] %(levelname)s %(message)s',datefmt='%a, %d %b %Y %H:%M:%S',filename='test.log',filemode='w')

'''
Download all picture with extension png and jpg from a url
'''
class AllPicsOfUrl:
	count = 0

	def __init__(self, retryTimes=5, decodeCode="utf-8", timeOut=5):
		self.imgurls = []
		self.exts = ["png","jpg"]
		self.spider = spider.Spider(retryTimes,decodeCode,timeOut)
		self.getsinglephoto = singlephoto.SinglePhoto(retryTimes,decodeCode,timeOut)

	def setExtsOfPics(self, extensionsList):
		self.exts = extensionsList
	
	def saveImgs(self):
		for img in self.imgurls:
			try:
				self.getsinglephoto.setUrl(img)
				self.getsinglephoto.startDownload()
				self.count += 1
			except:
				print("Can't download pic: " + img)

	def downloadAllPics(self, url):
		
		page = self.spider.getDecodeResponseData(url)
		if page is None:
			return
		
		for ext in self.exts:
			rex = '(http'+ '[^\"\']*?' + ext+')'
			pattern = re.compile(rex,re.S)
			self.imgurls = re.findall(pattern,page)
			self.saveImgs()
		
		print("%d pics are download!"%self.count)


'''
2.Reference
'''











'''
3.Extension

'''


