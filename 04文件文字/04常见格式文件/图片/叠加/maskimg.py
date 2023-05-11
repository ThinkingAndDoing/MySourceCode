#!/usr/bin/python3
# -*- coding: UTF-8 -*-

import cv2
import time
import pandas as pd

	

	
def generatePics(df):
	
	rows = df.shape[0]
	for i in range(0, rows):
		offsetx = df.loc[i,"XOffsetOfBottom"]
		offsety = df.loc[i,"YOffsetOfBottom"]
		bottompic = df.loc[i,"BottomPic"]
		toppic = df.loc[i,"TopPic"]
		
		try:
			maskImg(offsetx, offsety, bottompic, toppic)
		except Exception as e:
			print(e)

		

def maskImg(offsetX, offsetY, bottomPic, topPic):
	# 偏移量
	iXOffsetOfBottom = offsetX
	iYOffsetOfBottom = offsetY
	# 底板图案
	bottom_pic = bottomPic
	# 上层图案
	top_pic = topPic
	
	bottom = cv2.imread(bottom_pic, cv2.IMREAD_UNCHANGED)
	top = cv2.imread(top_pic, cv2.IMREAD_UNCHANGED)

	h, w = top.shape[:2]
	bottom_fragment = bottom[iYOffsetOfBottom:h+iYOffsetOfBottom, iXOffsetOfBottom:w+iXOffsetOfBottom]
	
	#img2 = cv2.resize(top, (w,h), interpolation=cv2.INTER_AREA)
	#alpha，beta，gamma可调
	bottom_alpha = 0
	top_alpha = 1-bottom_alpha
	gamma = 0
	# 权重越大，透明度越低
	new_fragment = cv2.addWeighted(bottom_fragment, bottom_alpha, top, top_alpha, gamma) 
	new_img = bottom.copy()
	new_img[iYOffsetOfBottom:h+iYOffsetOfBottom, iXOffsetOfBottom:w+iXOffsetOfBottom] = new_fragment

	# 保存叠加后的图片
	cv2.imwrite("output\\" + bottom_pic.split("\\")[1], new_img)
	#cv2.imwrite(str(time.time())+'.png', new_img)
	"""
	# 显示叠加后的图片
	cv2.namedWindow('newImage')
	cv2.imshow('newImage', bottom)
	cv2.waitKey()
	cv2.destroyAllWindows()
	"""

if __name__=="__main__":

	'''
	maskimg.csv
	XOffsetOfBottom,YOffsetOfBottom,BottomPic,TopPic
	27,23,src\wrn_tt_SuspensionRed.png,"src\wrn_tt_SuspensionRed(VSync5,orange,806ceca6).png"
	41,21,src\gear_P.png,"src\gear_P(VSync6,orange,6f704e42).png"
	27,23,src\wrn_tt_SuspensionYellow.png,"src\wrn_tt_SuspensionYellow(VSync4,orange,23bc4757).png"
	18,23,src\wrn_tt_BrakeRed.png,"src\wrn_tt_BrakeRed(VSync3,orange,569f209c).png"
	17,23,src\wrn_tt_ABSLamp.png,"src\wrn_tt_ABSLamp(VSync2,orange,e5b32bb).png"
	18,33,src\wrn_tt_ESCOFF.png,"src\wrn_tt_ESCOFF(VSync1,orange,96ac8c01).png"
	'''
	data = pd.read_csv("maskimg.csv")
	generatePics(data)
	
	
	
