# -*- coding: UTF-8 -*-

import win32clipboard as wc
import win32con
import chardet
import time

def getCopyText():
	try:
		wc.OpenClipboard()
		copy_text = wc.GetClipboardData(win32con.CF_UNICODETEXT)
		wc.CloseClipboard()
	except:
		return ""
	else:
		return copy_text
	
def saveText(filename, content):
	outfile = open("copyLog.txt", "a", encoding="utf-8")
	outfile.write(content+'\n')
	outfile.close()


if __name__=="__main__":
	thePrevious = ""

	while True:
		time.sleep(0.1)
		theCurrent = getCopyText()
		if theCurrent!=thePrevious and theCurrent!="":
			print(theCurrent)
			saveText("save.txt", theCurrent)
			thePrevious = theCurrent
			
			
	