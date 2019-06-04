#!/usr/bin/python
# -*- coding: UTF-8 -*-
 
import poplib
import smtplib
from email.mime.text import MIMEText
from email.header import Header

class EmailSender:
	def __init__(self):
		self.mail_host= "smtp.163.com"
		self.mail_user= "15192535292@163.com"
		self.mail_pass= "***"
		self.sender = '15192535292@163.com'
		self.receiver = '610980236@qq.com'  # 接收邮件，可设置为你的QQ邮箱或者其他邮箱
		self.smtpObj = smtplib.SMTP()
		self.content = ""
		self.subject = ""

	def setReceiver(self, receiver):
		self.receiver = receiver

	def setSender(self, host, user, password, sender):
		self.mail_host= host
		self.mail_user= user
		self.mail_pass= password
		self.sender = sender

	def setHeader(self, str):
		self.subject = str

	def setContent(self, str):
		self.content = str

	def login(self):
		try:
			self.smtpObj.connect(self.mail_host, 25)    # 25 为 SMTP 端口号
			self.smtpObj.login(self.mail_user, self.mail_pass)
		except smtplib.SMTPException as e:
			print("Error: 无法登陆邮箱"+self.mail_user)
			print("Exception：",e)
			return False
		else:
			return True

	def getMessage(self):
		message = MIMEText(self.content, 'plain')
		message['From'] = "<"+ self.sender +">" #Fix error: 554 DT:SPM
		message['To'] = "<"+ self.receiver +">" #Fix error: 554 DT:SPM
		message['Subject'] = self.subject
		return message

	def send(self):
		try:
			message = self.getMessage()
			self.smtpObj.sendmail(self.sender, self.receiver, message.as_string())
			print("邮件发送成功")
		except smtplib.SMTPException as e:
			print("Error: "+self.mail_user+"无法发送邮件")
			print("Exception：",e)
			return False
		else:
			return True

	def logout(self):
		self.smtpObj.close()

def sendEmail(header, content, senderList):
	smpt = EmailSender()
	smpt.setHeader(header)
	smpt.setContent(content)

	for sender in senderList:
		smpt.setSender(sender['host'], sender['user'], sender['pwd'], sender['user'])
		if smpt.login()==True:
			sendStatus = smpt.send()
			smpt.logout()
			if sendStatus==True:
				return True

if __name__ == "__main__":
	senderList = []
	senderList.append({"host":"smtp.163.com", "user":"15192535292@163.com", "pwd":"554637you"})
	senderList.append({"host":"smtp.sina.com", "user":"xiewei23703@sina.com", "pwd":"554637you[]"})
	sendEmail("Hello world!", "It is amazing!", senderList)



