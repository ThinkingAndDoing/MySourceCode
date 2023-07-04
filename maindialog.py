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


INVALID_ID = 0xFFFF

class My_Dialog(QDialog, Ui_Dialog):

	def __init__(self, parent=None):
		super(My_Dialog, self).__init__(parent)
		self.setupUi(self)
		self.setWindowTitle("开发中")
		self.setFixedSize(self.width(), self.height())
		self.lineEdit.setFocus()
		self.lineEdit_2.setText("4")
		
		self.qbusagemode = QButtonGroup(self)
		self.qbusagemode.addButton(self.radioAbandoned, 11)
		self.qbusagemode.addButton(self.radioInactive, 12)
		self.qbusagemode.addButton(self.radioConvenience, 13)
		self.qbusagemode.addButton(self.radioActive, 14)
		self.qbusagemode.addButton(self.radioDriving, 15)
		self.qbusagemode.buttonClicked.connect(self.usagemode_changed)
		self.radioAbandoned.setChecked(True)
		
		self.qbavailiable = QButtonGroup(self)
		self.qbavailiable.addButton(self.radioOFF, 21)
		self.qbavailiable.addButton(self.radioMode1, 22)
		self.qbavailiable.addButton(self.radioMode2, 23)
		self.qbavailiable.addButton(self.radioMode3, 24)
		self.qbavailiable.addButton(self.radioStale, 25)
		self.qbavailiable.buttonClicked.connect(self.availiable_changed)
		self.radioOFF.setChecked(True)
		
		self.label_3.setText("")
		self.label_4.setText("")
		self.label_5.setText("")
		self.label_6.setText("")
		self.label_7.setText("")
				
		self.pushButton.clicked.connect(self.request)
		self.pushButton_2.clicked.connect(self.release)
		self.pushButton_3.clicked.connect(self.sendkey)
		self.Suspension.clicked.connect(self.suspension)
		self.Resume.clicked.connect(self.resume)
		self.wrnManager = None
		
	def usagemode_changed(self):
	
		sender = self.sender()
		if sender == self.qbusagemode:
			if self.qbusagemode.checkedId() == 11:
				self.wrnManager.SetWarningMode(5)
			elif self.qbusagemode.checkedId() == 12:
				self.wrnManager.SetWarningMode(4)
			elif self.qbusagemode.checkedId() == 13:
				self.wrnManager.SetWarningMode(3)
			elif self.qbusagemode.checkedId() == 14:
				self.wrnManager.SetWarningMode(2)
			elif self.qbusagemode.checkedId() == 15:
				self.wrnManager.SetWarningMode(1)
			else:
				self.wrnManager.SetWarningMode(5)
		
	def availiable_changed(self):
	
		sender = self.sender()
		if sender == self.qbavailiable:
			if self.qbavailiable.checkedId() == 21:
				self.wrnManager.SetAvailiable(0)
			elif self.qbavailiable.checkedId() == 22:
				self.wrnManager.SetAvailiable(1)
			elif self.qbavailiable.checkedId() == 23:
				self.wrnManager.SetAvailiable(2)
			elif self.qbavailiable.checkedId() == 24:
				self.wrnManager.SetAvailiable(3)
			elif self.qbavailiable.checkedId() == 25:
				self.wrnManager.SetAvailiable(4)
			else:
				self.wrnManager.SetAvailiable(0)
		
	def set_warning_manager(self, wm):
		self.wrnManager = wm
	
	def request(self):
		self.wrnManager.RequestWarning( int(self.lineEdit.text()) )
		
	def release(self):
		self.wrnManager.ReleaseWarning( int(self.lineEdit.text()) )
		
	def sendkey(self):
		self.wrnManager.ProcessVirtualKey(int(self.lineEdit_2.text()))

	def suspension(self):
		self.wrnManager.Suspension()
		
	def resume(self):
		self.wrnManager.Resume()
	
	def set_warninglist_item(self, itemLabel, itemValue):
	
		if itemValue != INVALID_ID:
			itemLabel.setText("WarningItem = " + str(itemValue))
		else:
			itemLabel.setText("")

	def on_warningstack_changed(self, stackSize):
		'''
		This functiion will be called in DLL
		'''
		print(" stackSize = "+ str(stackSize))
		self.set_warninglist_item(self.label_3, wm.GetWarningIDFromStack(0))
		self.set_warninglist_item(self.label_4, wm.GetWarningIDFromStack(1))
		self.set_warninglist_item(self.label_5, wm.GetWarningIDFromStack(2))
		self.set_warninglist_item(self.label_6, wm.GetWarningIDFromStack(3))
		self.set_warninglist_item(self.label_7, wm.GetWarningIDFromStack(4))
		
	def on_warning_changed(self, curWrnID):
		'''
		This functiion will be called in DLL
		'''
		if INVALID_ID!=curWrnID:
			self.label_2.setText("Current warning ID is\n\n" + str(curWrnID))
		else:
			self.label_2.setText("No warning display!")

	def on_telltale_changed(self, curTelltaleID):
		'''
		This functiion will be called in DLL
		'''
		print("on_telltale_changed curTelltaleID is "+str(curTelltaleID))
	
	
def register_callback_func(myDll):

	callbackWrnStack = ctypes.CFUNCTYPE(ctypes.c_bool, ctypes.c_int)(w.on_warningstack_changed)
	dllapi.gCallbackFuncList.append(callbackWrnStack) #There is an error if this line is missing. OSError: exception: access violation writing 0x00000000
	
	callbackWrn = ctypes.CFUNCTYPE(ctypes.c_bool, ctypes.c_int)(w.on_warning_changed)
	dllapi.gCallbackFuncList.append(callbackWrn) #There is an error if this line is missing. OSError: exception: access violation writing 0x00000000
	
	callbackTT = ctypes.CFUNCTYPE(ctypes.c_bool, ctypes.c_int)(w.on_telltale_changed)
	dllapi.gCallbackFuncList.append(callbackTT) #There is an error if this line is missing. OSError: exception: access violation writing 0x00000000
	
	myDll.dllRegisterPythonFunc(callbackWrnStack, callbackWrn, callbackTT)

if __name__ == "__main__": 

	app = QApplication(sys.argv) 
	w = My_Dialog()
	w.show()
	
	wm = dllapi.get_warning_manager_dll(False)
	register_callback_func(wm)
	wm.init()
	
	w.set_warning_manager(wm)
		
	sys.exit(app.exec_())

	
	
