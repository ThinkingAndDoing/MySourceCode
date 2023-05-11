#!/usr/bin/python3
# -*- coding: UTF-8 -*-

#import shutil
import os
import codecs
import chardet
import argparse


_TEXT_BOMS = (
	codecs.BOM_UTF16_BE,
	codecs.BOM_UTF16_LE,
	codecs.BOM_UTF32_BE,
	codecs.BOM_UTF32_LE,
	codecs.BOM_UTF8,
	)
	
def get_args():
	#python findstr.py -h

	parser = argparse.ArgumentParser()
	parser.add_argument("-sr", "--saveresult", help="Whether to keep the search results or not.", default=r"no")
	parser.add_argument("-ft", "--filetype", help="Search for specific file types.", default='.*')
	
	args = parser.parse_args()
	
	return args
	
class StringSearcher(object):

	def __init__(self, kw, sp="."):
		self.searchRst = "SearchResult.txt"
		self.keyWord = kw
		self.searchPath = sp
		self.searchArgs = None
		self.searchedFileNum = 0
		
	def set_search_args(self, args):
		self.searchArgs = args

	def save_to_local(data):
		f = open(self.searchRst, "w")
		f.write(data+"\n")
		f.close()
	
	def is_binary_file(self, file_path):
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

	def get_char_encode(self, fileName):
		file = open(fileName, "rb")		#要有"rb"，如果没有这个的话，默认使用gbk读文件。
		buf = file.read()
		file.close()
		result = chardet.detect(buf)
		return result["encoding"]
	
	def find_str_in_file(self, saveRst, fileName):
		
		if self.is_binary_file(fileName)==False:
			f = open(fileName, "r", encoding = self.get_char_encode(fileName))
			data = f.read()
			
			if data.find(self.keyWord)!=-1:
				print(fileName)
				if saveRst == "yes":
					self.save_to_local(fileName)
			
			f.close()
			self.searchedFileNum = self.searchedFileNum+1
			
	def start_to_search(self):
		print("Search result as follows:")
		
		for root, dirs, files in os.walk(self.searchPath, topdown=False):
		
			if root.find(".git")!=-1:
				continue
				
			for name in files:
				try:
					if self.searchArgs.filetype == ".*" or os.path.splitext(name)[1] in self.searchArgs.filetype.split(";"):
						self.find_str_in_file(self.searchArgs.saveresult, os.path.join(root, name))
						
				except Exception as e:
					print("\n%s at %s" % (str(e), os.path.join(root, name)))
					pass
					
		print("\n[ %d ] file searched!"%(self.searchedFileNum))
		
if __name__=="__main__":
	#Warning ID:
	args = get_args()
	
	print("Please input the string to search:")
	strInput = input()
	
	SS = StringSearcher(strInput, os.getcwd())
	SS.set_search_args(args)
	SS.start_to_search()

		
		
		
		
		