#!/usr/bin/python3
# -*- coding: UTF-8 -*-

#pip install PyQt5 -> pip install PyQt5-tools
#http://code.py40.com/2540.html#title-1 QtDesigner安装
#http://code.py40.com/pyqt5/14.html PyQt5教程
#http://code.py40.com/face 使用教程

import git
import os
import sys
from PyQt5.QtWidgets import QApplication, QMainWindow
from PyQt5.uic import loadUi

global repo

_srcpath = r'D:\\03SourceCode\\'
#init repository
repo = git.Repo(_srcpath)

def gitDifftool():
    commit1 = repo.git.rev_parse("HEAD")
    commit2 = repo.git.rev_parse("HEAD~1")
    repo.git.difftool("-y", "-d",commit1, commit2)

def getCurrentStatus():
    gitstatus = repo.git.status()
    curstatus = ""
    if gitstatus.find("Untracked files:")!=-1 or gitstatus.find("Changes to be committed:")!=-1 or gitstatus.find("Changes not staged for commit:")!=-1:
        curstatus = "当前有未Commit的更改！"
    elif gitstatus.find("Your branch is ahead of")!=-1:
        curstatus = "当前有未上传的Commit！"
    else:
        curstatus = "当前仓库干净！"
    return curstatus

def viewLocal():
    os.system("start " + _srcpath)

def viewCurStatus():
    print(repo.git.status())
    
def viewWorkTree():
    curdir = os.getcwd()
    os.chdir(_srcpath)
    os.system("gitk")
    os.chdir(curdir)

def startSyncToOrigin():
    #git reset --hard HEAD & git clean -fd
    if repo.git.cherry("-v")!="":
        repo.git.reset("--hard", "HEAD~1")
    else:
        repo.git.reset("--hard", "HEAD")
    repo.git.clean("-fd")
    repo.git.pull()

def startCommit():
    #add new files
    repo.git.add(".")
    #git commit
    if repo.is_dirty():
        if repo.git.cherry("-v")=="":
            repo.git.commit("-m", "no comments")
            
    
    #compare new commit with HEAD
    if repo.git.cherry("-v")!="":
        repo.git.commit("--amend")
        gitDifftool(repo)
        
    
def startPush():
    repo.git.push()

#def testbutton():
#    print("Button clicked")

class MainWindow(QMainWindow):
    def __init__(self, parent=None):
        super(MainWindow, self).__init__(parent)
        loadUi('untitled.ui', self)
        #self.pushButton.clicked.connect(testbutton)
        self.pushButton_2.clicked.connect(viewLocal)
        self.pushButton_4.clicked.connect(viewCurStatus)
        self.pushButton_6.clicked.connect(viewWorkTree)
        self.pushButton_5.clicked.connect(startSyncToOrigin)
        self.pushButton_3.clicked.connect(startCommit)
        self.pushButton.clicked.connect(startPush)

if __name__=="__main__":
        
    app = QApplication(sys.argv)
    w = MainWindow()
    w.show()
    sys.exit(app.exec())
