#!/usr/bin/python3
# -*- coding: UTF-8 -*-
import sys

from PyQt5.QtGui import QFont
from PyQt5.QtCore import Qt
from PyQt5.QtWidgets import (QWidget, QLCDNumber, QSlider, QVBoxLayout, QApplication, QLabel)

class Example(QWidget):

	def __init__(self):
		super().__init__()

		self.my_UI()


	def my_UI(self):
	
		ft = QFont()
		ft.setPointSize(20)

		notice=QLabel(self)
		notice.setText('还有10分钟关机，请提前做好准备！')
		notice.move(30,50)
		notice.setFont(ft)
		
		self.setGeometry(400, 300, 500, 150)
		self.setWindowFlags(Qt.WindowStaysOnTopHint)
		self.setWindowTitle('关机提示')
		self.show()


if __name__ == '__main__':

	app = QApplication(sys.argv)
	ex = Example()
	sys.exit(app.exec_())

	
	