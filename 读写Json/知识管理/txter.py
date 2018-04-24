#!/usr/bin/python3 
# -*- coding: UTF-8 -*- 


def loadFromLocal(fn):
	f = open(fn, "r")
	data = f.read()
	f.close()
	return data

def saveToLocal(fn, data): 
	f = open(fn, "w") 
	f.write(data) 
	f.close() 

if __name__ == "__main__": 
	print("hello")
