#!/usr/bin/python3
# -*- coding: UTF-8 -*-
import sys
from PyQt5.QtCore import pyqtSignal, QObject
from PyQt5.QtWidgets import QMainWindow, QApplication


class Communicate(QObject):     #信号使用了pyqtSignal()方法创建，
                                #并且成为外部类Communicate类的属性。    
	closeApp = pyqtSignal() #创建一个新的信号叫做closeApp


class Example(QMainWindow):

	def __init__(self):
		super().__init__()

		self.my_UI()


	def my_UI(self):     

		self.c = Communicate()
		self.c.closeApp.connect(self.close)  #把自定义的closeApp信号连接到QMainWindow的close()槽上。    

		self.setGeometry(300, 300, 290, 150)
		self.setWindowTitle('发出信号')
		self.show()


	def mousePressEvent(self, event):

		self.c.closeApp.emit()              #在窗口上点击一下鼠标，closeApp信号会被发射


if __name__ == '__main__':

	app = QApplication(sys.argv)
	ex = Example()
	sys.exit(app.exec_())


	
	

	
	
	



	