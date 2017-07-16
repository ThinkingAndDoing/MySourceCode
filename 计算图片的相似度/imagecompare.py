#!/usr/bin/python3
# -*- coding: UTF-8 -*-

'''
https://pillow.readthedocs.io/en/latest/installation.html
PIL 安装
'''

_BaseDir = '.\\Base'
_NewDir = '.\\New'

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



if __name__ == '__main__':
	baseImgs = os.listdir(_BaseDir)
	for pic in os.listdir(_NewDir):
		if pic.find(".png")==-1:
			continue
		for bp in baseImgs:
			if compareImage(_BaseDir+"\\"+bp, _NewDir+"\\"+pic) == 0.0:
				print(pic + " is found in base")
				os.remove(_NewDir+"\\"+pic)
				break
