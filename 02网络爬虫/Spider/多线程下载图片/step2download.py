"""
1.Sample Python 3.x
"""
# -*- coding: UTF-8 -*-
import listofphotos
import os
from time import ctime
import threading
import logging

logging.basicConfig(
    level=logging.DEBUG,
    format="%(asctime)s %(filename)s[line:%(lineno)d] %(levelname)s %(message)s",
    datefmt="%a, %d %b %Y %H:%M:%S",
    filename="test.log",
    filemode="w",
)


def downloadList(list):
    try:
        gp = listofphotos.ListOfPhotos()
        for i in list:
            if i == "":
                continue
            logging.debug("break 1")
            args = i.split("--")
            imgurls = []
            templist = args[1].split("http:")
            for j in templist:
                if j != "":
                    imgurls.append("http:" + j)
            if args[0] == "" or os.path.exists(args[0].strip()):
                print("The folder is aready created ! Skip.")
                continue
            logging.debug("break 2")
            if imgurls != []:
                logging.debug("break 3")
                gp.setUrlListAndPath(imgurls, args[0])
                gp.startDownload()
    except Exception as e:
        print(Exception, "in downloadList:", e)


f = open("out.txt", "r", encoding="utf-8")
data = f.read()
inputList = data.split("\n")

threadsNum = 1
subLen = int(len(inputList) / threadsNum)
threads = []
for i in range(0, threadsNum):
    if i != threadsNum - 1:
        t = threading.Thread(
            target=downloadList, args=(inputList[i * subLen : i * subLen + subLen],)
        )
    else:
        t = threading.Thread(
            target=downloadList, args=(inputList[i * subLen : len(inputList)],)
        )
    threads.append(t)

if __name__ == "__main__":
    for t in threads:
        t.setDaemon(True)
        t.start()
    t.join()  # wait all threads.
    print("all over %s" % ctime())


"""
2.Reference
"""


"""
3.Extension

"""
