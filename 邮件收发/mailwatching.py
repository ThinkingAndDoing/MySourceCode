#!/usr/bin/python3
# -*- coding: UTF-8 -*-

import os
import sys
import time
import email
import poplib
from email.mime.text import MIMEText
from email.header import Header
from email.header import decode_header


'''
读取邮箱中所有邮件的标题
将标题作为进程名
杀死系统中所有存在于标题中的进程
每天读取一次邮件
每分钟检查一次系统中的进程
'''

__processpath = "processes.txt"

class getemail:
	maillist = []
	def __init__(self):
		self.host = "pop3.163.com"
		self.username = "xxx@163.com"
		self.password = "xxx"
		self.pp = poplib.POP3(self.host)	# 创建一个pop3对象，这个时候实际上已经连接上服务器了
		
	def login(self):
		#self.pp.set_debuglevel(1)	# 设置调试模式，可以看到与服务器的交互信息
		self.pp.user(self.username)	# 向服务器发送用户名
		self.pp.pass_(self.password)	# 向服务器发送密码
		
	def getmailboxinfo(self):
		ret = self.pp.stat()	# 获取服务器上信件信息，返回是一个列表，第一项是一共有多少封邮件，第二项是共有多少字节
		print(ret)
		# 需要取出所有信件的头部，信件id是从1开始的。
		for i in range(1, ret[0]+1):
			# 取出信件头部。注意：top指定的行数是以信件头为基数的，也就是说当取0行，
			# 其实是返回头部信息，取1行其实是返回头部信息之外再多1行。
			mlist = self.pp.top(i, 0)
			print('line: ', len(mlist[1]))
		ret = self.pp.list()	# 列出服务器上邮件信息，这个会对每一封邮件都输出id和大小。不象stat输出的是总的统计信息
		
	def getemails(self):
		ret = self.pp.stat()
		for i in range(1, ret[0]+1):
			aMail = ""
			down = self.pp.retr(i)	# 遍历所有邮件完整信息，在返回值里，是按行存储在down[1]的列表里的。down[0]是返回的状态信息
			for line in down[1]:	# 输出邮件
				aMail += line.decode("utf-8")+'\n'
			self.maillist.append(aMail)
		
	def quit(self):
		self.pp.quit()

def killprocess(processName):
	cmd = 'tasklist | find "' + processName + '"'
	status = os.system(cmd)
	if status==0:
		cmd = 'taskkill /F /IM ' + processName
		os.system(cmd)
		print(processName+' is killed!')
	else:
		print(processName+' is not found!')

def addrule(rule):
	if os.path.splitext(rule)[-1]=='.exe':
		killprocess(rule)

def decodemailheader(subject):
	list = decode_header(subject)
	if list[0][1] is None:
		return list[0][0]
	else:
		return list[0][0].decode(list[0][1])

def reademail(mail):
	msg = email.message_from_string(mail)
	subject = msg.get("Subject")
	subject = decodemailheader(subject)
	mailsrc = email.utils.parseaddr(msg.get("from"))[1]
	if mailsrc=="xiewei23703@163.com" or mailsrc=="xiewei23703@126.com":
		addrule(subject)
		return subject
	else:
		return ""

def readprocessfromfile():
	try:
		f = open(__processpath, "r", encoding='utf-8')
		for line in f.readlines:
			line.replace("\n","")
			if line!="":
				killprocess(line)
	except:
		print("Do nothing!")

def isonedaypassd():
	if os.path.exists(__processpath) and os.path.isfile(__processpath):
		#mtime = time.ctime(os.path.getmtime(__processpath))
		createtime = time.localtime(os.path.getctime(__processpath))
		curtime = time.localtime(time.time())
		if createtime.tm_year==curtime.tm_year and createtime.tm_mon==curtime.tm_mon and createtime.tm_mday!=curtime.tm_mday:
			return True
		else:
			return False
	else:
		return True

def run():
	flag = isonedaypassd()
	if flag:
		try:
			pop = getemail()
			pop.login()
			pop.getemails()
			#print(pop.maillist)
			f = open(__processpath, "w", encoding='utf-8')
			for mail in pop.maillist:
				pn = reademail(mail)
				if pn!="":
					f.write(pn+'\n')
			f.close()
			pop.quit()
		except:
			readprocessfromfile()
	else:
		readprocessfromfile()

while True:
	run()
	time.sleep(60)