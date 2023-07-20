#!/usr/bin/python3
# -*- coding: UTF-8 -*-

import chardet


def getcharencode(filename):
    file = open(filename, "rb")
    buf = file.read()
    file.close()
    result = chardet.detect(buf)
    return result["encoding"]


def loadFromLocal(fn):
    f = open(fn, "r", encoding=getcharencode(fn), errors="ignore")
    data = f.read()
    f.close()
    return data


def saveToLocal(fn, data):
    try:
        data.encode(encoding="gbk")
    except:
        saveToLocalByEncode(fn, data, "utf8")
    else:
        saveToLocalByEncode(fn, data, "gbk")


def saveToLocalByEncode(fn, data, fileEncode):
    f = open(fn, "w", encoding=fileEncode)
    f.write(data)
    f.close()


if __name__ == "__main__":
    print("hello")
