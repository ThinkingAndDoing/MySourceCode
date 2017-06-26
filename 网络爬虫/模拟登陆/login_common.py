#!/usr/bin/python3
# -*- coding: UTF-8 -*-

'''
http://www.cnblogs.com/nbkhic/p/4216149.html
仅仅适用于采用Form登录的网站
button link 跳转
link = browser.find('a')[0]
browser.follow_link(link)
'''

import re
from robobrowser import RoboBrowser

url = 'http://d.teamdoc.cn/TPAMemberLogin.aspx'
b = RoboBrowser(history=True, parser='html.parser')
b.open(url)
# 获取登陆表单
login_form = b.get_form(action='TPAMemberLogin.aspx')
login_form = b.get_forms()[0]
# 输入用户名和密码
login_form['CNameLogin'].value = 'username'
login_form['CPassword'].value = 'password'
# 提交表单
b.submit_form(login_form)
# 打印登陆成功的信息
f = open('output.txt','w',encoding='utf-8')
f.write(str(b.find('html')))
f.close()

