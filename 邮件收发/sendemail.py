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
		self.receivers = ['15192535292@163.com']  # 接收邮件，可设置为你的QQ邮箱或者其他邮箱
		self.smtpObj = smtplib.SMTP()
		self.message = MIMEText(b'This is the content...', 'plain', 'utf-8')
		self.message['From'] = Header(b"Sender", 'utf-8')
		self.message['To'] =  Header(b"Receiver", 'utf-8')
		subject = b'This is the subject'
		self.message['Subject'] = Header(subject, 'utf-8')

	def login(self):
		try:
			self.smtpObj.connect(self.mail_host, 25)    # 25 为 SMTP 端口号
			self.smtpObj.login(self.mail_user, self.mail_pass)
		except smtplib.SMTPException as e:
			print("Error: 无法登陆邮箱")
			print("Exception：",e)
	
	def send(self):
		try:
			self.smtpObj.sendmail(self.sender, self.receivers, self.message.as_string())
			print("邮件发送成功")
		except smtplib.SMTPException as e:
			print("Error: 无法发送邮件")
			print("Exception：",e)
	
def testSendEmail():
	smpt = sendemail()
	smpt.login()
	smpt.send()

testSendEmail()
