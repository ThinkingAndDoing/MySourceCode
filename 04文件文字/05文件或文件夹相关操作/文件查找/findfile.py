#!/usr/bin/python3
# -*- coding: UTF-8 -*-

import sys
import shutil
import os

# _Filename = sys.argv[1]


def findStrInFiles(fileToBeSearch, distpath):
    print("查询结果如下：")
    for root, dirs, files in os.walk(distpath, topdown=False):
        if root.find(os.getcwd() + "\\" + ".git") != -1:
            continue

        for name in files:
            try:
                filename = os.path.join(root, name)
                if filename.find(fileToBeSearch) != -1:
                    print(os.path.join(root, name))
            except Exception as e:
                continue


if __name__ == "__main__":
    print("请输入要查找的文件名！")
    inputStr = input()
    findStrInFiles(inputStr, ".")
