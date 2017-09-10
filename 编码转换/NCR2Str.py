'''
1.例子源代码 Python 3.x
'''
# -*- coding: UTF-8 -*-

import os
import sys

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

if __name__=="__main__":
	print(mixNcrtoStr("你好吗？&#20013;&#22269;"))



'''
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
'''












'''
3.扩展
'''

