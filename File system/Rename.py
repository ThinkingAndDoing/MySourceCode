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
	
def renameAll(length):
	videolist = []
	list = os.listdir(".")
	for item in list:
		if item.find("mp4")!=-1:
			videolist.append(item)

	indexA = 1
	indexB = 1
	for item in videolist:
		if item.find("A")!=-1:
			formatStr = "A"+getFormatStr(length, indexA)+"%d.mp4"
			os.rename(item, formatStr%indexA)
			indexA += 1
	
		if item.find("B")!=-1:
			formatStr = "B"+getFormatStr(length, indexB)+"%d.mp4"
			os.rename(item, formatStr%indexB)
			indexB += 1

renameAll(4)
renameAll(3)
