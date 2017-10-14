#!/usr/bin/env python3
#-*- coding:utf-8 -*-

'''
author : zhu cuicui
date   : 2016-09-27 
input: image path output: Image.xml
'''

import os 
import sys
import glob
import codecs
import xml.dom.minidom
import GeneratorCommonConfig as Config
from GeneratorCommonConfig import AddRunLog


'''
global variable
'''
thisFile = sys._getframe().f_code.co_filename

Config.requestConfig()

ListMode = Config._CarType['_ListMode']

ModeSuffix = Config._CarType['_ModeSuffix']

ListImgPath = Config._ImgPathList['_ListImgPath']

outputFile = Config._FileList['_GenImgFile']



'''
functions
'''


#function : Add warning display strings
def AddWrnImg(keyvalue,elements,ImgPath,_groupnum):
	resElement = dom.createElement('Resource')
	resElement.setAttribute("Name",keyvalue)
	resElement.setAttribute("GroupNumber",_groupnum)
	
	if len(elements) > len(ListMode):
		print('Warnings:Language attribute exceed the safe range ,len %d!'% len(elements))
		AddRunLog('warning','Language attribute exceed the safe range ,len'+str(len(elements)), thisFile, sys._getframe().f_lineno)
		return 1
	  
	for i in range(0,len(elements)):
		chElement = dom.createElement('Value')
		chElement.setAttribute("DependencyExpression",ListMode[i])
		nameTxt = dom.createTextNode(ImgPath+elements[i]+'.png') #ImgPath add by user
		chElement.appendChild(nameTxt)   
		resElement.appendChild(chElement)	 
	root.appendChild(resElement)
	
	return 0

def ErgodicPicture(_path,_rpath, _prefix, _groupnum):
	if (os.path.exists(_path) == False):	   #all about warning image path
		print('Warning : path '+_path+' not exist !\n')
		AddRunLog('warning', 'Path '+_path+' not exist !', thisFile, sys._getframe().f_lineno)
		return 1
	else:
		_picPath = _path + '*.png'
		for filename in glob.glob( _picPath ):
			
			if filename[-7:-4] in ModeSuffix:
				continue
			
			Listfilename= []
			
			namelist = filename.split('\\')
			Imgname = namelist[len(namelist)-1][:-4]	#filename[:-4] # make sure the dir structure is not changed.
			#Imgname = filename.split('\\',7)[7][:-4]	#filename[:-4] # make sure the dir structure is not changed.
			for i in range(0,len(ListMode)):   #different dependency assignment same picture resource
				_sourceName = _prefix + Imgname

				filenameWithMode = filename[:-4] + ModeSuffix[i] + ".png"
				if os.path.exists(filenameWithMode) == True:
					filenamelist = filenameWithMode.split('\\')
					Listfilename.append(filenamelist[len(filenamelist)-1][:-4])
					#Listfilename.append(filenameWithMode.split('\\',7)[7][:-4])
				else: 
					Listfilename.append(Imgname)
			ret = AddWrnImg(_sourceName,Listfilename,_rpath,_groupnum)
			if(ret):
				return ret 
	return 0
			
def ErgodicDir():
	for item in ListImgPath:
		ret = ErgodicPicture(item[0], item[1], item[2], item[3]) #traverse file path
		if(ret):
			return ret

			
def startToGenerate():
	global dom 
	global root	
	impl = xml.dom.minidom.getDOMImplementation()  
	dom = impl.createDocument(None,'Resources',None)
	root = dom.documentElement
	typeElement = dom.createElement('Type')
	nameTxt = dom.createTextNode('Images')
	typeElement.appendChild(nameTxt)
	root.appendChild(typeElement)
	ret = ErgodicDir()
	if(ret):
		return ret
	
	f= codecs.open(outputFile, 'w','utf-8')  
	dom.writexml(f, addindent='  ', newl='\n',encoding = 'utf-8')  
	f.close
	
	return 0


def Main_GeneratedImg(): 
	ret = 0
	try:
		ret = startToGenerate()
	except Exception as e:
		AddRunLog('error',str(e), thisFile, sys._getframe().f_lineno)
		ret = 1
	return ret

if __name__ == "__main__":
	Main_GeneratedImg()

	
