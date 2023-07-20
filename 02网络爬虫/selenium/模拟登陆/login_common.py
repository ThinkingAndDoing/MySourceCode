#!/usr/bin/python3
# -*- coding: UTF-8 -*-

"""
http://www.cnblogs.com/nbkhic/p/4216149.html
仅仅适用于采用Form登录的网站
button link 跳转
link = browser.find('a')[0]
browser.follow_link(link)
打印对象
print (object .__dict__)
print (dir(object))
"""

import re
import requests
from robobrowser import RoboBrowser


def login(url, username, password):
    # cookie={'sc_device_auth':'abcdef'}
    session = requests.Session()
    user_agent = (
        "Mozilla/5.0 (Windows NT 10.0; WOW64; rv:47.0) Gecko/20100101 Firefox/47.0"
    )

    browser = RoboBrowser(
        history=True, session=session, user_agent=user_agent, parser="html.parser"
    )
    browser.open(url, method="post")
    form = browser.get_form(action="TPAMemberLogin.aspx")
    # print (form.__dict__)

    form["CNameLogin"] = username
    form["CPassword"] = password
    browser.session.headers.update(
        {
            "Referer": url,
            "Accept": "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8",
            "Accept-Language": "en-US,en;q=0.5",
        }
    )
    # browser.session.cookies.update(cookie)
    browser.submit_form(form)
    # print(browser.session.cookies.__dict__)
    f = open("output.txt", "w", encoding="utf-8")
    f.write(str(browser.find("html")))
    f.close()


login("http://d.teamdoc.cn/TPAMemberLogin.aspx", "username", "password")
