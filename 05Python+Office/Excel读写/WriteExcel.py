'''
1.例子源代码 Python 3.x
'''
# -*- coding: UTF-8 -*-
import xlwt

#创建workbook和sheet对象
workbook = xlwt.Workbook() #注意Workbook的开头W要大写
sheet1 = workbook.add_sheet('sheet1',cell_overwrite_ok=True)
sheet2 = workbook.add_sheet('sheet2',cell_overwrite_ok=True)
#向sheet页中写入数据
sheet1.write(0,0,'this should overwrite1')
sheet1.write(0,1,'aaaaaaaaaaaa')
sheet2.write(0,0,'this should overwrite2')
sheet2.write(1,2,'bbbbbbbbbbbbb')
#保存该excel文件,有同名文件时直接覆盖
workbook.save('C:\\Users\\uidp8103\\Desktop\\TextCompare\\python\\testing\\test2.xls')
print('创建excel文件完成！')




'''
2.相关知识点
'''












'''
3.扩展
'''
