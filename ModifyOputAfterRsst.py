#!/usr/bin/python3
# -*- coding: UTF-8 -*-

import re
import os
import shutil

_InputFile = ".\\pkg\\gs4\\pkg\\rsst\\adapt\\rsst__dbitmapid_jcp2011.h"


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
	#	RSST_nInvalidBitmap 		= 65535	/* dummy id, addresses no valid resource, see spec for further questions! */
	data = readFile(_InputFile)
	newdata = re.sub(r'RSST_nInvalidBitmap 		=[^/]+/', "RSST_nInvalidBitmap 		= 65535	/", data)
	writeFile(_InputFile, newdata)

	



