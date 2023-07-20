"""
1.例子源代码 Python 3.x
"""
# -*- coding: UTF-8 -*-
import urllib.request
import re
import sys
import socket
import os


class Spider:
    # init args
    def __init__(self):
        self.timesOfRetry = 1
        self.targetCodeFormat = "gb2312"
        self.debug = True

    # get response data from http request
    def getResponseData(self, url):
        attempts = 0
        success = False
        data = b"0"
        while attempts < self.timesOfRetry and not success:
            try:
                data = urllib.request.urlopen(url).read()
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
        except:
            print("Failed to decode data in getDecodeResponseData!")

    # set args of request, get decoded response data
    def getPage(self, url):
        request = urllib.request.Request(url)
        return self.getDecodeResponseData(request)  # gbk

    # get matched contents
    def getContents(self, url):
        page = self.getPage(url)
        pattern = re.compile(
            '<i class="iTitle"><a target="_blank" href="(.*?)">(.*?)</a></i>', re.S
        )
        items = re.findall(pattern, page)
        contents = []
        for item in items:
            contents.append([item[0], item[1]])
        return contents

    # get the number of imgs in some album
    def getImgNum(self, page):
        try:
            # pattern = re.compile('<li><a href=\'#\'>上一页(.*?)下一页</a></li>',re.S)
            pattern = re.compile('<i class="current">1</i>/(.*?)\)</span>', re.S)
            items = re.findall(pattern, page)
            contents = items[0]
            print(contents)
            return int(contents)
        except Exception as e:
            print(Exception, "in ", sys._getframe().f_code.co_name, ":", e)

    # get the urllist of all imgs in some album
    def getImgUrls(self, detailURL, imgNum):
        contents = detailURL.split(".html")
        urlList = []
        if imgNum > 1:
            urlList.append(detailURL)
            for num in range(2, imgNum + 1):
                urlList.append(contents[0] + "_" + str(num) + ".html")
        return urlList

    # get the url of some img
    def getImg(self, page):
        try:
            pattern = re.compile(
                '<span id="J-BigPic"><img alt=".*?"  src="(.*?)"/></span>', re.S
            )
            items = re.findall(pattern, page)
            print(items)
            if items == []:
                return items
            else:
                return items[0]
        except Exception as e:
            print(Exception, "in ", sys._getframe().f_code.co_name, ":", e)

    # save some img
    def saveImg(self, imageURL, fileName):
        data = self.getResponseData(imageURL)
        f = open(fileName, "wb")
        f.write(data)
        # print(u"正在悄悄保存她的一张图片为",fileName)
        f.close()

    # create new folder if the folder is not exists
    def mkdir(self, path):
        path = path.strip()
        isExists = os.path.exists(path)
        if not isExists:
            # print(u"新建一个文件夹：", path)
            os.makedirs(path)
            return True
        else:
            # print(u"文件夹：", path, u"。已经存在！")
            return False

    # save all imgs in some album
    def saveImgs(self, urlList, path):
        self.mkdir(path)
        num = 1
        for imgUrl in urlList:
            imageDetail = self.getDecodeResponseData(imgUrl)
            image = self.getImg(imageDetail)
            self.saveImg(image, path + "\\" + str(num) + ".jpg")
            num = num + 1

    # save all imgs of all albums
    def savePageInfo(self, url):
        # 1，获取所有相册的URL 名称
        contents = self.getContents(url)
        # 2，循环下载所有相册图片
        for item in contents:
            # print(u"开始下载相册：",item[1])
            detailURL = item[0]
            # 获取相册首页内容
            firstPage = self.getDecodeResponseData(detailURL)
            # 获取相册相片个数
            imgNum = self.getImgNum(firstPage)
            # 获取相册所有图片的网址
            imgUrls = self.getImgUrls(detailURL, imgNum)
            # 保存相册所有图片
            self.saveImgs(imgUrls, item[1])

    # download albums
    def downloadAlbums(self, url):
        try:
            spider.savePageInfo(url)
        except Exception as e:
            print(Exception, "in downloadAlbums:", e)


timeout = 5  # 5
socket.setdefaulttimeout(timeout)
spider = Spider()
pageurl = "http://dp.pconline.com.cn/tour/photo_330_p5.html"
spider.downloadAlbums(pageurl)


"""
2.相关知识点
"""


"""
3.扩展
"""
