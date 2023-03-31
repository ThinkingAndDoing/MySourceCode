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
import dllapi
import ctypes


class My_Dialog(QDialog, Ui_Dialog):
	def __init__(self, parent=None):
		super(My_Dialog, self).__init__(parent)
		self.setupUi(self)
		self.setWindowTitle("开发中")
		self.setFixedSize(self.width(), self.height())
		self.pushButton.clicked.connect(self.request)
		self.pushButton_2.clicked.connect(self.release)
		self.pushButton_3.clicked.connect(self.sendkey)
		self.wrnManager = None
		
	def set_warning_manager(self, wm):
		self.wrnManager = wm
	
	def request(self):
		self.wrnManager.RequestWarning( int(self.lineEdit.text()) )
		print(self.lineEdit.text())
		print("Button 1 clicked")
		
	def release(self):
		print(self.lineEdit.text())
		print ("Button 2 clicked")
		
	def sendkey(self):
		print(self.lineEdit_2.text())
		print ("Button 3 clicked")
		
	def on_warning_changed(self, curWrnID):
		'''
		This functiion will be called in DLL
		'''
		print("on_warning_changed curWrnID is "+str(curWrnID))

	def on_telltale_changed(self, curTelltaleID):
		'''
		This functiion will be called in DLL
		'''
		print("on_telltale_changed curTelltaleID is "+str(curTelltaleID))
	
	
def register_callback_func(myDll):

	callbackWrn = ctypes.CFUNCTYPE(ctypes.c_bool, ctypes.c_int)(w.on_warning_changed)
	dllapi.gCallbackFuncList.append(callbackWrn) #There is an error if this line is missing. OSError: exception: access violation writing 0x00000000
	
	callbackTT = ctypes.CFUNCTYPE(ctypes.c_bool, ctypes.c_int)(w.on_telltale_changed)
	dllapi.gCallbackFuncList.append(callbackTT) #There is an error if this line is missing. OSError: exception: access violation writing 0x00000000
	
	myDll.dllRegisterPythonFunc(callbackWrn, callbackTT)

if __name__ == "__main__": 

	app = QApplication(sys.argv) 
	w = My_Dialog()
	w.show()
	
	wm = dllapi.get_warning_manager_dll(False)
	register_callback_func(wm)
	wm.init()
	
	w.set_warning_manager(wm)
		
	sys.exit(app.exec_())

	
	
