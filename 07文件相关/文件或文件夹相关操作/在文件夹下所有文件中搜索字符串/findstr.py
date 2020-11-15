#!/usr/bin/python3
# -*- coding: UTF-8 -*-

#import shutil
import os
import codecs
import chardet


def getcharencode(filename):
	file = open(filename, "rb")#要有"rb"，如果没有这个的话，默认使用gbk读文件。          
	buf = file.read()
	file.close()
	result = chardet.detect(buf)
	return result["encoding"]

_TEXT_BOMS = (
	codecs.BOM_UTF16_BE,
	codecs.BOM_UTF16_LE,
	codecs.BOM_UTF32_BE,
	codecs.BOM_UTF32_LE,
	codecs.BOM_UTF8,
	)

	
def is_binary_file(file_path):
	with open(file_path, 'rb') as file:
		initial_bytes = file.read(8192)
		file.close()
		for bom in _TEXT_BOMS:
			if initial_bytes.startswith(bom):
				continue
			else:
				if b'\0' in initial_bytes:
					return True
	return False
	
def findStrInFiles(key, distpath):
	print("查询结果如下：")
	for root, dirs, files in os.walk(distpath, topdown=False):
	
		if root.find(os.getcwd()+"\\"+".git")!=-1:
			continue
			
		for name in files:
			try:
				if is_binary_file(os.path.join(root, name))==False:
					filename = os.path.join(root, name)
					f = open(filename, "r", encoding = getcharencode(filename))
					data = f.read()
					if data.find(key)!=-1:
						print(os.path.join(root, name))
						#saveToLocal(os.path.join(root, name))
					f.close()
			except Exception as e:
				#print("Failed to search file: " + os.path.join(root, name))
				pass

def saveToLocal(data):
	f = open("SearchResult.txt", "w")
	f.write(data+"\n")
	f.close()	
	
if __name__=="__main__":
	#Warning ID:
	print("请输入要查找的字符串！")
	strInput = input()
	findStrInFiles(strInput, os.getcwd())


		
		
		
		
		