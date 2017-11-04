#!/usr/bin/python3
# -*- coding: UTF-8 -*-

'''
https://pillow.readthedocs.io/en/latest/installation.html
PIL 安装
'''

_BaseDir = '.\\Base'
_NewDir = '.\\New'
#_ImgExt = '.png'
_ImgExt = '.jpg'

import os
import math
import operator
from functools import reduce
from PIL import Image

def compareImage(imgPathA, imgPathB):
	'''
	计算两种图片的相似度
	'''
	imageA=Image.open(imgPathA)
	imageB=Image.open(imgPathB)
	h1=imageA.histogram()
	h2=imageB.histogram()
	result = math.sqrt(reduce(operator.add,  list(map(lambda a,b: (a-b)**2, h1, h2)))/len(h1) )
	return result

def isImageEqual(imgPathA, imgPathB):

	boEqual = False
	imageA=Image.open(imgPathA)
	imageB=Image.open(imgPathB)
	if imageA.size!=imageB.size:
		return boEqual
	
	if compareImage(imgPathA, imgPathB) == 0.0:
		boEqual = True
	return boEqual

def compareImages():
	for root, dirs, files in os.walk(_NewDir, topdown=False):
		for name in files:
			if os.path.splitext(name)[1]==_ImgExt:
				if findImageInBase(os.path.join(root, name))==True:
					print(os.path.join(root, name) + " is found in base")
					os.remove(os.path.join(root, name))

def findImageInBase(imageNew):

	boFound = False
	for root, dirs, files in os.walk(_BaseDir, topdown=False):
		for name in files:
			if os.path.splitext(name)[1]==_ImgExt:
				if isImageEqual(os.path.join(root, name), imageNew) == True:
					boFound = True
					return boFound
	return boFound
	
if __name__ == '__main__':
	compareImages()


	
	
	
