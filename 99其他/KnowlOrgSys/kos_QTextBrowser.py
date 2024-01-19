# -*- coding: UTF-8 -*-
from PyQt5.QtWidgets import QTextBrowser
from PyQt5.QtCore import Qt, QUrl
import shutil
import os

class KosTextBrowser(QTextBrowser):
    def __init__(self):
        super().__init__()
        self.setContextMenuPolicy(Qt.CustomContextMenu)
        self.customContextMenuRequested.connect(self.showContextMenu)
        self.file_to_be_copied = ""


    def getLinkClicked(self, pos):
        # save the link clicked
        self.file_to_be_copied = ""
        link = self.anchorAt(pos)
        if link:  
            url = QUrl(link)  
            if url.scheme() == "file":  
                self.file_to_be_copied = url.toLocalFile()


    def showContextMenu(self, pos):

        self.getLinkClicked(pos)

        # get the origin context menu
        default_menu = self.createStandardContextMenu()

        # remove unused actions
        for action in default_menu.actions():
            if action.text()=="Copy &Link Location" or action.text().strip()=="":
                default_menu.removeAction(action)

        # add split line
        default_menu.addSeparator()
        # add menu action
        custom_action = default_menu.addAction("Copy file to desktop")
        custom_action.triggered.connect(self.copy_file)
        if self.file_to_be_copied=="":
            custom_action.setDisabled(True)
        else:
            custom_action.setDisabled(False)

        default_menu.addAction(custom_action)
        default_menu.exec_(self.mapToGlobal(pos))
        

    def copy_file(self):
        desktop_path = os.path.join(os.path.expanduser("~"), "Desktop")

        shutil.copy(self.file_to_be_copied, desktop_path)

        
