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


class My_Dialog(QDialog, Ui_Dialog):
    def __init__(self, parent=None):
        super(My_Dialog, self).__init__(parent)
        self.setupUi(self)


if __name__ == "__main__":  
	app = QApplication(sys.argv) 
	w = My_Dialog()
	w.show()
	sys.exit(app.exec_())

