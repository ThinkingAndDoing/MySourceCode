#!/usr/bin/python3
# -*- coding: UTF-8 -*-

import os
import json
import chardet
#每个KEY加一个关键词
#在不同Key之间计算相关度，内容含有相同关键词的，相似度高--那和百度知道有何区别？我想做的是一个知识体系，一个知识体系应该用因果联系串联
#https://www.zhihu.com/question/21929143
#http://www.sohu.com/a/140258152_367117
#https://zhidao.baidu.com/question/167778108.html
#http://gaozhongwuli.com/zongjie/

_InputDir = ".\\addNewKey"
_DictFile = ".\\data\\theDict.json"

_Dict = {}

class Node:
	def __init__(self, p, n):
		self.parent = p
		self.name = n
		self.childs = []
		self.what = ""
		self.how = ""
		self.decision = ""

	def setWhat(self, data):
		self.what = data
		
	def setHow(self, data):
		self.how = data
		
	def setDecision(self, data):
		self.decision = data

def getcharencode(filename):
	file = open(filename, "rb")#要有"rb"，如果没有这个的话，默认使用gbk读文件。          
	buf = file.read()
	file.close()
	result = chardet.detect(buf)
	return result["encoding"]
	
def getType(data, type):
	if data.find(type)!=-1:
		indexstart = data.find(type) + len(type)
		indexend = data.find("@", indexstart) - 1
		return data[indexstart:indexend]

def loadKey(fn):
	f = open(_InputDir+"\\"+fn, "r", encoding=getcharencode(_InputDir+"\\"+fn))
	data = f.read()
	f.close()
	
	newkey = Node(fn.split("-")[0], fn.split("-")[1].split(".")[0])
	newkey.setWhat(getType(data, "@what"))
	newkey.setHow(getType(data, "@how"))
	newkey.setDecision(getType(data, "@decision"))
	return newkey
	
def addKey(key):
	if key in _Dict:
		_Dict[key.parent].childs.append(key.name)
		
	dictkey = {}
	dictkey["parent"] = key.parent
	dictkey["name"] = key.name
	dictkey["childs"] = key.childs
	dictkey["what"] = key.what
	dictkey["how"] = key.how
	dictkey["decision"] = key.decision
	_Dict[key.name] = dictkey
	
def writeJson(fn, js):
	with open(fn, 'w') as f:
		json.dump(js, f, indent=4, ensure_ascii=False)

def readJson(fn):
	with open(fn, 'r') as f:
		data = json.load(f)
		return eval(str(data))
	
def initDict():
	global _Dict
	
	if os.path.exists(_DictFile):
		_Dict = readJson(_DictFile)
	
def addNewKeys(foldername):
	global _Dict
	
	filelist = os.listdir(foldername)
	for fn in filelist:
		newkey = loadKey(fn)
		addKey(newkey)

def saveKeyList():
	global _Dict
	
	keyList = {}
	keyList["keylist"] = list(_Dict.keys())
	writeJson("MyDict.json", keyList)
	
if __name__ == "__main__":
	initDict()
	
	addNewKeys(_InputDir)
	
	"""
	print(list(_Dict.keys()))
	
	key = input("Tell me what you want!")
	
	if key in _Dict.keys():
		print("***********************************************")
		print(_Dict[key])
	else:
		print("Not found!")
	"""
	
	writeJson(_DictFile, _Dict)
	
	saveKeyList()
	
	
	