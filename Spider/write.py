'''
1.例子源代码 Python 3.x
'''
# -*- coding: UTF-8 -*-
import xlwt
import time

def writeTable(content):
	workbook = xlwt.Workbook() #注意Workbook的开头W要大写
	sheet1 = workbook.add_sheet('sheet1',cell_overwrite_ok=True)
	row = 0
	for i in content:
		col = 0
		for j in i:
			sheet1.write(row, col, j)
			col = col + 1
		row = row + 1
	timeTag = time.strftime('(%Y%m%d)%H-%M-%S',time.localtime(time.time()))
	workbook.save(timeTag+'OutputExcel.xls')

array1 = []
array1.append(["1","2"])
array1.append(["a","b"])
writeTable(array1)

print('输出完毕！')


'''
2.相关知识点
'''












'''
3.扩展
'''