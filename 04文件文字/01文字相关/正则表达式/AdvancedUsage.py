#!/usr/bin/python3
# -*- coding: UTF-8 -*-

import re
from functools import wraps



#https://baijiahao.baidu.com/s?id=1712491497500869183&wfr=spider&for=pc
#https://zhuanlan.zhihu.com/p/127807805
#https://www.runoob.com/python/python-reg-expressions.html


def print_header(func):

	@wraps(func)
	def decorate(*args, **kwargs):
	
		print("\n● ", end="")
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
		elif func.__name__ == "re_exclude_match":
			print("一行中不包含某个字符串")
		else:
			print("XXX匹配")
			
		#print("\n"*2)
		ret = func(*args, **kwargs)
		print("\n"*2)
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
	print("原文："+text+"\n")
	print("匹配结果：")
	print(rst)  #['xx', 'xx', 'xy', '2', 'en']

@print_header
def re_forward_definition():
	'''
	(?=exp) 零宽正向先行断言： 匹配exp前面的位置，也可以理解为 匹配，但不包含在结果内。
	'''
	text = "red,,white,and blue"
	pattern = re.compile(r'[a-z]+(?=,,)')
	rst = re.findall(pattern, text)
	print("原文："+text+"\n")
	print("示例1匹配结果：")
	print(rst)  #['red']

	# 前向界定
	text = 'aa<div>test1</div>bb<div>test2</div>cc'
	print("原文："+text+"\n")
	print("示例2匹配结果：")
	print(re.search(r'.*(?=bb)', text).group())  #aa<div>test1</div>
	print(re.search(r'(?<=bb).*(?=cc)', text).group())  #<div>test2</div>
	
@print_header
def re_backward_reference():
	'''
	当我们需要匹配类似“taobao taobao”，“jingdong jingdong”这样的内容时，我们的正则表达式怎么写呢？可以使用  \b(\w+)\b\s+(\1)  来进行匹配。
	解释一下具体含义： \b(\w+)\b 表示匹配的内容为字符串，(\1) 表示后向引用第1分组的内容进行匹配，所以，最终我们就能匹配到上面我们提到的场景的内容。
	'''
	text = "taobao taobao, taobao jingdong, jingdong, jingdong jingdong"
	pattern = re.compile(r'\b(\w+)\b\s+(\1)')
	rst = re.findall(pattern, text)
	print("原文："+text+"\n")
	print("示例1匹配结果：")
	print(rst)  #[('taobao', 'taobao'), ('jingdong', 'jingdong')]

	# 将从被替换文字中匹配到的内容，作为替换后内容的一部分
	text = 'Today is 11/27/2018. PyCon starts 3/13/2018.'
	print("原文："+text+"\n")
	print("示例2匹配结果：")
	print(re.sub(r'(\d+)/(\d+)/(\d+)', r'\3-\1-\2', text))  #Today is 2018-11-27. PyCon starts 2018-3-13.
	
@print_header
def re_greedy_nongreedy():
	'''
	贪婪与非贪婪匹配
	'''
	text = 'aa<div>test1</div>bb<div>test2</div>cc'
	print("原文："+text+"\n")
	print("匹配结果：")
	print(re.search(r'<div>.*</div>', text).group())  # 贪婪式，<div>test1</div>bb<div>test2</div>
	print(re.search(r'<div>.*?</div>', text).group())  # 非贪婪式，<div>test1</div>
	print(re.search(r'<div>.*</div>cc', text).group())  # 贪婪式，<div>test1</div>bb<div>test2</div>cc
	print(re.search(r'<div>.*?</div>cc', text).group())  # 非贪婪式，<div>test1</div>bb<div>test2</div>cc

@print_header
def re_chinese_match():
	'''
	匹配中文字符的正则表达式： [\u4e00 -\u9fa5], 匹配双字节字符(包括汉字在内)：[^\x00-\xff]
	'''
	text = '你好吗 world. I will come! 这个世界'
	pattern = re.compile('([\u4e00-\u9fa5]+)')
	results = pattern.findall(text)
	print("原文："+text+"\n")
	print("匹配结果：")
	print(results)  #['你好吗', '这个世界']
	
@print_header
def re_exclude_match():
	'''
	匹配不包含 "MsgID_" 的一行
	'''
	text = '11.22 MsgID_Pre!\r\n we are the world!\r\n 2.11 MsgID_Has!\r\n 11.33'
	pattern = re.compile('^(?!.*MsgID_).*$', re.M)
	results = pattern.findall(text)
	print("原文："+text+"\n")
	print("匹配结果：")
	print(results)  #[' we are the world!\r', ' 11.33']


def run_re_example():

	re_multi_exp()
	
	re_forward_definition()

	re_backward_reference()
	
	re_greedy_nongreedy()
	
	re_chinese_match()

	re_exclude_match()
	
	
if __name__ == "__main__":

	run_re_example()

