#!/usr/bin/python3
# -*- coding: UTF-8 -*-

import execjs


def getJS(jsfile):
    try:
        f = open(jsfile, "r")
        js = f.read()
        ctx = execjs.compile(js)
    except:
        print("Error! Exception in getJS!")
        return None
    else:
        return ctx


jser = getJS("tj.js")
print(jser.call("add", 1, 2))
print(jser.call("sub", 10, 2))
