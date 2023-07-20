#!/usr/bin/python3
# -*- coding: UTF-8 -*-
import sys
import re

_sourcefile = sys.argv[1]


def loadFromLocal(filename):
    hFile = open(filename, "r")
    lRecords = hFile.read()
    hFile.close()
    return lRecords


def saveToLocal(filename, data):
    hFile = open(filename, "w")
    hFile.write(data)
    hFile.close()


def convert(code):
    newcode = code
    newcode = re.sub(r"\w+\s+(\w+)\(\w*\)", r"def \1():", newcode)
    newcode = re.sub(r"[;\{\}]|int |extern |double |void ", "", newcode)
    newcode = newcode.replace("//", "#")
    newcode = newcode.replace("false", "False")
    newcode = newcode.replace("true", "True")
    newcode = newcode.replace("Print", "print")
    newcode = newcode.replace("&&", "and")
    newcode = newcode.replace("||", "or")
    return newcode


if __name__ == "__main__":
    data = loadFromLocal(_sourcefile)
    saveToLocal(_sourcefile[:-3] + "py", convert(data))
