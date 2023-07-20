#!/usr/bin/python3
# -*- coding: UTF-8 -*-

# pip install PyQt5 -> pip install PyQt5-tools
# http://code.py40.com/2540.html#title-1 QtDesigner安装
# http://code.py40.com/pyqt5/14.html PyQt5教程
# http://code.py40.com/face 使用教程

import sys
from PyQt5.QtWidgets import QApplication, QMainWindow
from ui import *

# ctrl + R  Preview


class MyWindow(QMainWindow, Ui_MainWindow):
    def __init__(self, parent=None):
        super(MyWindow, self).__init__(parent)
        self.setupUi(self)
        self.setWindowTitle("开发中")
        self.setFixedSize(self.width(), self.height())
        # self.showFullScreen()


if __name__ == "__main__":
    app = QApplication(sys.argv)
    myWin = MyWindow()
    myWin.show()
    sys.exit(app.exec_())
