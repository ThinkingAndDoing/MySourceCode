#!/usr/bin/python3
# -*- coding: UTF-8 -*-


FileName = "urllist.txt"


def generateList():
    f = open(FileName, "w", encoding="utf-8")
    f.write("http://nj.58.com/zufang/" + "\n")
    for i in range(2, 1000):
        f.write("http://nj.58.com/zufang/pn" + str(i) + "/" + "\n")
    f.close()


def generateList2():
    f = open(FileName, "w", encoding="utf-8")
    f.write("http://zu.nanjing.fang.com/house-a0268/" + "\n")
    for i in range(2, 1000):
        f.write("http://zu.nanjing.fang.com/house-a0268/i3" + str(i) + "/" + "\n")
    f.close()


def generateList3():
    f = open(FileName, "w", encoding="utf-8")
    f.write("http://nj.ganji.com/fang1/jiangning/" + "\n")
    for i in range(2, 1000):
        f.write("http://nj.ganji.com/fang1/jiangning/o" + str(i) + "/" + "\n")
    f.close()


if __name__ == "__main__":
    generateList3()
