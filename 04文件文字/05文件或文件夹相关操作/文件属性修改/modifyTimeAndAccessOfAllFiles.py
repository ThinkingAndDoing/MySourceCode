#!/usr/bin/python
# -*- coding: UTF-8 -*-

import os
import sys
import time
import stat

global _DistPath

_DistPath = "pkg_mks"

def modifyTimeAndAccessOfAllFiles(distpath):
	for root, dirs, files in os.walk(distpath, topdown=False):
		for name in files + dirs:
			print(os.path.join(root, name))
			os.chmod(os.path.join(root, name), stat.S_IWRITE)
			os.utime(os.path.join(root, name), None)

if __name__=="__main__":

	modifyTimeAndAccessOfAllFiles(_DistPath)
