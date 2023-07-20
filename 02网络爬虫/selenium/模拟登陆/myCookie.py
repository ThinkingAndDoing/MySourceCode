#!/usr/bin/env python
# -*- coding: utf-8 -*-

import urllib.request, urllib.parse, urllib.error
import http.cookiejar
import time


class Login:
    def __init__(self):
        self.cookie = http.cookiejar.MozillaCookieJar("cookie.txt")
        # self.cookie = http.cookiejar.CookieJar()
        self.headers = {
            "User-Agent": "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/44.0.2403.157 Safari/537.36",
            "Connection": "keep-alive",
        }

        handler = urllib.request.HTTPCookieProcessor(self.cookie)
        self.opener = urllib.request.build_opener(handler)
        self.request = None

    def getHeader(self):
        return self.headers

    def getHeaderEncoded(self):
        data = urllib.parse.urlencode(self.headers).encode()
        return data

    def setRequest(self, req):
        self.request = req

    def saveCookie(self):
        self.cookie.save(
            ignore_discard=True, ignore_expires=True
        )  # 保存cookie到cookie.txt中
        for item in self.cookie:
            print(item.name + ":" + item.value)

    def openUrl(self):
        try:
            response = self.opener.open(self.request)
            page = response.read().decode()
            # print(page)
            writeToFile(page)
            return page
        except urllib.error.URLError as e:
            print(e.code, ":", e.reason)


def writeToFile(page, fileName="login.html"):
    f = open(fileName, "w", encoding="utf-8")
    f.write(page)
    f.close()


login = Login()
values = {
    "user": "17625938664",
    "password": "***",
    "_xsrf": "ee0b2fa0f2aa598655d3d92b2da4f2bf",
}  #'submit' : 'Login'
postdata = urllib.parse.urlencode(values).encode()
request = urllib.request.Request(
    "https://www.zhihu.com/#signin", postdata, login.getHeader(), method="PUT"
)
login.setRequest("https://www.zhihu.com/#signin")
login.openUrl()
login.saveCookie()

"""
time.sleep(3)

get_url = 'https://www.zhihu.com/question/60702820/answer/179426781'  # 利用cookie请求访问另一个网址
get_request = urllib.request.Request(get_url, headers=login.getHeader())
login.setRequest(get_request)
login.openUrl()
login.saveCookie()
"""


"""
import urllib.request, urllib.parse, urllib.error
import http.cookiejar

cookie_filename = 'cookie.txt'
cookie = http.cookiejar.MozillaCookieJar(cookie_filename)
cookie.load(cookie_filename, ignore_discard=True, ignore_expires=True)
print(cookie)
handler = urllib.request.HTTPCookieProcessor(cookie)
opener = urllib.request.build_opener(handler)

get_url = 'http://acm.hit.edu.cn/hoj/problem/solution/?problem=1'  # 利用cookie请求访问另一个网址
get_request = urllib.request.Request(get_url)
get_response = opener.open(get_request)
print(get_response.read().decode())
"""
