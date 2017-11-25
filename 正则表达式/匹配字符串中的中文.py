import re



if __name__=='__main__':
	
	temp = '你好吗 world. I will come! 这个世界'
	pattern = re.compile('([\u4e00-\u9fa5]+)')
	results = pattern.findall(temp)
	print(results)