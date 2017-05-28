#!/usr/bin/python
# -*- coding: UTF-8 -*-
 
import poplib
import smtplib
from email.mime.text import MIMEText
from email.header import Header

class sendemail:
	def __init__(self):
		self.mail_host="smtp.163.com"
		self.mail_user="15192535292@163.com"
		self.mail_pass="***"
		self.sender = '15192535292@163.com'
		self.receiver = 'xiewei23703@163.com'  # 接收邮件，可设置为你的QQ邮箱或者其他邮箱
		self.smtpObj = smtplib.SMTP()
		self.content = ""
		self.subject = ""

	def setHeader(self, str):
		self.subject = str
	
	def setContent(self, str):
		self.content = str

	def login(self):
		try:
			self.smtpObj.connect(self.mail_host, 25)    # 25 为 SMTP 端口号
			self.smtpObj.login(self.mail_user, self.mail_pass)
		except smtplib.SMTPException as e:
			print("Error: 无法登陆邮箱")
			print("Exception：",e)
	
	def getMessage(self):
		message = MIMEText(self.content, 'plain')
		message['From'] = "Robet" + "<"+ self.sender +">" #Fix error: 554 DT:SPM
		message['To'] =  "XieWei" + "<"+ self.receiver +">" #Fix error: 554 DT:SPM
		message['Subject'] = self.subject
		return message

	def send(self):
		try:
			message = self.getMessage()
			self.smtpObj.sendmail(self.sender, self.receiver, message.as_string())
			print("邮件发送成功")
		except smtplib.SMTPException as e:
			print(self.message)
			print("Error: 无法发送邮件")
			print("Exception：",e)
			
	def close(self):
		self.smtpObj.close()
	
def testSendEmail():
	smpt = sendemail()
	smpt.login()
	smpt.setHeader("au Price")
	smpt.setContent("180")
	smpt.send()
	smpt.close()

#testSendEmail()
