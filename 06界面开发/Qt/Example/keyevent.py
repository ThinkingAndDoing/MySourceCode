#!/usr/bin/python3
# -*- coding: UTF-8 -*-
import sys
from PyQt5.QtCore import Qt
from PyQt5.QtWidgets import QWidget, QApplication


class Example(QWidget):

	def __init__(self):
		super().__init__()

		self.my_UI()


	def my_UI(self):     

		self.setGeometry(300, 300, 300, 250)
		self.setWindowTitle('事件处理')
		self.show()


	def keyPressEvent(self, e):         #重写keyPressEvent()事件处理函数
                                        #如果我们点击了Esc按钮，应用将会被终止。         
		if e.key() == Qt.Key_Escape:
			self.close()


if __name__ == '__main__':

	app = QApplication(sys.argv)
	ex = Example()
	sys.exit(app.exec_())


	