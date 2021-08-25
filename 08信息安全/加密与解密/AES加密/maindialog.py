#!/usr/bin/python3
# -*- coding: UTF-8 -*-

#pip install PyQt5 -> pip install PyQt5-tools
#http://code.py40.com/2540.html#title-1 QtDesigner安装
#http://code.py40.com/pyqt5/14.html PyQt5教程
#http://code.py40.com/face 使用教程

import sys
from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtCore import *
from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from ui import *
import aes
import base64
import chardet
from PyQt5.QtWidgets import QMessageBox

class My_Dialog(QDialog, Ui_Dialog):
	def __init__(self, parent=None):
		super(My_Dialog, self).__init__(parent)
		self.setupUi(self)
		self.setWindowTitle("加密与解密")
		self.setFixedSize(self.width(), self.height())
		self.setWindowFlags(Qt.WindowMinimizeButtonHint|Qt.WindowCloseButtonHint)
		self.lineEdit.setEchoMode(QtWidgets.QLineEdit.Password)
		self.pushButton.clicked.connect(self.encript)
		self.pushButton_2.clicked.connect(self.decript)
		
	def decript(self):
		print("解密")
		try:
			aesCrypt = aes.AEScrypt(self.get_password())
			e = self.get_content()
			d = aesCrypt.decrypt(e)
			ed = self.decrypt_by_base64(d)
			self.textEdit.setText(ed)
		except Exception as e:
			QMessageBox.warning(self,"消息框标题","解密失败！",QMessageBox.Ok)

	def encript(self):
		print("加密")
		try:
			aesCrypt = aes.AEScrypt(self.get_password())
			d = self.get_content()
			de = self.encrypt_by_base64(d)
			e = aesCrypt.encrypt(de)
			self.textEdit.setText(e)
		except Exception as e:
			QMessageBox.warning(self,"消息框标题","加密失败！",QMessageBox.Ok)

	def get_password(self):
		return self.lineEdit.text()
	
	def get_content(self):
		return self.textEdit.toPlainText()
		
	def decrypt_by_base64(self, str):
		data = base64.b64decode(str.encode('ascii'))
		return data.decode('utf8')

	def encrypt_by_base64(self, str):
		return base64.b64encode(str.encode('utf8')).decode('ascii')
	
if __name__ == "__main__":  
	app = QApplication(sys.argv) 
	w = My_Dialog()
	w.show()
	sys.exit(app.exec_())

