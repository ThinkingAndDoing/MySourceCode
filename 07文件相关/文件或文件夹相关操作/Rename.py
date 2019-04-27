#!/usr/bin/python3
# -*- coding: UTF-8 -*-
import os

def getFormatStr(length, value):
	if value<0 or length<=0:
		return "error"
		
	if value == 0:
		return "000"
	
	prefix = ""
	x = length-1
	while x>=0 and value<=pow(10,x)-1:
		prefix += "0"
		x -= 1
	return prefix

def renameVideo(origin, target):
	if os.path.exists(target):
		print(target + " is already exist! " + origin +" will not be renamed!")
	else:
		os.rename(origin, target)
	
def renameAll(length):
	videolist = []
	list = os.listdir(".")
	for item in list:
		ext = item.split(".")
		if ext[1]!="bat" and ext[1]!="py":
			videolist.append(item)

	indexA = 1
	indexB = 1
	indexS = 1
	for item in videolist:
		if item.find("A")!=-1:
			formatStr = "A"+getFormatStr(length, indexA)+"%d."+item.split(".")[1]
			renameVideo(item, formatStr%indexA)
			indexA += 1
	
		if item.find("B")!=-1:
			formatStr = "B"+getFormatStr(length, indexB)+"%d."+item.split(".")[1]
			renameVideo(item, formatStr%indexB)
			indexB += 1

		if item.find("S")!=-1:
			formatStr = "S"+getFormatStr(length, indexS)+"%d."+item.split(".")[1]
			renameVideo(item, formatStr%indexS)
			indexS += 1

if __name__=="__main__":
	
	renameAll(3)
	renameAll(4)
	renameAll(3)
	
