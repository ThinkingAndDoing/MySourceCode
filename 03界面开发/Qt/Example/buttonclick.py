#!/usr/bin/python3
# -*- coding: UTF-8 -*-
import sys
from PyQt5.QtWidgets import QMainWindow, QPushButton, QApplication


class Example(QMainWindow):
    def __init__(self):
        super().__init__()

        self.my_UI()

    def my_UI(self):
        btn1 = QPushButton("按钮1", self)
        btn1.move(30, 50)

        btn2 = QPushButton("按钮2", self)
        btn2.move(150, 50)

        btn1.clicked.connect(self.buttonClicked)  # 两个按钮都连接到了同一个槽中
        btn2.clicked.connect(self.buttonClicked)

        self.statusBar()

        self.setGeometry(300, 300, 290, 150)
        self.setWindowTitle("事件发送者")
        self.show()

    def buttonClicked(self):  # 在buttonClikced()方法中，我们调用sender()方法来判断哪一个按钮是我们按下的
        sender = self.sender()
        self.statusBar().showMessage(sender.text() + " 是发送者")


if __name__ == "__main__":
    app = QApplication(sys.argv)
    ex = Example()
    sys.exit(app.exec_())
