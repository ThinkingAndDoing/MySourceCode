'''
1.例子源代码 Python 3.x
'''
# -*- coding: UTF-8 -*-

import ctypes
import time
import os

#返回当前时间 时：分
def GetNowTime():
    return time.strftime("%H:%M",time.localtime(time.time()))

#调用WindowAPI锁定计算机
def LockWindows():
    dll = ctypes.WinDLL('user32.dll');
    dll.LockWorkStation();

#开始工作
'''
D:\\Schedule.txt
19:40
20:50
14:30
'''
def StartWork():
    while(True):
        print("i am sleeping")
        time.sleep(60) #one time in a minute
        try:
            f = open("D:\\Schedule.txt","r")
        except:
            print("D:\\Schedule.txt is not exist!")
        else:
            list=f.read().split("\n")
            print(list)
            for i in list:
                if i == GetNowTime():
                    LockWindows()
            f.close()

#设置工作环境
def SetEnv():
    SystemRoot=os.environ.get("SystemRoot")
    f = open(SystemRoot+"\\System32\\drivers\\etc\\hosts","w")
    etcstr = "\
    # Copyright (c) 1993-2009 Microsoft Corp.\n\
    #\n\
    # This is a sample HOSTS file used by Microsoft TCP/IP for Windows.\n\
    #\n\
    # This file contains the mappings of IP addresses to host names. Each\n\
    # entry should be kept on an individual line. The IP address should\n\
    # be placed in the first column followed by the corresponding host name.\n\
    # The IP address and the host name should be separated by at least one\n\
    # space.\n\
    #\n\
    # Additionally, comments (such as these) may be inserted on individual\n\
    # lines or following the machine name denoted by a '#' symbol.\n\
    #\n\
    # For example:\n\
    #\n\
    #      102.54.94.97     rhino.acme.com          # source server\n\
    #       38.25.63.10     x.acme.com              # x client host\n\
    \n\
    # localhost name resolution is handled within DNS itself.\n\
    #	127.0.0.1       localhost\n\
    #	::1             localhost\n\
    \n\
    # disable all video site\n\
    0.0.0.0       v.qq.com\n\
    0.0.0.0       www.mgtv.com\n\
    0.0.0.0       www.youku.com\n\
    0.0.0.0       v.youku.com\n\
    0.0.0.0       www.tudou.com\n\
    0.0.0.0       www.iqiyi.com\n\
    0.0.0.0       tv.sohu.com\n\
    0.0.0.0       vod.kankan.com\n\
    0.0.0.0       www.wasu.cn\n\
    0.0.0.0       e.hd.baofeng.com\n\
    0.0.0.0       www.baofeng.com\n\
    0.0.0.0       v.pptv.com\n\
    0.0.0.0       www.pptv.com\n\
    0.0.0.0       www.le.com\n\
    0.0.0.0       v.pps.tv\n\
    0.0.0.0       www.pps.tv\n\
    0.0.0.0       v.ku6.com\n\
    0.0.0.0       www.56.com\n\
    0.0.0.0       movie.kankan.com\n\
    0.0.0.0       tv.kankan.com\n\
    0.0.0.0       www.kankan.com\n\
    0.0.0.0       wdy.kankan.com\n\
    0.0.0.0       video.sina.com.cn\n\
    0.0.0.0       www.fun.tv\n\
    0.0.0.0       www.1905.com\n\
    0.0.0.0       tv.cntv.cn\n\
    \n\
    # disable all novels site\n\
    0.0.0.0       www.23wx.com\n\
    0.0.0.0       www.bxwx8.org\n\
    0.0.0.0       www.zhuzhudao.com\n\
    0.0.0.0       www.dpcq1.com\n\
    0.0.0.0       www.00ksw.com\n\
    0.0.0.0       www.xxbiquge.com\n\
    0.0.0.0       www.liewen.cc\n\
    0.0.0.0       www.biquge5.com\n\
    0.0.0.0       www.ty2016.net\n\
    0.0.0.0       www.siluke.tw\n\
    0.0.0.0       www.ybdu.com\n\
    0.0.0.0       www.qidian.com\n\
    0.0.0.0       book.2345.com\n\
    0.0.0.0       www.23wx.com\n\
    0.0.0.0       www.23wx.com\n\
    "
    f.write(etcstr)
    f.close


#start Work
#SetEnv()
StartWork()


'''
2.相关知识点
'''






'''
3.扩展
'''
