#!/usr/bin/python3
# -*- coding: UTF-8 -*-

import os
import chardet
import tkinter
import threading
from tkinter import *
from tkinter import ttk
from tkinter.font import Font
from tkinter.scrolledtext import ScrolledText
import jsoner 
import txter 
#每个KEY加一个关键词
#在不同Key之间计算相关度，内容含有相同关键词的，相似度高--那和百度知道有何区别？我想做的是一个知识体系，一个知识体系应该用因果联系串联
#如果你希望精确熟练地掌握你所总结的知识树，那么最好是打印出知识网络，经常查阅思考
#增加提问功能，用于在阅读知识点时，记录所思考到的问题
#那些储存了“以后慢慢看”的东西，你基本不会再看。所以本项目的正确用法是用作组织原创，自己理解的知识体系，不求全面，只要实用
#在知识传承中，如果接受者是初学者，那么至今最好的方法是给出按步骤操作的实例，再加以解释。舍此别无他法。本项目不适用。
#本项目更适合掌握基本知识的读者，做精读，反复思考，修改，知识精华的提炼。
#https://www.zhihu.com/question/21929143
#http://www.sohu.com/a/140258152_367117
#https://zhidao.baidu.com/question/167778108.html
#http://gaozhongwuli.com/zongjie/
#https://blog.csdn.net/bnanoou/article/details/38434443
#https://www.cnblogs.com/wwf828/p/7418181.html

class GloableVariables:
	_Dict = {}
	_InputDir = ""
	_KnowledgeSegment = ""
	_RootKey = ""
	_ScrollText = None
	_Interval = 0.2
	_StopThread = False
	_Root = None
	_TimerThread = None

class Node:
	def __init__(self, p, n):
		self.parent = p
		self.name = n
		self.childs = []
		self.what = ""
		self.how = ""
		self.question = "" 

	def setWhat(self, data):
		self.what = data
		
	def setHow(self, data):
		self.how = data
		
	def setQuestion(self, data): 
		self.question = data

class MyTreeView:
	def __init__(self, root):
		self.root = root
		treeItemFont=Font(family='宋体', size=16)
		fontheight=treeItemFont.metrics()['linespace']
		ttk.Style().configure('Filter.Treeview', font=treeItemFont, rowheight=fontheight, background='white', foreground='blue')
		self.treeView=ttk.Treeview(root, show='tree', style='Filter.Treeview')
		
		#放置水平方向滚动条
		hbar = ttk.Scrollbar(self.root,orient=tkinter.HORIZONTAL,command=self.treeView.xview)
		hbar.place(y=460,width=200,height=20)
		hbar.pack(side=BOTTOM, fill=X)
		
		#放置垂直方向滚动条
		vbar = ttk.Scrollbar(root,orient=tkinter.VERTICAL,command=self.treeView.yview)
		vbar.place(x=200,width=20,height=480)
		vbar.pack(side=RIGHT, fill=Y)
		
		self.treeView.configure(xscrollcommand=hbar.set)
		self.treeView.configure(yscrollcommand=vbar.set)
		self.treeView.bind("<<TreeviewSelect>>", self.leftClick)
		self.treeView.bind('<3>', self.rightClickMenu)
		#放置树形目录
		#self.treeView.place(x=0, y=0)
		self.treeView.pack(side=LEFT, fill=Y)

	def rightClickMenu(self, event):
		'''
		def delete():
			print(rowID)
			print("delete!")
			
		def edit():
			print(rowID)
			print("edit!")
		'''
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
		myid=self.treeView.insert("", 0, mydict[GV._RootKey]["name"], text=mydict[GV._RootKey]["name"])
		self.createTree(self.treeView, mydict[GV._RootKey]["childs"], myid, mydict)

	def createTree(self, tree, childList, parentID, mydict):
		for child in childList:
			childID=tree.insert(parentID, childList.index(child), mydict[child]["name"], text=mydict[child]["name"])
			self.createTree(tree, mydict[child]["childs"], childID, mydict)
		
	def leftClick(self, event):
		#event.widget获取Treeview对象，调用selection获取选择对象名称
		sels= event.widget.selection()
		setTextArea(sels[0])

#--------------------------------------------------
#存储
#--------------------------------------------------
def restoreSrcTXT(inputDir): 
	
	for key in GV._Dict.keys():
		content = ""
		content +="@how\n"
		content +=removeEmptyLines(GV._Dict[key]["how"])+ "\n"
		content +="@what\n"
		content +=removeEmptyLines(GV._Dict[key]["what"])+ "\n"
		content +="@question\n" 
		content +=removeEmptyLines(GV._Dict[key]["question"])+ "\n" 
		content +="@"
		txter.saveToLocal(inputDir+"\\"+GV._Dict[key]["parent"]+"-"+GV._Dict[key]["name"]+".txt", content) 
	
def loadKey(fn, inputdir):
	data = txter.loadFromLocal(inputdir+"\\"+fn)
	
	newkey = Node(fn.split("-")[0].strip(), fn.split("-")[1].split(".")[0].strip())
	newkey.setWhat(getType(data, "@what"))
	newkey.setHow(getType(data, "@how"))
	newkey.setQuestion(getType(data, "@question"))
	return newkey
	
def initDict(thedict):
	if os.path.exists(thedict):
		GV._Dict = jsoner.readJson(thedict)

