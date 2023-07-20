#!/usr/bin/python3
# -*- coding: UTF-8 -*-
# Pool类的构造函数中指定了进程池的大小为4，然后通过调用map方法来启动进程池中的进程。
# map方法会将worker函数和range(10)序列中的每个元素一一对应，然后将它们作为参数传递给进程池中的进程。
# 最后，调用close方法关闭进程池，并调用join方法等待所有进程结束。

import os
import time
import multiprocessing


def worker(num):
    for i in range(200000):
        pass
    print("%s get %s at %s" % (os.getpid(), num, time.strftime("%Y-%m-%d %H:%M:%S")))


if __name__ == "__main__":
    # 创建进程池
    pool = multiprocessing.Pool(4)
    # 启动进程池中的进程
    pool.map(worker, range(10))
    # 关闭进程池
    pool.close()
    # 等待进程池中的进程结束
    pool.join()
