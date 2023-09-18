﻿# -*- coding: UTF-8 -*-

import re
import os
import shutil
import hashlib

import sys
from PyQt5.QtWidgets import QStatusBar, QFileSystemModel, QApplication, QMainWindow, QTextEdit, QAction, QFileDialog, QHBoxLayout
from PyQt5.QtWidgets import QWidget, QTextBrowser, QInputDialog, QComboBox, QScrollArea, QTreeView
from PyQt5.QtGui import QDesktopServices, QTextCursor, QFont, QTextOption
from PyQt5.QtCore import Qt
import markdown

TEXT_FONT = "新宋体"
TEXT_FONT_SIZE = 14
ACTION_FONT = "Arial"
ACTION_FONT_SIZE = 12

def get_html_text(plain_text):
    #replace \n as <br/>
    plain_text = plain_text.replace('\n', '<br/>')
    html_text = markdown.markdown(plain_text)
    #keep all space
    html_text = "<pre>" + html_text + "</pre>"
    return html_text

def get_md5(filename):
    with open(filename, 'rb') as f:
        md5 = hashlib.md5()
        while chunk := f.read(1024):
            md5.update(chunk)
    return md5.hexdigest()


class MarkdownEditor(QMainWindow):

    def __init__(self):
        super().__init__()

        self.initMarkdownEditorUI()
        self.text_content = ""
        self.show_mark_down()
        self.mdFilePath = "."

    def initMarkdownEditorUI(self):
        self.setWindowTitle('Markdown Editor')
        self.setGeometry(100, 100, 1000, 750)
        
        # 创建工具栏
        self.toolbar = self.addToolBar('工具栏')
        self.toolbar.setLayoutDirection(Qt.RightToLeft)
        # 创建下拉框
        self.comboBox = QComboBox(self)
        self.comboBox.setFont(QFont(ACTION_FONT, ACTION_FONT_SIZE))
        self.comboBox.addItem('阅读')
        self.comboBox.addItem('编辑')
        # 连接下拉框的activated信号到槽函数
        self.comboBox.activated.connect(self.on_combo_box_activated)
        self.comboBox.setDisabled(True)
        # 创建一个小部件动作并将下拉框添加到其中
        self.toolbar.addWidget(self.comboBox)
        self.action = QAction(self)
        self.action.setEnabled(True)
        self.action.setVisible(True)
        self.action.setObjectName("action")
        self.action.setText("一级缩进")
        self.action_2 = QAction(self)
        self.action_2.setObjectName("action_2")
        self.action_2.setText("二级缩进")
        self.action_3 = QAction(self)
        self.action_3.setCheckable(False)
        self.action_3.setObjectName("action_3")
        self.action_3.setText("三级缩进")
        self.toolbar.addAction(self.action_3)
        self.toolbar.addAction(self.action_2)
        self.toolbar.addAction(self.action)
        self.toolbar.actionTriggered[QAction].connect(self.on_toolbtn_pressed)

        self.status_bar = QStatusBar()
        self.setStatusBar(self.status_bar)

        self.menu = self.menuBar()
        self.menu.setFont(QFont(ACTION_FONT, ACTION_FONT_SIZE))

        self.file_menu = self.menu.addMenu('文件')
        self.file_menu.setFont(QFont(ACTION_FONT, ACTION_FONT_SIZE))
        self.open_file_action = QAction('加载', self)
        self.file_menu.addAction(self.open_file_action)
        self.save_file_action = QAction('保存', self)
        self.file_menu.addAction(self.save_file_action)

        self.insert_menu = self.menu.addMenu('插入')
        self.insert_menu.setFont(QFont(ACTION_FONT, ACTION_FONT_SIZE))
        self.insert_file_action = QAction('插入文件', self)
        self.insert_file_action.triggered.connect(self.insert_file_link)
        self.insert_menu.addAction(self.insert_file_action)
        self.insert_image_action = QAction('插入图片', self)
        self.insert_image_action.triggered.connect(self.insert_image)
        self.insert_menu.addAction(self.insert_image_action)
        self.insert_link_action = QAction('插入超级链接', self)
        self.insert_link_action.triggered.connect(self.insert_link)
        self.insert_menu.addAction(self.insert_link_action)

        # 创建左侧的 QTreeView
        self.tree_view = QTreeView(self)
        self.tree_view.setFont(QFont(ACTION_FONT, ACTION_FONT_SIZE))
        self.tree_view.setFixedWidth(180)  # 设置固定宽度
        # 创建文件系统模型
        self.file_model = QFileSystemModel()
        self.file_model.setRootPath("/")  # 设置根目录
        # 将模型与 QTreeView 关联
        self.tree_view.setModel(self.file_model)
        self.tree_view.setRootIndex(self.file_model.index("/"))  # 设置根目录索引

        self.text_browser = QTextBrowser()
        self.text_browser.setFont(QFont(TEXT_FONT, TEXT_FONT_SIZE))
        self.text_browser.setWordWrapMode(QTextOption.WordWrap)
        self.text_browser.setHtml("QTextBrowser")
        self.text_browser.setOpenLinks(False)
        self.text_browser.anchorClicked.connect(lambda url: QDesktopServices.openUrl(url))
                
        self.textEdit = QTextEdit(self)
        self.textEdit.setFont(QFont(TEXT_FONT, TEXT_FONT_SIZE))
        self.textEdit.setAcceptRichText(False)
        self.textEdit.hide()
        self.textEdit.textChanged.connect(self.on_textedit_changed)
        
        self.central_widget = QWidget()
        self.layout = QHBoxLayout(self.central_widget)
        self.layout.addWidget(self.tree_view)
        self.layout.addWidget(self.textEdit)
        self.layout.addWidget(self.text_browser)
        self.central_widget.setLayout(self.layout)

        scroll_area = QScrollArea(self)
        scroll_area.setWidgetResizable(True)
        scroll_area.setWidget(self.central_widget)

        self.setCentralWidget(scroll_area)

    def on_toolbtn_pressed(self, qAction):

        if self.textEdit.textCursor().selection().toPlainText()!="":
            selectionTextList = self.textEdit.textCursor().selection().toPlainText().split("\n")
            newSelectionLines = []
            if qAction.text() == "一级缩进":
                newSelectionLines.append("■ " + selectionTextList[0].lstrip())
                newSelectionLines.extend([" "*3+x for x in selectionTextList[1:]])
            elif qAction.text() == "二级缩进":
                newSelectionLines.append("  ◆ " + selectionTextList[0].lstrip())
                newSelectionLines.extend([" "*2+x for x in selectionTextList[1:]])
            else:
                newSelectionLines.append("    ◇ " + selectionTextList[0].lstrip())
                newSelectionLines.extend([" "*2+x for x in selectionTextList[1:]])
            newSelectionText = "\n".join(newSelectionLines)
            self.textEdit.textCursor().removeSelectedText()
            self.textEdit.textCursor().insertText(newSelectionText)
               
    def on_combo_box_activated(self, index):
        selected_text = self.comboBox.itemText(index)
        
        if selected_text == '阅读':
            self.show_mark_down()
            self.status_bar.showMessage("当前在阅读模式！")
        elif selected_text == '编辑':
            self.edit_mark_down()
            self.status_bar.showMessage("当前在编辑模式！")

    def insert_file(self):
        file_path, _ = QFileDialog.getOpenFileName(self, '选择文件', '', '所有文件 (*.*);;文本文件 (*.md)')

        if file_path:
            filename, file_extension = os.path.splitext(os.path.basename(file_path))
            local_folder_path = os.path.join(self.mdFilePath, "resources", file_extension[1:])
            
            if not os.path.exists(local_folder_path):
                os.makedirs(local_folder_path)

            new_file_name = get_md5(file_path)+file_extension
            shutil.copy(file_path, os.path.join(local_folder_path, new_file_name))
            
            file_link = "["+filename + file_extension+"]"+"(file:///" + os.path.join(local_folder_path, new_file_name).replace("\\", "/")+")"
            
            cursor = QTextCursor(self.textEdit.textCursor())
            cursor.insertText(file_link)

    def insert_file_link(self):
        file_path, _ = QFileDialog.getOpenFileName(self, '选择文件', '', '所有文件 (*.*);;文本文件 (*.md)')

        if file_path:
            filename, file_extension = os.path.splitext(os.path.basename(file_path))
            target_file_path = os.path.join("D:\\.kos_file_library", os.path.basename(file_path))

            if os.path.exists(target_file_path):
                old_file_md5 = get_md5(target_file_path)
                new_file_md5 = get_md5(file_path)
                if old_file_md5!=new_file_md5:
                    filename = "_".join((filename, new_file_md5))
                    target_file_path = os.path.join("D:\\.kos_file_library", filename + file_extension)

            shutil.move(file_path, target_file_path)

            file_link = "["+filename + file_extension+"]"+"(file:///" + target_file_path.replace("\\", "/")+")"
            
            cursor = QTextCursor(self.textEdit.textCursor())
            cursor.insertText(file_link)

    def insert_image(self):
        image_path, _ = QFileDialog.getOpenFileName(self, '选择图片', '', '图片文件 (*.png *.xpm *.jpg)')

        if not image_path:
            return

        image_extension = image_path.split('.')[-1]
        image_name = os.path.basename(image_path)
        local_folder_path = os.path.join(self.mdFilePath, "resources", image_extension)
        if not os.path.exists(local_folder_path):
            os.makedirs(local_folder_path)

        new_image_name = get_md5(image_path)+"."+image_extension
        if not os.path.exists(os.path.join(local_folder_path, new_image_name)):
            shutil.copy(image_path, os.path.join(local_folder_path, new_image_name))

        image_url = f'![{image_name}](' + os.path.join(local_folder_path, new_image_name) + ')'
        cursor = QTextCursor(self.textEdit.textCursor())
        cursor.insertText(image_url)

    def insert_link(self):
        link, ok = QInputDialog.getText(self, '插入超级链接', '请输入链接地址：')

        if ok and link:
            cursor = QTextCursor(self.textEdit.textCursor())
            cursor.clearSelection()
            cursor.movePosition(QTextCursor.StartOfWord)
            cursor.insertText('<' + link + '>')
            cursor.movePosition(QTextCursor.EndOfWord)
            cursor.insertText('</' + link + '>')
            self.textEdit.setTextCursor(cursor)

    def on_textedit_changed(self):
        self.text_content = self.textEdit.toPlainText()
            
    def edit_mark_down(self):
        self.insert_menu.setEnabled(True)
        self.action.setEnabled(True)
        self.action_2.setEnabled(True)
        self.action_3.setEnabled(True)
        self.textEdit.setText(self.text_content)
        self.textEdit.show()
        self.text_browser.hide()

    def show_mark_down(self):
        self.insert_menu.setEnabled(False)
        self.action.setEnabled(False)
        self.action_2.setEnabled(False)
        self.action_3.setEnabled(False)
        html_text = get_html_text(self.text_content)
        self.text_browser.setText(html_text)
        self.text_browser.show()
        self.textEdit.hide()

    def set_md_file_path(self, path):
        self.mdFilePath = path

def main():
    app = QApplication(sys.argv)
    editor = MarkdownEditor()
    editor.show()
    sys.exit(app.exec_())

if __name__ == '__main__':
    main()