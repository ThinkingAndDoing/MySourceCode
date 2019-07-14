#!/usr/bin/python3
# -*- coding: UTF-8 -*-
import git
import os

'''
配置代码对比工具
[diff]
    tool = bc3
[difftool "bc3"]
    path = D:\\01MyProgram\\Beyond Compare 4\\BCompare.exe
'''
'''
配置编辑工具
git config --global core.editor "D:/01MyProgram/Notepad++/notepad++.exe"
git config --global -l
'''

_srcpath = r'D:\\03SourceCode\\'

def gitCommit(repo):
    if repo.is_dirty():
        if repo.git.cherry("-v")!="":
            repo.git.commit("--amend")
        else:
            repo.git.commit("-m", "no comments")
 
def gitDifftool(repo):
    commit1 = repo.git.rev_parse("HEAD")
    commit2 = repo.git.rev_parse("HEAD~1")
    repo.git.difftool("-y", "-d",commit1, commit2)

def getCurrentStatus(repo):
    gitstatus = repo.git.status()
    curstatus = ""
    if gitstatus.find("Untracked files:")!=-1 or gitstatus.find("Changes to be committed:")!=-1:
        curstatus = "当前有未Commit的更改！"
    elif gitstatus.find("Your branch is ahead of")!=-1:
        curstatus = "当前有未上传的Commit！"
    else:
        curstatus = "当前仓库干净！"
    return curstatus

def viewLocal():
    os.system("start " + _srcpath)

def viewCurStatus(repo):
    print(repo.git.status())
    
def viewWorkTree():
    curdir = os.getcwd()
    os.chdir(_srcpath)
    os.system("gitk")
    os.chdir(curdir)

def startSyncToOrigin(repo):
    #git reset --hard HEAD & git clean -fd
    if repo.git.cherry("-v")!="":
        repo.git.reset("--hard", "HEAD~1")
    else:
        repo.git.reset("--hard", "HEAD")
    repo.git.clean("-fd")
    repo.git.pull()

def startCommit(repo):
    #add new files
    repo.git.add(".")
    gitCommit(repo)
    #compare new commit with HEAD
    if repo.git.cherry("-v")!="":
        gitDifftool(repo)
    else:
        print(repo.git.status())

def startPush(repo):
    if repo.git.cherry("-v")!="":
        repo.git.commit("--amend")
        repo.git.push()
        print(repo.git.status())
    else:
        print(repo.git.status())

def run(repo):
    
    while(True):
        print("*"*40)
        print("当前状态："+getCurrentStatus(repo))
        print("输入选项：")
        print("1:查看本地仓库代码；\n2:查看本地仓库当前状态；\n3:查看本地仓库版本树；\n4:执行同步到远程仓库;\n5:执行一键Commit；\n6:执行一键push；")
        print("*"*40)
        cmd = input()
        print("返回结果：")
        if cmd=="1":
            viewLocal()
        elif cmd=="2":
            viewCurStatus()
        elif cmd=="3":
            viewWorkTree()
        elif cmd=="4":
            startSyncToOrigin()
        elif cmd=="5":
            startCommit()
        elif cmd=="6":
            startPush()
        else:
            print("Exit!")
            break
        #
        print("\nPress any other key to exit!\n\n")
    

if __name__=="__main__":

    #init repository
    gitRepo = git.Repo(_srcpath)
    
    run(gitRepo)

    
