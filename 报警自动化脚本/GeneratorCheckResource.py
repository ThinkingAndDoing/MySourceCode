#!/usr/bin/env python3
#-*- coding:utf-8 -*-

'''
author : xie wei
date   : 2016-09-29 
input  :
'''

import sys 
import codecs
import xml.dom.minidom as XML
import GeneratorCommonConfig as Config
from GeneratorCommonConfig import AddRunLog


'''
global variable
'''
thisFile = sys._getframe().f_code.co_filename

Config.requestConfig()

warningObjectFile = Config._FileList['_WarningObjectFile']
stringFile = Config._FileList['_GenStrFile']
imageFile = Config._FileList['_GenImgFile']


'''
functions
'''

def startToCheck():
	'''
	print root.nodeName
	print root.nodeValue
	print root.nodeType
	print root.ELEMENT_NODE
	'''
	try:
		inputDom = XML.parse(warningObjectFile)
		inputRoot = inputDom.documentElement
		strDom = XML.parse(stringFile)
		strRoot = strDom.documentElement
		imgDom = XML.parse(imageFile)
		imgRoot = imgDom.documentElement

	except Exception as e:
		AddRunLog('error', str(e), thisFile, sys._getframe().f_lineno)
		return False
	else:
		strList = []
		for resource in strRoot.getElementsByTagName("Resource"):
			strList.append(resource.getAttribute("Name"))
			
		imgList = []
		for resource in imgRoot.getElementsByTagName("Resource"):
			imgList.append(resource.getAttribute("Name"))
			
		#logging.debug(imgList)
		checkResult = True
		for array in inputRoot.getElementsByTagName("Array"):
			for object in array.getElementsByTagName("Object"):
				properties = object.getElementsByTagName("Properties")[0]
				for property in properties.getElementsByTagName("Property"):
					if property.getAttribute("Name")== "TextWList" or property.getAttribute("Name")== "TextWPopup":
						resource = property.getElementsByTagName("Resource")[0]
						try:
							if resource.firstChild is not None:
								retVal = strList.index(resource.firstChild.data)
						except Exception as e:
							checkResult = False
							AddRunLog('error', str(e), thisFile, sys._getframe().f_lineno)

					if property.getAttribute("Name")== "PopupBitmap":
						resource = property.getElementsByTagName("Resource")[0]
						try:
							if resource.firstChild is not None:
								retVal = imgList.index(resource.firstChild.data)
						except Exception as e:
							checkResult = False
							AddRunLog('error', str(e), thisFile, sys._getframe().f_lineno)

		if checkResult:
			return True
		else:
			return False

def resourceCheck():
	ret = 0
	try:
		ret = startToCheck()
	except Exception as e:
		AddRunLog('error',str(e), thisFile, sys._getframe().f_lineno)
		ret = 1
	return ret

if __name__ == "__main__":
	startCheck()
	
	
	