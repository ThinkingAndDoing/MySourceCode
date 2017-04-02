'''
1.例子源代码 Python 3.x
'''
# -*- coding: UTF-8 -*-
import spider
import os

class Photos:
   def __init__(self):
      self.list = []
      self.distPath = "."
      self.spider = spider.Spider(5,"gbk",5)

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

'''
2.相关知识点
'''












'''
3.扩展
'''
