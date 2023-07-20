"""
1.例子源代码 Python 3.x
"""
# -*- coding: UTF-8 -*-

import os
import sys
from langconv import *


def simple2tradition(line):
    # 将简体转换成繁体
    # line = Converter('zh-hant').convert(line.decode('utf-8'))
    line = Converter("zh-hant").convert(line)
    # line = line.encode('gbk')
    return line


def tradition2simple(line):
    # 将繁体转换成简体
    line = Converter("zh-hans").convert(line.decode("utf-8"))
    line = line.encode("utf-8")
    return line


if __name__ == "__main__":
    content = "你好吗中国"
    print("The converted string is " + simple2tradition(content))


"""
2.相关知识点

形如——
&#dddd;
&#xhhhh;
&#name;
——的一串字符是 HTML、XML 等 SGML 类语言的转义序列（escape sequence）。它们不是「编码」。

以 HTML 为例，这三种转义序列都称作 character reference：
•前两种是 numeric character reference（NCR），数字取值为目标字符的 Unicode code point；以「&#」开头的后接十进制数字，以「&#x」开头的后接十六进制数字。
•后一种是 character entity reference，后接预先定义的 entity 名称，而 entity 声明了自身指代的字符。

从 HTML 4 开始，NCR 以 Unicode 为准，与文档编码无关。

「中国」二字分别是 Unicode 字符 U+4E2D 和 U+56FD，十六进制表示的 code point 数值「4E2D」和「56FD」就是十进制的「20013」和「22269」。所以——
&#x4e2d;&#x56fd;
&#20013;&#22269;
——这两种 NCR 写法都会在显示时转换为「中国」二字。
"""


"""
3.扩展
"""
