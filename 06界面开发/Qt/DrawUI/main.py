#!/usr/bin/python3
# -*- coding: UTF-8 -*-

#pip install PyQt5 -> pip install PyQt5-tools
#http://code.py40.com/2540.html#title-1 QtDesigner安装
#http://code.py40.com/pyqt5/14.html PyQt5教程
#http://code.py40.com/face 使用教程

import sys
from PyQt5.QtWidgets import QApplication, QMainWindow
from PyQt5.uic import loadUi


def testbutton():
    print("Button clicked")

class MainWindow(QMainWindow):
    def __init__(self, parent=None):
        super(MainWindow, self).__init__(parent)
        loadUi('untitled.ui', self)
        #self.pushButton.clicked.connect(testbutton)

if __name__=="__main__":

    app = QApplication(sys.argv)
    w = MainWindow()
    w.show()
    sys.exit(app.exec())
