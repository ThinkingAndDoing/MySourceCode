#!/usr/bin/env python3
#-*- coding:utf-8 -*-

'''
author : xie wei
date   : 2016-09-29 
input  :
'''
import json

'''
global variable
'''


def readJson(fn):
	with open(fn, 'r') as f:
		data = json.load(f)
		return eval(str(data))

def requestConfig():
	global _WrnObjConf
	global _WrnDispatConf
	global _LangSetting
	global _FileList
	global _CarType
	global _ImgPathList

	_LangSetting = readJson("data\\langsetting.json")
	_FileList = readJson("data\\filelist.json")
	_CarType = readJson("data\\cartype.json")
	_ImgPathList = readJson("data\\imgpathlist.json")
	_WrnObjConf = readJson("data\\wrnobjconf.json")
	_WrnDispatConf = readJson("data\\wrndispatconf.json")
	

if __name__ == "__main__":
	requestConfig()
	
	print(_LangSetting)
	
		