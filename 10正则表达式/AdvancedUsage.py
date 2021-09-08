#!/usr/bin/python3
# -*- coding: UTF-8 -*-

import re
from functools import wraps

def print_header(func):

	@wraps(func)
	def decorate(*args, **kwargs):
	
		print("\n" + "*"*50)
		if func.__name__ == "re_multi_exp":
			print("多关键字匹配")
		elif func.__name__ == "re_forward_definition":
			print("前向界定")
		elif func.__name__ == "re_backward_reference":
			print("后向引用")
		elif func.__name__ == "re_greedy_nongreedy":
			print("贪婪与非贪婪")
		elif func.__name__ == "re_chinese_match":
			print("中文匹配")
			
		print("")
		ret = func(*args, **kwargs)
		#print("*"*3)
		return ret
		
	return decorate

@print_header
def re_multi_exp():
	'''
	使用 | 可以将不同的规则分隔开，从左到右的测试每个条件，如果满足了其中的一个分支的话，就不会再去测试其他的条件了。
	'''
	text = "xx,,xx=,-xy2,,@enD,"
	pattern = re.compile(r'[a-z]+|\d')
	rst = re.findall(pattern, text)
	print("匹配结果：")
	print(rst)

@print_header
def re_forward_definition():
	'''
	(?=exp) 零宽正向先行断言： 匹配exp前面的位置，也可以理解为 匹配，但不包含在结果内。
	'''
	text = "red,,white,and blue"
	pattern = re.compile(r'[a-z]+(?=,,)')
	rst = re.findall(pattern, text)
	print("示例1匹配结果：")
	print(rst)

	# 前向界定
	text = 'aa<div>test1</div>bb<div>test2</div>cc'
	print("示例2匹配结果：")
	print(re.search(r'.*(?=bb)', text).group())
	print(re.search(r'(?<=bb).*(?=cc)', text).group())
	
@print_header
def re_backward_reference():
	'''
	当我们需要匹配类似“taobao taobao”，“jingdong jingdong”这样的内容时，我们的正则表达式怎么写呢？可以使用  \b(\w+)\b\s+(\1)  来进行匹配。
	解释一下具体含义： \b(\w+)\b 表示匹配的内容为字符串，(\1) 表示后向引用第1分组的内容进行匹配，所以，最终我们就能匹配到上面我们提到的场景的内容。
	'''
	text = "taobao taobao, taobao jingdong, jingdong, jingdong jingdong"
	pattern = re.compile(r'\b(\w+)\b\s+(\1)')
	rst = re.findall(pattern, text)
	print("示例1匹配结果：")
	print(rst)

	# 将从被替换文字中匹配到的内容，作为替换后内容的一部分
	text = 'Today is 11/27/2018. PyCon starts 3/13/2018.'
	print("示例2匹配结果：")
	print(re.sub(r'(\d+)/(\d+)/(\d+)', r'\3-\1-\2', text))
	
@print_header
def re_greedy_nongreedy():
	'''
	贪婪与非贪婪匹配
	'''
	text = 'aa<div>test1</div>bb<div>test2</div>cc'
	print("匹配结果：")
	print(re.search(r'<div>.*</div>', text).group())  # 贪婪式
	print(re.search(r'<div>.*?</div>', text).group())  # 非贪婪式
	print(re.search(r'<div>.*</div>cc', text).group())  # 贪婪式
	print(re.search(r'<div>.*?</div>cc', text).group())  # 非贪婪式

@print_header
def re_chinese_match():
	'''
	匹配中文字符的正则表达式： [\u4e00 -\u9fa5], 匹配双字节字符(包括汉字在内)：[^\x00-\xff]
	'''
	text = '你好吗 world. I will come! 这个世界'
	pattern = re.compile('([\u4e00-\u9fa5]+)')
	results = pattern.findall(text)
	print("匹配结果：")
	print(results)
	
def run_re_example():

	re_multi_exp()
	
	re_forward_definition()

	re_backward_reference()
	
	re_greedy_nongreedy()
	
	re_chinese_match()

if __name__ == "__main__":

	run_re_example()

