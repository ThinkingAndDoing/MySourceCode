#!/usr/bin/python3
# -*- coding: UTF-8 -*-

import re

def printReS():
    #将从被替换文字中匹配到的内容，作为替换后内容的一部分
    text = 'Today is 11/27/2018. PyCon starts 3/13/2018.'
    print(re.sub(r'(\d+)/(\d+)/(\d+)', r'\3-\1-\2', text))

    #贪婪与非贪婪匹配
    text = 'aa<div>test1</div>bb<div>test2</div>cc'
    print(re.sub(r'(<div>.*</div>)', '', text)) #贪婪
    print(re.sub(r'<div>.*?</div>', '', text)) #非贪婪
    
if __name__=="__main__":
    
    printReS()