def updateDict(content):
	try:
		name = getType(content, "@name")
		if name!=None:
			name=name.strip("\n")
			if name in list(GV._Dict.keys()):
				if getType(content, "@question")!=None:
					GV._Dict[name]["question"] = getType(content, "@question")
			else:
				#print("name:"+name + " is not in list:"+ str(list(GV._Dict.keys())))
				pass
	except Exception as e:
		#print(e)
		pass
	
def createKnowledgeList(): 	
	content = ""
	for key in GV._Dict.keys():
		content +="["+GV._Dict[key]["parent"]+"->"+key+"]\n"
		content +="\n什么是" + key + "？\n"
		content +=GV._Dict[key]["what"]
		content +="\n如何" + key + "？\n"
		content +=GV._Dict[key]["how"]
		content +="\n"
	
	txter.saveToLocal("领域知识.txt", content) 

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
	for key in GV._Dict.keys():
		if GV._Dict[key]["parent"] in list(GV._Dict.keys()):
			if GV._Dict[key]["name"] not in GV._Dict[GV._Dict[key]["parent"]]["childs"]:
				GV._Dict[GV._Dict[key]["parent"]]["childs"].append(GV._Dict[key]["name"])

def addKey(key):
	dictkey = {}
	dictkey["parent"] = key.parent
	dictkey["name"] = key.name
	dictkey["childs"] = key.childs
	dictkey["what"] = key.what
	dictkey["how"] = key.how
	dictkey["question"] = key.question 
	GV._Dict[key.name] = dictkey
	
def addNewKeys(foldername):
	filelist = os.listdir(foldername)
	for fn in filelist:
		if fn.rfind(".txt")!=-1:
			newkey = loadKey(fn, foldername)
			addKey(newkey)
		else:
			#print(fn+" is skipped!")
			pass
	addRelationship()

def getRootKey():
	for k in list(GV._Dict.keys()):
		if "ROOT"==GV._Dict[k]["parent"]:
			GV._RootKey = k
			return True
	return False

#--------------------------------------------------
#UI 显示部分
#--------------------------------------------------
def syncQuestionArea(scrollText):
	if GV._StopThread==False:
		content = scrollText.get(1.0, END)
		updateDict(content)
		
		GV._TimerThread = threading.Timer(GV._Interval, syncQuestionArea, [scrollText])
		GV._TimerThread.setDaemon(True)
		GV._TimerThread.start()

def setTextArea(item):
	GV._ScrollText.delete(1.0, END)
	GV._ScrollText.insert(INSERT, "@name\n"+GV._Dict[item]["name"] + "\n\n")
	GV._ScrollText.insert(INSERT, "@how\n"+GV._Dict[item]["how"] + "\n")
	GV._ScrollText.insert(INSERT, "@what\n"+GV._Dict[item]["what"] + "\n")
	GV._ScrollText.insert(INSERT, "@question\n"+GV._Dict[item]["question"] + "\n") 
		
def drawGUI():
	GV._StopThread = False
	GV._Root=tkinter.Tk()
	GV._Root.title("领域知识")
	GV._Root.resizable(width=False, height=False)
	textFont=Font(family='宋体', size=12)
	fontheight = textFont.metrics()['linespace']
	frame_root = Frame(GV._Root)
	frame_root.pack(side=RIGHT, fill=BOTH)
	#带ScrollBar的文本区域
	GV._ScrollText = ScrolledText(frame_root, spacing3=8, padx=10, pady=10, font=textFont, borderwidth=2, width=80, background='white')
	GV._ScrollText.pack(side=RIGHT, fill=Y)
	#Resize Window
	frame_root.update()
	newWidthOfWindow = frame_root.winfo_width()+225
	newHeightOfWindow = ( frame_root.winfo_width()+225 )/5*3
	GV._Root.geometry('%dx%d'%(newWidthOfWindow, newHeightOfWindow))
	
	GV._TimerThread = threading.Timer(GV._Interval, syncQuestionArea, [GV._ScrollText])
	GV._TimerThread.setDaemon(True)
	GV._TimerThread.start()
	#新建树形目录
	tree = MyTreeView(GV._Root)
	tree.createMyTree(GV._Dict)
	GV._Root.protocol('WM_DELETE_WINDOW', closeWindow)
	GV._Root.mainloop()

def closeWindow():
	GV._StopThread = True
	GV._Root.destroy()


def initGlobalVar(inputdir="."):
	GV._InputDir = inputdir
	GV._KnowledgeSegment = GV._InputDir

if __name__ == "__main__":
	global GV
	
	GV = GloableVariables()
	try:
		if os.path.exists( sys.argv[1] ):
			initGlobalVar(sys.argv[1])
		else:
			initGlobalVar()
			#print(sys.argv[1]+": Path is not exist!")
			pass
	except Exception as e:
		#print(e)
		pass
	
	#initDict(GV._InputDir+"\\theDict.json")
	
	#从TXTs中增加新的知识到字典中
	addNewKeys(GV._KnowledgeSegment)
	
	if getRootKey()==True:
		#创建知识列表用作打印
		#createKnowledgeList() 
		#显示阅读界面
		drawGUI()
		#根据最新的字典更新TXTs
		restoreSrcTXT(GV._KnowledgeSegment)
		#保存最新的字典
		#jsoner.writeJson(GV._InputDir+"\\theDict.json", GV._Dict)
	else:
		#print("Please create root node file. For example, the filename should be ROOT-HMI 报警开发")
		pass
	

