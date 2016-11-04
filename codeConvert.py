#!/usr/bin/python
# -*- coding: UTF-8 -*- 

import os
import sys
from langconv import *

def simple2tradition(line):
    #将简体转换成繁体  
    #line = Converter('zh-hant').convert(line.decode('utf-8'))
    line = Converter('zh-hant').convert(line)
    #line = line.encode('gbk')
    return line

def tradition2simple(line):
    # 将繁体转换成简体
    line = Converter('zh-hans').convert(line.decode('utf-8'))
    line = line.encode('utf-8')
    return line

def mixNcrtoStr(str):
    #NCR 字符转换为字符串
    i=0
    distStr=""
    while(i<len(str)-7):
        if str[i]=='&' and str[i+1]=='#' and str[i+2]>='0' and str[i+2]<='9' and str[i+6]>='0' and str[i+6]<='9':
            distStr = distStr + (chr(int(str[i+2:i+7])))
            i = i +8
        else:
            distStr = distStr + str[i]
            i = i +1
    while(i<len(str)):
        distStr = distStr + str[i]
        i = i+1
    return distStr


content="你好吗中国"
print('The converted string is '+simple2tradition(content))
print(mixNcrtoStr("你好吗？&#20013;&#22269;"))
