'''
1.����Դ���� Python 3.x
'''
# -*- coding: UTF-8 -*-
import xlrd
from xlutils.copy import copy

rb = xlrd.open_workbook('D:\\test.xls')
wb = copy(rb)
ws = wb.get_sheet(0)
ws.write(0,0,'changed!')
wb.save('D:\\test.xls')



'''
2.���֪ʶ��
'''












'''
3.��չ
'''

