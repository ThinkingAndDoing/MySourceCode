#!/usr/bin/python
# -*- coding: UTF-8 -*-

import os
import poplib
import smtplib
from email.mime.text import MIMEText
from email.header import Header
import configparser


def get_conf_from_local():
    conf = configparser.ConfigParser()
    root_path = os.getcwd()
    conf.read(root_path + "\\configuration\\mail.conf")
    return conf


class sendemail:
    def __init__(self):
        conf = get_conf_from_local()
        self.mail_host = conf.get("sender", "mail_host")
        self.mail_user = conf.get("sender", "mail_user")
        self.mail_pass = conf.get("sender", "mail_pass")
        self.sender = self.mail_user
        self.receiver = ""  # 接收邮件，可设置为你的QQ邮箱或者其他邮箱
        self.smtpObj = smtplib.SMTP()
        self.content = ""
        self.subject = ""

    def set_header(self, str):
        self.subject = str

    def set_content(self, str):
        self.content = str

    def login(self):
        try:
            self.smtpObj.connect(self.mail_host, 25)  # 25 为 SMTP 端口号
            self.smtpObj.login(self.mail_user, self.mail_pass)
        except smtplib.SMTPException as e:
            print("Error: 无法登陆邮箱")
            print("Exception：", e)

    def get_message(self):
        message = MIMEText(self.content, "plain")
        message["From"] = "Robet" + "<" + self.sender + ">"  # Fix error: 554 DT:SPM
        message["To"] = "XW" + "<" + self.receiver + ">"  # Fix error: 554 DT:SPM
        message["Subject"] = self.subject
        return message

    def send_to(self, r):
        self.receiver = r
        try:
            message = self.get_message()
            self.smtpObj.sendmail(self.sender, self.receiver, message.as_string())
            print("邮件发送成功")
        except smtplib.SMTPException as e:
            print(self.message)
            print("Error: 无法发送邮件")
            print("Exception：", e)

    def close(self):
        self.smtpObj.close()


def testSendEmail():
    smpt = sendemail()
    smpt.login()
    smpt.set_header("au")
    smpt.set_content("180")
    smpt.send_to("xxx@163.com")
    smpt.close()


testSendEmail()
