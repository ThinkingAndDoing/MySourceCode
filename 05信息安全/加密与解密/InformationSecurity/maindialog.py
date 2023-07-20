#!/usr/bin/python3
# -*- coding: UTF-8 -*-

# pip install PyQt5 -> pip install PyQt5-tools
# http://code.py40.com/2540.html#title-1 QtDesigner安装
# http://code.py40.com/pyqt5/14.html PyQt5教程
# http://code.py40.com/face 使用教程

import sys
from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtCore import *
from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from ui import *
import aesinstance
import rsainstance
import base64
import chardet
from PyQt5.QtWidgets import QMessageBox


# 双重加密，加密时将明文用AES加密，然后再用RSA加密；解密时，先用RSA解密，然后再用AES加密。
class My_Dialog(QDialog, Ui_Dialog):
    def __init__(self, parent=None):
        super(My_Dialog, self).__init__(parent)
        self.setupUi(self)
        self.setWindowTitle("加密与解密")
        self.setFixedSize(self.width(), self.height())
        self.setWindowFlags(Qt.WindowMinimizeButtonHint | Qt.WindowCloseButtonHint)
        self.lineEdit.setEchoMode(QtWidgets.QLineEdit.Password)
        self.pushButton.clicked.connect(self.encript)
        self.pushButton_2.clicked.connect(self.decript)

    def decript(self):
        try:
            print("解密")
            explicitText = self.decrypt_by_rsa(self.get_content())
            explicitText = self.decrypt_by_aes(explicitText)
            self.textEdit.setText(explicitText)
        except Exception as e:
            QMessageBox.warning(self, "消息框标题", "解密失败！", QMessageBox.Ok)

    def encript(self):
        print("加密")
        cipherText = self.encrypt_by_aes(self.get_content())
        cipherText = self.encrypt_by_rsa(cipherText)
        self.textEdit.setText(cipherText)
        try:
            pass
        except Exception as e:
            QMessageBox.warning(self, "消息框标题", "加密失败！", QMessageBox.Ok)

    def encrypt_by_aes(self, explicitText):
        aesCrypt = aesinstance.AEScrypt(self.get_password())
        base64Text = self.encrypt_by_base64(explicitText)
        return aesCrypt.encrypt(base64Text)

    def decrypt_by_aes(self, cipherText):
        aesCrypt = aesinstance.AEScrypt(self.get_password())
        base64Text = aesCrypt.decrypt(cipherText)
        return self.decrypt_by_base64(base64Text)

    def encrypt_by_rsa(self, explicitText):
        rsaCrypt = rsainstance.RsaUtil()
        cipherText = rsaCrypt.encrypt_by_public_key(explicitText.encode("utf8"))
        return cipherText.decode("utf8")

    def decrypt_by_rsa(self, cipherText):
        rsaCrypt = rsainstance.RsaUtil()
        explicitText = rsaCrypt.decrypt_by_private_key(cipherText.encode("utf8"))
        return explicitText.decode("utf8")

    def get_password(self):
        return self.lineEdit.text()

    def get_content(self):
        return self.textEdit.toPlainText()

    def decrypt_by_base64(self, str):
        data = base64.b64decode(str.encode("ascii"))
        return data.decode("utf8")

    def encrypt_by_base64(self, str):
        return base64.b64encode(str.encode("utf8")).decode("ascii")


if __name__ == "__main__":
    app = QApplication(sys.argv)
    w = My_Dialog()
    w.show()
    sys.exit(app.exec_())
