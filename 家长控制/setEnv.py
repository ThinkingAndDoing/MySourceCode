#!/usr/bin/env python
#-*- coding:utf8 -*-

import shutil
import os
import json

_MyDesktop = "C:\\Users\\uidp8103\\Desktop"
_TempDir = _MyDesktop + "\\Temp"

_DictEnvs = {}

def ClearAll():
	global _DictEnvs
	
	for i in _DictEnvs.keys():
		foldername = _DictEnvs[i]
		filelist = os.listdir(foldername)
		for i in filelist:
			i = i.rstrip('\n')
			try:
				os.remove(_MyDesktop+"\\"+i)
			except:
				continue
	
def setEnv(foldername):
	print(foldername)
	filelist = os.listdir(foldername)
	for i in filelist:
		i = i.rstrip('\n')
		if i!="start.bat":
			shutil.copy(foldername+"\\"+i, _MyDesktop)
	print(filelist)
	batshell = foldername+"\\start.bat"
	if os.path.exists(batshell):
		print(batshell)
		os.system(batshell)

def inputhelp():
	global _DictEnvs
	
	print("请输入ID，选择不同环境")
	dictSorted = sorted(_DictEnvs.keys())
	for i in range(0, len(dictSorted)):
		print(str(i)+": "+dictSorted[i])
	print("c: Clear")
	print("a: All")
	
def initDict():
	for fn in os.listdir(_TempDir):
		if os.path.isdir(_TempDir+"\\"+fn):
			_DictEnvs[fn] = _TempDir+"\\"+fn

def run():
	while True:
		inputhelp()
		envID = input()
		if envID=="c":
			ClearAll()
			break
		elif envID=="a":
			ClearAll()
			for i in _DictEnvs.keys():
				setEnv(_DictEnvs[i])
			break
		else:
			dictSorted = sorted(_DictEnvs.keys())
			for i in range(0, len(dictSorted)):
				if str(i)==envID:
					ClearAll()
					setEnv(_DictEnvs[dictSorted[i]])
			break

if __name__=="__main__":
	initDict()
	run()



	
