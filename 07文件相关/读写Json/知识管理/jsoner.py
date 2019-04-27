#!/usr/bin/python3 
# -*- coding: UTF-8 -*- 

import json 

def writeJson(fn, js): 
	with open(fn, 'w') as f: 
		json.dump(js, f, indent=4, ensure_ascii=False) 

def readJson(fn): 
	with open(fn, 'r') as f: 
		data = json.load(f) 
		return eval(str(data)) 

if __name__ == "__main__": 
	print("hello")
