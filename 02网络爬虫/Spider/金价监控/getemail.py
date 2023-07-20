#!/usr/bin/python3
# -*- coding: UTF-8 -*-

import poplib


class GetEmail:
    def __init__(self):
        self.host = "pop3.163.com"
        self.username = "15192535292@163.com"
        self.password = "***"
        self.pp = poplib.POP3(self.host)  # 创建一个pop3对象，这个时候实际上已经连接上服务器了
        self.maillist = []

    def login(self):
        # self.pp.set_debuglevel(1)	# 设置调试模式，可以看到与服务器的交互信息
        self.pp.user(self.username)  # 向服务器发送用户名
        self.pp.pass_(self.password)  # 向服务器发送密码

    def getmailboxinfo(self):
        ret = self.pp.stat()  # 获取服务器上信件信息，返回是一个列表，第一项是一共有多少封邮件，第二项是共有多少字节
        print(ret)
        # 需要取出所有信件的头部，信件id是从1开始的。
        for i in range(1, ret[0] + 1):
            # 取出信件头部。注意：top指定的行数是以信件头为基数的，也就是说当取0行，
            # 其实是返回头部信息，取1行其实是返回头部信息之外再多1行。
            mlist = self.pp.top(i, 0)
            print("line: ", len(mlist[1]))
        ret = self.pp.list()  # 列出服务器上邮件信息，这个会对每一封邮件都输出id和大小。不象stat输出的是总的统计信息

    def getemails(self):
        ret = self.pp.stat()
        for i in range(1, ret[0] + 1):
            aMail = ""
            down = self.pp.retr(
                i
            )  # 遍历所有邮件完整信息，在返回值里，是按行存储在down[1]的列表里的。down[0]是返回的状态信息
            for line in down[1]:  # 输出邮件
                aMail += line.decode("utf-8") + "\n"
            self.maillist.append(aMail)
        return self.maillist

    def quit(self):
        self.pp.quit()


if __name__ == "__main__":
    m = GetEmail()
    m.login()
    m.getemails()
    print(m.maillist[0])
