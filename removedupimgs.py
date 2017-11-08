#!/usr/bin/python3
# -*- coding: UTF-8 -*-

import os,hashlib


_MD5HashCode = {}
_DistDir = 'resource'
_NumOfDelFiles = 0

def md5sum(filename):
	f=open(filename, 'rb')
	md5=hashlib.md5()
	while True:
		fb = f.read(8096)
		if not fb:
			break
		md5.update(fb)
	f.close()
	return (md5.hexdigest())

def removeFile(file):
	global _NumOfDelFiles
	
	_NumOfDelFiles = _NumOfDelFiles + 1
	try:
		os.remove(file)
	except:
		print(file + " can't be deleted!")

def removeDupFiles():
	global _DistDir
	
	for root, dirs, files in os.walk(_DistDir, topdown=False):
		for name in files:
			if os.path.splitext(name)[1]=='.png':
				if name[0]=='.':
					removeFile(os.path.join(root, name))
					continue
				addNewMd5(os.path.join(root, name))
			else:
				removeFile(os.path.join(root, name))

def addNewMd5(file):
	global _MD5HashCode
	
	md5key = md5sum(file)
	if md5key in list(_MD5HashCode.keys()):
		try:
			print(file + ' is equal to ' + _MD5HashCode[md5key])
		except Exception as e:
			print(e)
		removeFile(file)
	else:
		_MD5HashCode[md5key] = file

if __name__=='__main__':
	removeDupFiles()
	print(str(_NumOfDelFiles) + ' files are deleted!')
	
	