'''
1.例子源代码 Python 3.x
'''
# -*- coding: UTF-8 -*-
import logging


def setDebugLevel(debuglevel):
    logging.basicConfig(level=debuglevel,format='%(message)s',filename='test.log',filemode='w')
    logging.critical('-------------------------------')
    logging.debug('debug message')
    logging.info('info message')
    logging.warning('warning message')
    logging.error('error message')
    logging.critical('critical message')

if __name__ == "__main__":
	setDebugLevel(logging.WARNING) #显示大于或等于logging.WARNING级别的消息

	console = logging.StreamHandler()
	console.setLevel(logging.INFO) #在console显示大于logging.INFO级别的消息
	formatter = logging.Formatter('%(name)-12s: %(levelname)-8s %(message)s')
	console.setFormatter(formatter)
	logging.getLogger('').addHandler(console)

	logging.debug('This is debug message')
	logging.info('This is info message')
	logging.warning('This is warning message')

'''
2.相关知识点

logging.basicConfig(level=logging.DEBUG,format='%(asctime)s %(filename)s[line:%(lineno)d] %(levelname)s %(message)s',datefmt='%a, %d %b %Y %H:%M:%S',filename='test.log',filemode='w')
logging.basicConfig函数各参数:
filename: 指定日志文件名
filemode: 和file函数意义相同，指定日志文件的打开模式，'w'或'a'
format: 指定输出的格式和内容，format可以输出很多有用信息，如上例所示:
 %(levelno)s: 打印日志级别的数值
 %(levelname)s: 打印日志级别名称
 %(pathname)s: 打印当前执行程序的路径，其实就是sys.argv[0]
 %(filename)s: 打印当前执行程序名
 %(funcName)s: 打印日志的当前函数
 %(lineno)d: 打印日志的当前行号
 %(asctime)s: 打印日志的时间
 %(thread)d: 打印线程ID
 %(threadName)s: 打印线程名称
 %(process)d: 打印进程ID
 %(message)s: 打印日志信息
datefmt: 指定时间格式，同time.strftime()
level: 设置日志级别，默认为logging.WARNING
stream: 指定将日志的输出流，可以指定输出到sys.stderr,sys.stdout或者文件，默认输出到sys.stderr，当stream和filename同时指定时，stream被忽略

#################################################################################################
#定义一个StreamHandler，将INFO级别或更高的日志信息打印到标准错误，并将其添加到当前的日志处理对象#
console = logging.StreamHandler()
console.setLevel(logging.INFO)
formatter = logging.Formatter('%(name)-12s: %(levelname)-8s %(message)s')
console.setFormatter(formatter)
logging.getLogger('').addHandler(console)
#################################################################################################

logging.debug('This is debug message')
logging.info('This is info message')
logging.warning('This is warning message')
'''












'''
3.扩展
'''

