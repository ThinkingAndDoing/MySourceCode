#!/usr/bin/python3
# -*- coding: UTF-8 -*-
import re
from robobrowser import RoboBrowser

url = 'http://itest.info/courses/2'
b = RoboBrowser(history=True, parser='html.parser')
b.open(url)

class_name = b.select('.headline h2')
print (class_name[0].text)

class_desc = b.select('.tag-box')
print (class_desc[0].text)

class_time = b.select('h4')
print (class_time[0].text)

teacher = b.select('.thumbnail-style h3')
print (teacher[0].text)

qq = b.find(text=re.compile('QQ'))
print (qq)
