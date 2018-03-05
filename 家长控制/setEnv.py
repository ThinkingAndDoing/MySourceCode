#!/usr/bin/env python
#-*- coding:cp936 -*-

import shutil
import os
import json

_MyDesktop = "C:\\Users\\uidp8103\\Desktop"
_TempDir = _MyDesktop + "\\Temp"

_DictEnvs = {}

def readJson(fn):
	with open(fn, 'r') as f:
		data = json.load(f)
		return eval(str(data))

def ClearPrevious():
	global _DictEnvs
	
	for i in _DictEnvs.keys():
		filename = _TempDir + "\\" + _DictEnvs[i]
		f = open(filename, "r")
		filelist = f.readlines()
		f.close()
		for i in filelist:
			i = i.rstrip('\n')
			try:
				os.remove(_MyDesktop+"\\"+i)
			except:
				continue
	
def setEnv(filename):
	filename = _TempDir + "\\" + filename
	print(filename)
	f = open(filename, "r")
	filelist = f.readlines()
	f.close()
	
	for i in filelist:
		i = i.rstrip('\n')
		shutil.copy(_TempDir+"\\"+i, _MyDesktop)
	print(filelist)

def inputhelp():
	global _DictEnvs
	
	print("请输入ID选择环境")
	dictSorted = sorted(_DictEnvs.keys())
	for i in range(0, len(dictSorted)):
		print(str(i)+": "+dictSorted[i])
	print("c: Clear")
	print("a: All")
	print("q: Quit")

def requestConfig():
	global _DictEnvs
	
	_DictEnvs = readJson(_TempDir + "\\Envlist.json")
	print(_DictEnvs)

if __name__=="__main__":
	requestConfig()
	
	while True:
		inputhelp()
		envID = input()
		if envID=="q":
			break
		elif envID=="c":
			ClearPrevious()
		elif envID=="a":
			ClearPrevious()
			for i in _DictEnvs.keys():
				setEnv(_DictEnvs[i])
		else:
			dictSorted = sorted(_DictEnvs.keys())
			for i in range(0, len(dictSorted)):
				if str(i)==envID:
					ClearPrevious()
					setEnv(_DictEnvs[dictSorted[i]])
					batshell = _TempDir+"\\"+dictSorted[i]+".bat"
					if os.path.exists(batshell):
						print(batshell)
						os.system(batshell)


	
