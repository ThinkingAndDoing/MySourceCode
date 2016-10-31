#!/usr/bin/python
# -*- coding: UTF-8 -*- 

import os
import sys

#numeric character reference（NCR）
def NCRtoStr(originStr):
    originStr=originStr.replace(";","")
    list=originStr.split("&#")
    distStr=""
    for i in list:
        if i!="":
            distStr=distStr+(chr(int(i)))
    return distStr

content="&#20013;&#22269;"
print('The converted string is '+NCRtoStr(content))
