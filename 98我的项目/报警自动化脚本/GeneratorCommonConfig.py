#!/usr/bin/env python3
#-*- coding:utf-8 -*-

'''
author : xie wei
date   : 2016-09-29 
input  :
'''
import logging
import json

'''
global variable
'''

_LogFile = './GeneratorErrorList.txt'

#save run log
def AddRunLog(level, message, _file, _line):
	
	message = _file + ' [' + str(_line) + '] ' + message
	
	logging.basicConfig(level=logging.DEBUG,format='%(asctime)s <%(levelname)s> %(message)s',datefmt = '%Y-%m-%d %H:%M:%S',filename =_LogFile, filemode ='w')
	if(level == 'debug'):
		logging.debug(message)
	elif(level == 'info'):
		logging.info(message)
	elif(level == 'warning'):
		logging.warning(message)
	elif(level == 'error'):
		logging.error(message)
	else: 
		logging.critical(message)

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
	
	
	
		