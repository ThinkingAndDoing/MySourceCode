#!/usr/bin/python3
# -*- coding: UTF-8 -*-

"""
http://www.cnblogs.com/nbkhic/p/4216149.html
"""

import re
from robobrowser import RoboBrowser

url = "https://bitbucket.org/account/signin/"
b = RoboBrowser(history=True, parser="html.parser")
b.open(url)
# 获取登陆表单
login_form = b.get_form(action="/account/signin/")
# 输入用户名和密码
login_form["username"].value = "xiewei23703@163.com"
login_form["password"].value = "***"
b.session.headers["Referer"] = url

# 提交表单
b.submit_form(login_form)
# 打印登陆成功的信息
f = open("output.txt", "w", encoding="utf-8")
f.write(str(b.find("html")))
f.close()
