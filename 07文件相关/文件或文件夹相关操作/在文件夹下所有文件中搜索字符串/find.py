#!/usr/bin/python3
# -*- coding: UTF-8 -*-

import sys
import shutil
import os

_Key = sys.argv[1]
_DistDir = sys.argv[2]

def findStrInFiles(key, distpath):
	for root, dirs, files in os.walk(distpath, topdown=False):
		for name in files:
			try:
				filename = os.path.join(root, name)
				f = open(filename, "r")
				if f.read().find(key)!=-1:
					print(os.path.join(root, name))
				f.close()
			except Exception as e:
				continue
				#print(e)

if __name__=="__main__":
	findStrInFiles(_Key, _DistDir)

