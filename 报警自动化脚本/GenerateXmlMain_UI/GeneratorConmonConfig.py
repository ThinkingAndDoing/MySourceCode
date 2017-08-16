#!/usr/bin/env python3
#-*- coding:utf-8 -*-

'''
author : xie wei
date   : 2016-09-29 
input  :
'''
import logging

'''
global variable
'''

_LogFile = './GenerateObject_runlog.txt'

#variable for GenerateDispatcherXml.py
_InputExcelName = 'WarningConfiguration.xlsm'
_WarningDispatcherFile = 'WarningDispatchers.xml'

#variable for GenerateImgXml.py
_ListMode =("CarType : Car_Normal","CarType : Car_SV","CarType : Car_CV") #configure dependency
_ModeSuffix =("","_SV","_CV") #suffix
_ListImgPath = [['.\\..\\..\\GraphicalResources\\Bitmaps\\Warning\\Telltales\\', ".\\Bitmaps\\Warning\\Telltales\\", "Telltale_"], \
				['.\\..\\..\\GraphicalResources\\Bitmaps\\Warning\\DoorOpen\\', ".\\Bitmaps\\Warning\\DoorOpen\\", "DoorOpen_"], \
				['.\\..\\..\\GraphicalResources\\Bitmaps\\Warning\\Message\\', ".\\Bitmaps\\Warning\\Message\\", "Message_"]]

#variable for CheckStringAndImage.py
_WarningObjectFile = 'WarningObjects.xml'

#variable for GenerateStringXml.py
_LangColNum = 6   #excel read  Range Col
_ListLan = ("Language : Chinese","Language : English","Language : Russian","Language : Arabic","Language : Persian","Language : Spanish")
_GenStrFile = 'Generated_String.xml'

#variable for GenerateImgXml.py
_GenImgFile = 'Generated_Image.xml'



#save run log
def AddRunLog(level, message, _file, _line):
	
	message = _file + ' [' + str(_line) + '] ' + message
	
	logging.basicConfig(level=logging.DEBUG,format='%(asctime)s <%(levelname)s> %(message)s',datefmt = '%Y-%m-%d %H:%M:%S',filename =_LogFile, filemode ='w')
	if(level == 'debug'):
		logging.debug(message)
	elif(level == 'info'):
		logging.info(message)
	elif(level == 'warning'):
		logging.warning(message)
	elif(level == 'error'):
		logging.error(message)
	else: 
		logging.critical(message)

