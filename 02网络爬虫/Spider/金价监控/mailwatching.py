#!/usr/bin/python3
# -*- coding: UTF-8 -*-

import os
import sys
import time
import pickle as p

import getemail
import reademail
import au99watching

'''
读取邮箱中所有邮件的标题
将标题作为进程名
杀死系统中所有存在于标题中的进程
每天读取一次邮件
每分钟检查一次系统中的进程
'''

__processpath = "C:\\ProgramData\\processes.txt"

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

def readprocessfromfile():
	try:
		f = open(__processpath, "rb")
		tasknamelist = p.load(f)
		print("read list:")
		print(tasknamelist)
		for tn in tasknamelist:
			addrule(tn)
	except Exception as e:
		print("exception:",e)

def writeprocesstofile(tnlist):
	try:
		f = open(__processpath, "wb")
		print("write list:")
		print(tnlist)
		p.dump(tnlist, f)
		f.close()
	except Exception as e:
		print("exception:",e)

def isonedaypassd():
	if os.path.exists(__processpath) and os.path.isfile(__processpath):
		modifytime = time.localtime(os.path.getmtime(__processpath))
		#createtime = time.localtime(os.path.getctime(__processpath))
		curtime = time.localtime(time.time())
		if modifytime.tm_year==curtime.tm_year and modifytime.tm_mon==curtime.tm_mon and modifytime.tm_mday!=curtime.tm_mday:
			return True
		else:
			return False
	else:
		return True

def gettasknamelist(emllist):
	tasknamelist = []
	for mail in emllist:
		eml = reademail.ReadEmail(mail)
		sender = eml.getsender()
		if sender=="xiewei23703@163.com" or sender=="xiewei23703@126.com":
			pn = eml.getsubject()
			if pn!="":
				tasknamelist.append(pn)
	return tasknamelist

def run():
	flag = isonedaypassd()
	if flag:
		try:
			print("Start to get emails!")
			pop = getemail.GetEmail()
			pop.login()
			emls = pop.getemails()
			pop.quit()
			
			tasknamelist = gettasknamelist(emls)
			writeprocesstofile(tasknamelist)
		except:
			readprocessfromfile()
		else:
			# get au price of yesterday.
			au99watching.getAuPrice()
	else:
		readprocessfromfile()

if __name__ == "__main__":
	while True:
		run()
		#time.sleep(1)
		time.sleep(60)

