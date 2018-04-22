#!/usr/bin/python3
# -*- coding: UTF-8 -*-

import re
import os
import json
import chardet
import tkinter
from tkinter import *
from tkinter import ttk
from tkinter.font import Font
from tkinter.scrolledtext import ScrolledText
#ÿ��KEY��һ���ؼ���
#�ڲ�ͬKey֮�������ضȣ����ݺ�����ͬ�ؼ��ʵģ����ƶȸ�--�ǺͰٶ�֪���к���������������һ��֪ʶ��ϵ��һ��֪ʶ��ϵӦ���������ϵ����
#��ӡ��֪ʶ����
#https://www.zhihu.com/question/21929143
#http://www.sohu.com/a/140258152_367117
#https://zhidao.baidu.com/question/167778108.html
#http://gaozhongwuli.com/zongjie/
#https://blog.csdn.net/bnanoou/article/details/38434443
#https://www.cnblogs.com/wwf828/p/7418181.html
_InputDir = ".\\HMI Warning����"
_DictFile = ".\\data\\theDict.json"
_RootKey = "HMI Warning����"
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

class MyTreeView:
	def __init__(self, root):
		self.root = root
		treeItemFont=Font(family='����', size=16)
		fontheight=treeItemFont.metrics()['linespace']
		ttk.Style().configure('Filter.Treeview', font=treeItemFont, rowheight=fontheight, background='white', foreground='blue')
		self.treeView=ttk.Treeview(root, show='tree', style='Filter.Treeview')
		
		#����ˮƽ���������
		hbar = ttk.Scrollbar(self.root,orient=tkinter.HORIZONTAL,command=self.treeView.xview)
		hbar.place(y=460,width=200,height=20)
		
		#���ô�ֱ���������
		vbar = ttk.Scrollbar(root,orient=tkinter.VERTICAL,command=self.treeView.yview)
		vbar.place(x=200,width=20,height=480)
		
		self.treeView.configure(xscrollcommand=hbar.set)
		self.treeView.configure(yscrollcommand=vbar.set)
		self.treeView.bind("<<TreeviewSelect>>", self.leftClick)
		self.treeView.bind('<3>', self.rightClickMenu)
		#��������Ŀ¼
		self.treeView.place(x=0, y=0, width=201, height=480)

	def rightClickMenu(self, event):
		def delete():
			print(rowID)
			print("delete!")
			
		def edit():
			print(rowID)
			print("edit!")
		
		rowID = self.treeView.identify('item', event.x, event.y)
		if rowID:
			self.treeView.selection_set(rowID)
			self.treeView.focus_set()
			self.treeView.focus(rowID)
			
			menu = Menu(self.root, tearoff=0)
			menu.add_command(label="Delete", command=delete)
			menu.add_command(label="Edit", command=edit)
			menu.post(event.x_root, event.y_root)
		else:
			pass

	def createMyTree(self, mydict):
		myid=self.treeView.insert("", 0, mydict[_RootKey]["name"], text=mydict[_RootKey]["name"])
		self.createTree(self.treeView, mydict[_RootKey]["childs"], myid, mydict)

	def createTree(self, tree, childList, parentID, mydict):
		for child in childList:
			childID=tree.insert(parentID, childList.index(child), mydict[child]["name"], text=mydict[child]["name"])
			self.createTree(tree, mydict[child]["childs"], childID, mydict)
		
	def leftClick(self, event):
		#event.widget��ȡTreeview���󣬵���selection��ȡѡ���������
		sels= event.widget.selection()
		setTextArea(sels[0])

#--------------------------------------------------
#�洢
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
	f = open(_InputDir+"\\"+fn, "r", encoding=getcharencode(_InputDir+"\\"+fn), errors='ignore')
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
		content +="\nʲô��" + key + "��\n"
		content +=_Dict[key]["what"]
		content +="\n���" + key + "��\n"
		content +=_Dict[key]["how"]
		content +="\n"
	
	saveToLocal("����֪ʶ.txt", content)

#--------------------------------------------------
#���ݴ���ת��
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
#UI ��ʾ����
#--------------------------------------------------
def setTextArea(item):
	global _ScrollText
	
	_ScrollText.delete(1.0, END)
	_ScrollText.insert(INSERT, "name:\n"+_Dict[item]["name"] + "\n\n")
	_ScrollText.insert(INSERT, "how:\n"+_Dict[item]["how"] + "\n")
	_ScrollText.insert(INSERT, "what:\n"+_Dict[item]["what"] + "\n")
	_ScrollText.insert(INSERT, "decision:\n"+_Dict[item]["decision"] + "\n")
		
def drawGUI():
	global _ScrollText
	
	root=tkinter.Tk()
	root.title("����֪ʶ")
	root.geometry("800x480")
	root.resizable(width=False, height=False)
	textFont=Font(family='����', size=12)
	fontheight = textFont.metrics()['linespace']
	#��ScrollBar���ı�����
	_ScrollText = ScrolledText(root, padx=10, pady=10, font=textFont, borderwidth=2, width=68, background='white')
	_ScrollText.pack(side=RIGHT, fill=Y)
	#�½�����Ŀ¼
	tree = MyTreeView(root)
	tree.createMyTree(_Dict)
	root.mainloop()

if __name__ == "__main__":
	initDict()
	
	addNewKeys(_InputDir)
	
	writeJson(_DictFile, _Dict)
	
	genAttribs()
	#restoreSrc()
	drawGUI()

	