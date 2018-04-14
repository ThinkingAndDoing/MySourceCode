#!/usr/bin/python3
# -*- coding: UTF-8 -*-

import re
import os
import json
import chardet
import tkinter
from tkinter import *
from tkinter import ttk
from tkinter.scrolledtext import ScrolledText
#每个KEY加一个关键词
#在不同Key之间计算相关度，内容含有相同关键词的，相似度高--那和百度知道有何区别？我想做的是一个知识体系，一个知识体系应该用因果联系串联
#打印出知识网络
#https://www.zhihu.com/question/21929143
#http://www.sohu.com/a/140258152_367117
#https://zhidao.baidu.com/question/167778108.html
#http://gaozhongwuli.com/zongjie/
#https://blog.csdn.net/bnanoou/article/details/38434443
#https://www.cnblogs.com/wwf828/p/7418181.html
_InputDir = ".\\HMI Warning开发"
_DictFile = ".\\data\\theDict.json"
_RootKey = "HMI Warning开发"
_ScrollText = None

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

#--------------------------------------------------
#存储
#--------------------------------------------------
def restoreSrc():
	global _Dict
	
	for key in _Dict.keys():
		content = ""
		content +="@how\n"
		content +=removeEmptyLines(_Dict[key]["how"])+ "\n"
		content +="@what\n"
		content +=removeEmptyLines(_Dict[key]["what"])+ "\n"
		content +="@decision\n"
		content +=removeEmptyLines(_Dict[key]["decision"])+ "\n"
		content +="@"
		saveToLocal(_InputDir+"\\"+_Dict[key]["parent"]+"-"+_Dict[key]["name"]+".txt", content)

def getcharencode(filename):
	file = open(filename, "rb")          
	buf = file.read()
	file.close()
	result = chardet.detect(buf)
	return result["encoding"]
	
def loadKey(fn):
	f = open(_InputDir+"\\"+fn, "r", encoding=getcharencode(_InputDir+"\\"+fn))
	data = f.read()
	f.close()
	
	newkey = Node(fn.split("-")[0].strip(), fn.split("-")[1].split(".")[0].strip())
	newkey.setWhat(getType(data, "@what"))
	newkey.setHow(getType(data, "@how"))
	newkey.setDecision(getType(data, "@decision"))
	return newkey
	
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
		
def saveToLocal(fn, data):
	f = open(fn, "w")
	f.write(data)
	f.close()
	
def genAttribs():
	global _Dict
	
	content = ""
	for key in _Dict.keys():
		content +="["+_Dict[key]["parent"]+"->"+key+"]\n"
		content +="\n什么是" + key + "？\n"
		content +=_Dict[key]["what"]
		content +="\n如何" + key + "？\n"
		content +=_Dict[key]["how"]
		content +="\n"
	
	saveToLocal("领域知识.txt", content)

#--------------------------------------------------
#数据处理，转换
#--------------------------------------------------
def removeEmptyLines(data):
	
	lines = data.split("\n")
	newdata = ""
	for line in lines:
		if line.strip()!="":
			newdata += line+"\n"
	return newdata

def getType(data, type):
	if data.find(type)!=-1:
		indexstart = data.find(type) + len(type)
		indexend = data.find("@", indexstart) - 1
		return removeEmptyLines(data[indexstart:indexend])

def addRelationship():
	global _Dict
	
	for key in _Dict.keys():
		if _Dict[key]["parent"] in list(_Dict.keys()):
			if _Dict[key]["name"] not in _Dict[_Dict[key]["parent"]]["childs"]:
				_Dict[_Dict[key]["parent"]]["childs"].append(_Dict[key]["name"])

def addKey(key):
	global _Dict

	dictkey = {}
	dictkey["parent"] = key.parent
	dictkey["name"] = key.name
	dictkey["childs"] = key.childs
	dictkey["what"] = key.what
	dictkey["how"] = key.how
	dictkey["decision"] = key.decision
	_Dict[key.name] = dictkey
	
def addNewKeys(foldername):
	global _Dict
	
	filelist = os.listdir(foldername)
	for fn in filelist:
		newkey = loadKey(fn)
		addKey(newkey)
	addRelationship()

#--------------------------------------------------
#UI 显示部分
#--------------------------------------------------
def drawGUI():
	global _ScrollText
	
	root=tkinter.Tk()
	root.title("领域知识")
	root.geometry("800x480")
	root.resizable(width=False, height=False)
	#part one
	_ScrollText = ScrolledText(root, x=240, y=0, width=80, height=480, background='#f0f0f0')
	_ScrollText.pack(side=RIGHT, fill=Y)
	#part two
	tree=ttk.Treeview(root)
	vbar = ttk.Scrollbar(root,orient=tkinter.VERTICAL,command=tree.yview)
	vbar.place(x=200,width=20,height=480)
	hbar = ttk.Scrollbar(root,orient=tkinter.HORIZONTAL,command=tree.yview)
	hbar.place(y=460,width=200,height=20)
	myid=tree.insert("", 0, _Dict[_RootKey]["name"], text=_Dict[_RootKey]["name"])
	createTree(tree, _Dict[_RootKey]["childs"], myid)
	tree.configure(yscrollcommand=vbar.set)
	tree.configure(yscrollcommand=hbar.set)
	tree.bind("<<TreeviewSelect>>", treeCB)
	tree.pack(side=LEFT, fill=Y)

	
	root.mainloop()

def treeCB(event):
	#event.widget获取Treeview对象，调用selection获取选择对象名称
	sels= event.widget.selection()
	_ScrollText.delete(1.0, END)
	_ScrollText.insert(INSERT, "name:"+_Dict[sels[0]]["name"] + "\n")
	_ScrollText.insert(INSERT, "how:"+_Dict[sels[0]]["how"] + "\n")
	_ScrollText.insert(INSERT, "what:"+_Dict[sels[0]]["what"] + "\n")
	_ScrollText.insert(INSERT, "decision:"+_Dict[sels[0]]["decision"] + "\n")
	print(sels[0])

def createTree(tree, childList, parentID):
	print(childList)
	for child in childList:
		childID=tree.insert(parentID, childList.index(child), _Dict[child]["name"], text=_Dict[child]["name"])
		createTree(tree, _Dict[child]["childs"], childID)
	
if __name__ == "__main__":
	initDict()
	
	addNewKeys(_InputDir)
	
	writeJson(_DictFile, _Dict)
	
	genAttribs()
	#restoreSrc()
	drawGUI()

	