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
    #git commit
    if repo.is_dirty():
        if repo.git.cherry("-v")!="":
            repo.git.commit("--amend")
        else:
            repo.git.commit("-m", "new")
 
def gitDifftool(repo):
    commit1 = repo.git.rev_parse("HEAD")
    commit2 = repo.git.rev_parse("HEAD~1")
    repo.git.difftool("-y", "-d",commit1, commit2)

if __name__=="__main__":

    #init repository
    repo = git.Repo(_srcpath)
    
    print("1，执行一键Commit；\n2，执行一键push;\n3，查看本地仓库；\n4，查看仓库最近三个Commit；\n")
    cmd = input()
    if cmd=="1":
        #add new files
        repo.git.add(".")
        gitCommit(repo)
        #compare new commit with HEAD
        if repo.git.cherry("-v")!="":
            gitDifftool(repo)
        else:
            print(repo.git.status())
    elif cmd=="2":
        if repo.git.cherry("-v")!="":
            repo.git.commit("--amend")
            repo.git.push()
            print(repo.git.status())
        else:
            print(repo.git.status())
    elif cmd=="3":
        doscmd = "start " + _srcpath
        os.system(doscmd)
    elif cmd=="4":
        print(repo.git.log("-3"))
    #
    print("\nPress any key to exit!")
    cmd = input()
    
    
