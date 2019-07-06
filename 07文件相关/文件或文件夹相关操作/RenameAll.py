#!/usr/bin/python3
# -*- coding: UTF-8 -*-
import os
import re

_lSupportExt = [".mp4", ".MP4", ".avi", ".rmvb"]
_dictFileName = {}

def getVideoDict(distDir="."):
    list = []
    for fn in os.listdir(distDir):
        if "."+fn.split(".")[-1] in _lSupportExt:
            _dictFileName[fn]=""
    
    i = 1
    for ofn in sorted(_dictFileName.keys()):
        setNewFileName(ofn, i)
        i = i+1

def boHasPrefix(fn):
    if re.match(r'^A[0-9]{3}_', fn) is None:
        return False
    else:
        return True

def setNewFileName(oldfilename, value):
    if boHasPrefix(oldfilename):
        newfilename = oldfilename[5:]
    else:
        newfilename = oldfilename
    newfilename = getPrefix(3, value) + newfilename
    _dictFileName[oldfilename] = newfilename

def getPrefix(length, value):
	print(value)
	if value<0 or length<=0:
		return "Aerror_"
		
	if value == 0:
		return "A000_"
	
	prefix = ""
	x = length-1
	while x>=0 and value<=pow(10,x)-1:
		prefix += "0"
		x -= 1
	prefix = "A" + prefix+"%d"%value + "_"
	return prefix

def renameVideos():
    for ofn in _dictFileName.keys():
        os.rename(ofn, "AXXX_"+ofn)
    for ofn in _dictFileName.keys():
        os.rename("AXXX_"+ofn, _dictFileName[ofn])

if __name__=="__main__":

	getVideoDict()
	print(_dictFileName)
	renameVideos()
	
