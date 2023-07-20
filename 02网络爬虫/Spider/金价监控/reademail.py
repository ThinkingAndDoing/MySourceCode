#!/usr/bin/python3
# -*- coding: UTF-8 -*-


import email
from email.mime.text import MIMEText
from email.header import Header
from email.header import decode_header


class ReadEmail:
    def __init__(self, email):
        self.eml = email
        self.msg = ""
        self.subject = ""
        self.sender = ""
        self.parse()

    def parse(self):
        self.msg = email.message_from_string(self.eml)

    def decodemailheader(self):
        list = decode_header(self.subject)
        if list[0][1] is None:
            self.subject = list[0][0]
        else:
            self.subject = list[0][0].decode(list[0][1])

    def getsubject(self):
        self.subject = self.msg.get("Subject")
        self.decodemailheader()
        return self.subject

    def getsender(self):
        self.sender = email.utils.parseaddr(self.msg.get("from"))[1]
        return self.sender
