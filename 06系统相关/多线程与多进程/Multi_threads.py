"""
1.例子源代码 Python 3.x
"""
# -*- coding: UTF-8 -*-
# python多线程比单线程效率低的原因及其解决办法
# 尽管Python也支持多线程，但这些线程受GIL约束，所以每次或许只能有一条线程向前推进，而无法实现多头并进。
# 并且由于GIL锁存在，python里一个进程永远只能同时执行一个线程(拿到 GIL的线程才能执行 )，这就是为什么在多核 CPU上，python的多线程效率并不高
# 每个进程有各自独立的 GIL，互不干扰，这样就可以真正意义上的并行执行。
# 在python中，多进程的执行效率优于多线程 (仅仅针对多核 CPU而言 )。所以在多核CPU下，想做并行提升效率，比较通用的方法是使用多进程，能够有效提高执行效率。

import threading
from time import ctime, sleep


def funcOne(func):
    for i in range(20):
        print("This is %s. %s" % (func, ctime()))
        sleep(1)


def funcTwo(func):
    for i in range(4):
        print("This is %s. %s" % (func, ctime()))
        sleep(5)


threads = []
t1 = threading.Thread(target=funcOne, args=("funcOne",))
threads.append(t1)
t2 = threading.Thread(target=funcTwo, args=("funcTwo thread 2",))
threads.append(t2)
t3 = threading.Thread(target=funcTwo, args=("funcTwo thread 3",))
threads.append(t3)

if __name__ == "__main__":
    for t in threads:
        t.setDaemon(True)
        t.start()
    t.join()  # 等待其他线程结束
    print("all threads over %s" % ctime())


"""
2.相关知识点
"""


"""
3.扩展
"""
