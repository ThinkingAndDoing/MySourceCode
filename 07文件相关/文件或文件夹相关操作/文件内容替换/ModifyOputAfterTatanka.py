#!/usr/bin/python3
# -*- coding: UTF-8 -*-

import re
import os
import shutil

_InputFile = ".\\02_Tatanka_Output\\CIA\\TimeDomains.xml"
_BCTool = "C:\Program Files (x86)\Beyond Compare 3"

def readFile(fn):
	f = open(fn, "r", encoding='utf-8')
	data = f.read()
	f.close()
	return data
	
def writeFile(fn, data):
	f = open(fn, "w", encoding='utf-8')
	f.write(data)
	f.close()


if __name__ == "__main__":
	'''
	if os.path.isfile(_OutputFile):
		os.remove(_OutputFile)
	'''
	#step 1
	data = readFile(_InputFile)
	newdata = re.sub(r'Divider="1"', "Divider=\"3\"", data)
	newdata = re.sub(r'"CIA_TDCyclic_1"', "\"CIA_TDCyclic_1\" ", newdata)
	writeFile(_InputFile, newdata)
	#step 2
	shutil.copyfile(".\\Internals\\3.7.6\\Configuration\\MemoryManagerConfiguration.xml",".\\02_Tatanka_Output\\Configuration\\MemoryManagerConfiguration.xml")
	shutil.copyfile(".\\Internals\\3.7.6\\Cache\\Cache_JCP2011.xml",".\\02_Tatanka_Output\\Cache\\Cache_JCP2011.xml")
	shutil.copyfile(".\\Internals\\3.7.6\\Resources\\ModelFile.xml",".\\02_Tatanka_Output\\Resources\\ModelFile.xml")
	shutil.copyfile(".\\Internals\\3.7.6\\Resources\\TargetMem.xml",".\\02_Tatanka_Output\\Resources\\TargetMem.xml")
	#step 3 open beyond compare
	curPos = os.getcwd()
	if os.path.exists(_BCTool):
		os.chdir(_BCTool)
		os.system("BCompare.exe "+curPos+"\\02_Tatanka_Output "+curPos+"\..\Model")
		os.chdir(curPos)
	else:
		print("What a pity! Beyond compare is not found!")
	



