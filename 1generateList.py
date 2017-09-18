#!/usr/bin/python3
# -*- coding: UTF-8 -*-

'''
http://www.cnblogs.com/nbkhic/p/4216115.html
http://blog.csdn.net/abclixu123/article/details/38502993
https://robobrowser.readthedocs.io/en/latest/api.html#module-robobrowser.browser
http://cuiqingcai.com/1319.html
https://www.crummy.com/software/BeautifulSoup/bs4/doc/index.zh.html
'''

'''
1）name 参数
name 参数可以查找所有名字为 name 的tag,字符串对象会被自动忽略掉
A.传字符串
最简单的过滤器是字符串.在搜索方法中传入一个字符串参数,Beautiful Soup会查找与字符串完整匹配的内容,下面的例子用于查找文档中所有的<b>标签
soup.find_all('b')
# [<b>The Dormouse's story</b>]

B.传正则表达式
如果传入正则表达式作为参数,Beautiful Soup会通过正则表达式的 match() 来匹配内容.下面例子中找出所有以b开头的标签,这表示<body>和<b>标签都应该被找到
import re
for tag in soup.find_all(re.compile("^b")):
    print(tag.name)
# body
# b

C.传列表
如果传入列表参数,Beautiful Soup会将与列表中任一元素匹配的内容返回.下面代码找到文档中所有<a>标签和<b>标签
soup.find_all(["a", "b"])
# [<b>The Dormouse's story</b>,
#  <a class="sister" href="http://example.com/elsie" id="link1">Elsie</a>,
#  <a class="sister" href="http://example.com/lacie" id="link2">Lacie</a>,
#  <a class="sister" href="http://example.com/tillie" id="link3">Tillie</a>]

D.传 True
True 可以匹配任何值,下面代码查找到所有的tag,但是不会返回字符串节点
for tag in soup.find_all(True):
    print(tag.name)
# html
# head
# title
# body
# p
# b
# p
# a
# a

E.传方法
如果没有合适过滤器,那么还可以定义一个方法,方法只接受一个元素参数 [4] ,如果这个方法返回 True 表示当前元素匹配并且被找到,如果不是则反回 False
下面方法校验了当前元素,如果包含 class 属性却不包含 id 属性,那么将返回 True:
def has_class_but_no_id(tag):
    return tag.has_attr('class') and not tag.has_attr('id')
将这个方法作为参数传入 find_all() 方法,将得到所有<p>标签:
soup.find_all(has_class_but_no_id)
# [<p class="title"><b>The Dormouse's story</b></p>,
#  <p class="story">Once upon a time there were...</p>,
#  <p class="story">...</p>]

2）keyword 参数
注意：如果一个指定名字的参数不是搜索内置的参数名,搜索时会把该参数当作指定名字tag的属性来搜索,如果包含一个名字为 id 的参数,Beautiful Soup会搜索每个tag的”id”属性
soup.find_all(id='link2')
# [<a class="sister" href="http://example.com/lacie" id="link2">Lacie</a>]
如果传入 href 参数,Beautiful Soup会搜索每个tag的”href”属性
soup.find_all(href=re.compile("elsie"))
# [<a class="sister" href="http://example.com/elsie" id="link1">Elsie</a>]
使用多个指定名字的参数可以同时过滤tag的多个属性
soup.find_all(href=re.compile("elsie"), id='link1')
# [<a class="sister" href="http://example.com/elsie" id="link1">three</a>]
在这里我们想用 class 过滤，不过 class 是 python 的关键词，这怎么办？加个下划线就可以
soup.find_all("a", class_="sister")
# [<a class="sister" href="http://example.com/elsie" id="link1">Elsie</a>,
#  <a class="sister" href="http://example.com/lacie" id="link2">Lacie</a>,
#  <a class="sister" href="http://example.com/tillie" id="link3">Tillie</a>]
有些tag属性在搜索不能使用,比如HTML5中的 data-* 属性
data_soup = BeautifulSoup('<div data-foo="value">foo!</div>')
data_soup.find_all(data-foo="value")
# SyntaxError: keyword can't be an expression
但是可以通过 find_all() 方法的 attrs 参数定义一个字典参数来搜索包含特殊属性的tag
data_soup.find_all(attrs={"data-foo": "value"})
# [<div data-foo="value">foo!</div>]

3）text 参数
通过 text 参数可以搜搜文档中的字符串内容.与 name 参数的可选值一样, text 参数接受 字符串 , 正则表达式 , 列表, True
soup.find_all(text="Elsie")
# [u'Elsie']
soup.find_all(text=["Tillie", "Elsie", "Lacie"])
# [u'Elsie', u'Lacie', u'Tillie']
soup.find_all(text=re.compile("Dormouse"))
[u"The Dormouse's story", u"The Dormouse's story"]

4）limit 参数
find_all() 方法返回全部的搜索结构,如果文档树很大那么搜索会很慢.如果我们不需要全部结果,可以使用 limit 参数限制返回结果的数量.效果与SQL中的limit关键字类似,当搜索到的结果数量达到 limit 的限制时,就停止搜索返回结果.
文档树中有3个tag符合搜索条件,但结果只返回了2个,因为我们限制了返回数量
soup.find_all("a", limit=2)
# [<a class="sister" href="http://example.com/elsie" id="link1">Elsie</a>,
#  <a class="sister" href="http://example.com/lacie" id="link2">Lacie</a>]


'''
import re
import os
from robobrowser import RoboBrowser

