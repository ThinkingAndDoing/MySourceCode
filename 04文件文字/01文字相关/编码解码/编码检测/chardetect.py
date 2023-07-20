#!/usr/bin/python3
# -*- coding: UTF-8 -*-
# 1.字符串在python内部中是采用unicode的编码方式，所以其他语言先decode转换成unicode编码，再encode转换成utf8编码。
# 2.utf-8包含国际上所有字符的编码,GBK主要包含全部中文字符，所以说我们大家爱用utf-8，因为全。所以说utf-8中有一些字符，gbk没有，所以有一些Utf-8解码后再编码成gbk后会报错，因为gbk没有那种字符。
# 3.decode('utf-8','ignore'),encode('utf-8','ignore') 加一个'ignore'参数  就会忽略错误。
# 4.Unicode只是一个符号集，它规定了符号的二进制代码，却没有规定二进制代码如何存储。

import chardet


def getcharencode(filename):
    file = open(filename, "rb")  # 要有"rb"，如果没有这个的话，默认使用gbk读文件。
    buf = file.read()
    file.close()
    result = chardet.detect(buf)
    return result["encoding"]


if __name__ == "__main__":
    getcharencode("base\\test.py")
    getcharencode("base\\test.txt")
    getcharencode("base\\BCompare.exe")
