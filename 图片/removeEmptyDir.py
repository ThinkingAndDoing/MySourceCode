#!/usr/bin/python3
# -*- coding: UTF-8 -*-

import re
import os
import sys

_InputDir = ".\\Bitmaps"

def isEmpty(distfolder):
	if os.listdir(distfolder)==[]:
		return True
	else:
		return False

def removedir(adir):
	try:
		os.rmdir(adir)
	except Exception as e:
		print(e)
	else:
		print(adir + " is deleted!")
	

def removeEmptyDir(distfolder):
	for root, dirs, files in os.walk(distfolder, topdown=False):
		for name in dirs:
			if isEmpty(os.path.join(root, name))==True:
				removedir(os.path.join(root, name))

if __name__ == "__main__":
	try:
		if os.path.exists( sys.argv[1] ):
			_InputDir = sys.argv[1]
	except Exception as e:
		print(e)
	
	removeEmptyDir(_InputDir)

	



