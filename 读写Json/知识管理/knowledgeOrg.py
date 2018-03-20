#!/usr/bin/python3
# -*- coding: UTF-8 -*-

import os
import json

_InputDir = ".\\addNewKey"
_DictFile = ".\\data\\theDict.json"

_Dict = {}

def writeJson(fn, js):
	with open(fn, 'w') as f:
		json.dump(js, f, indent=4, ensure_ascii=False)

def readJson(fn):
	with open(fn, 'r') as f:
		data = json.load(f)
		return eval(str(data))

def loadListFromLocal(fn):
	f = open(fn, "r")
	theList = []
	for line in f.readlines():
		theList.append(line.replace("\n", "").replace("\t", " "))
	f.close()
	return theList
	
def initDict():
	global _Dict
	
	if os.path.exists(_DictFile):
		_Dict = readJson(_DictFile)
	
def addNewKeys(foldername):
	global _Dict
	
	filelist = os.listdir(foldername)
	for fn in filelist:
		valuelist = loadListFromLocal(_InputDir+"\\"+fn)
		key = fn.split(".")[0]
		if []!=valuelist:
			_Dict[key] = valuelist
		else:
			if key in _Dict.keys():
				del _Dict[fn.split(".")[0]]

if __name__ == "__main__":
	initDict()
	
	addNewKeys(_InputDir)
	
	print(list(_Dict.keys()))
	
	key = input("Tell me what you want!")
	
	if key in _Dict.keys():
		print("***********************************************")
		for i in _Dict[key]:
			print(i)
	else:
		print("Not found!")
		
	writeJson(_DictFile, _Dict)
	
	
	
	