_FileName = 'urllist.txt'
_UrlListName = 'list.txt'

def getUrlList(fn):
	f = open(fn, 'w+', encoding='utf-8')
	list = f.read().split('\n')
	f.close()
	return list

def has_logr(tag):
	'''
	content = b.find_all(has_logr)
	content = b.find_all(class_='info rel')
	content = b.find_all(class_='f-list-item')
	content = b.find_all('dt', class_='img rel floatl')
	content = b.select('dt[class="img rel floatl"] a')
		for link in content:
			listOutput.append("http://esf.nanjing.fang.com" + link.get('href') + "\n")
	'''
	return tag.has_attr('logr')

def writeListToFile(file, list):
	f = open(file, "w+", encoding='utf-8')
	for item in list:
		f.write(str(item))
	f.close()

class MyRoboBrowser:
	def __init__(self):
		user_agent = 'Mozilla/5.0 (Windows NT 10.0; WOW64; rv:47.0) Gecko/20100101 Firefox/47.0'
		self.browser = RoboBrowser(history=True, user_agent=user_agent, parser='html.parser')
		self.tag = ""
		self.id = "PageControl1_hlk_next"
		self.clss = ""
		self.select = 'dt[class="img rel floatl"] a'
		
	def findHtmlTags(self, url):
		self.browser.open(url)
		content = self.browser.find_all(name=self.tag, class_=self.clss)
		return content
		
	def selectHtmlTags(self, url):
		self.browser.open(url)
		content = self.browser.select(self.select)
		'''
		for link in content:
			listOutput.append("http://esf.nanjing.fang.com" + link.get('href') + "\n")
		'''
		

def readList(urllist):
	user_agent = 'Mozilla/5.0 (Windows NT 10.0; WOW64; rv:47.0) Gecko/20100101 Firefox/47.0'
	b = RoboBrowser(history=True, user_agent=user_agent, parser='html.parser')
	
	listOutput = []
	for url in urllist:
		if url=='':
			continue

		b.open(url)
		#print(url) 
		content = b.select('dt[class="img rel floatl"] a')<a id="PageControl1_hlk_next" href="/house-a0268-b0606/c2120-d2180-i32-l3100/">下一页</a>
		for link in content:
			listOutput.append("http://esf.nanjing.fang.com" + link.get('href') + "\n")
	return listOutput

if __name__ == "__main__":
	if os.path.isfile(_FileName):
		os.remove(_FileName)
	listOutput = readList(getUrlList(_UrlListName))
	list = listOutput + getUrlList(_FileName)
	writeListToFile(_FileName, list)




	

	
