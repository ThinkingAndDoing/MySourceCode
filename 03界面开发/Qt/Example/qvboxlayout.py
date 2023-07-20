#!/usr/bin/python3
# -*- coding: UTF-8 -*-
import sys
from PyQt5.QtCore import Qt
from PyQt5.QtWidgets import QWidget, QLCDNumber, QSlider, QVBoxLayout, QApplication


class Example(QWidget):
    def __init__(self):
        super().__init__()

        self.my_UI()

    def my_UI(self):
        lcd = QLCDNumber(self)  # LCDNumber 显示类
        sld = QSlider(Qt.Horizontal, self)  # QSlider 显示类

        vbox = QVBoxLayout()
        vbox.addWidget(lcd)
        vbox.addWidget(sld)

        self.setLayout(vbox)
        sld.valueChanged.connect(
            lcd.display
        )  # 将滑块条的valueChanged信号和lcd数字显示的display槽连接在一起

        self.setGeometry(300, 300, 300, 250)
        self.setWindowTitle("信号 & 槽")
        self.show()


if __name__ == "__main__":
    app = QApplication(sys.argv)
    ex = Example()
    sys.exit(app.exec_())
