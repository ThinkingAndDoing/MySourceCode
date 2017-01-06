'''
1.例子源代码 Python 3.x
'''
# -*- coding: UTF-8 -*-
import threading
from time import ctime,sleep


def funcOne(func):
    for i in range(20):
        print("This is %s. %s" %(func,ctime()))
        sleep(1)

def funcTwo(func):
    for i in range(4):
        print ("This is %s. %s" %(func,ctime()))
        sleep(5)

threads = []
t1 = threading.Thread(target=funcOne,args=('funcOne',))
threads.append(t1)
t2 = threading.Thread(target=funcTwo,args=('funcTwo thread 2',))
threads.append(t2)
t3 = threading.Thread(target=funcTwo,args=('funcTwo thread 3',))
threads.append(t3)

if __name__ == '__main__':
    for t in threads:
        t.setDaemon(True)
        t.start()
    t.join()  #等待其他线程结束
    print("all threads over %s" %ctime())



'''
2.相关知识点
'''












'''
3.扩展
'''

