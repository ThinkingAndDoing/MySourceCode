# -*- coding: UTF-8 -*-

import re
import os
import shutil
import hashlib

import sys
from PyQt5.QtWidgets import QApplication, QMainWindow, QTextEdit, QAction, QFileDialog, QVBoxLayout, QPushButton, QWidget, QTextBrowser, QInputDialog
from PyQt5.QtGui import QDesktopServices, QTextCursor
import markdown

def format_html_text(html_text):
    #replace \n as <br/> between <p> and </p>
    new_html_text = re.sub(r'<p>.*?</p>', lambda x: x.group().replace('\n', '<br/>'), html_text, flags=re.DOTALL)
    #keep all space
    new_html_text = "<pre>" + new_html_text + "</pre>"
    return new_html_text

def get_md5(filename):
    with open(filename, 'rb') as f:
        md5 = hashlib.md5()
        while chunk := f.read(1024):
            md5.update(chunk)
    return md5.hexdigest()

def preprocessing(md_content):
    md_content = re.sub(r'file:///[^\.]*/([a-zA-Z0-9]+)\.(\w*)', r"file:///\2/\1.\2", md_content, flags=re.DOTALL)
    md_content = md_content.replace('file:///', "file:///"+os.getcwd().replace("\\", "/") + "/")
    return md_content

class MarkdownEditor(QMainWindow):

    def __init__(self):
        super().__init__()

        self.initUI()
        self.text_content = ""

    def initUI(self):
        self.setWindowTitle('Markdown Editor')
        self.setGeometry(100, 100, 800, 600)
        
        # create toolbar
        self.toolbar = self.addToolBar('插入元素')

        self.insert_file_action = QAction('插入文件', self)
        self.insert_file_action.triggered.connect(self.insert_file)
        self.toolbar.addAction(self.insert_file_action)

        self.insert_image_action = QAction('插入图片', self)
        self.insert_image_action.triggered.connect(self.insert_image)
        self.toolbar.addAction(self.insert_image_action)

        self.insert_link_action = QAction('插入超级链接', self)
        self.insert_link_action.triggered.connect(self.insert_link)
        self.toolbar.addAction(self.insert_link_action)

        self.text_browser = QTextBrowser()
        self.text_browser.setHtml("QTextBrowser")
        self.text_browser.setOpenLinks(False)
        self.text_browser.anchorClicked.connect(lambda url: QDesktopServices.openUrl(url))
                
        self.textEdit = QTextEdit(self)
        self.textEdit.setAcceptRichText(False)
        self.textEdit.hide()
        self.textEdit.textChanged.connect(self.on_textedit_changed)
        
        self.load_button = QPushButton('Load Markdown')
        self.load_button.clicked.connect(self.load_mark_down)
        self.save_button = QPushButton('Save Markdown')
        self.save_button.clicked.connect(self.save_mark_down)
        self.edit_show_button = QPushButton('Edit')
        self.edit_show_button.clicked.connect(self.edit_or_show_markdown)
        
        self.central_widget = QWidget()
        self.layout = QVBoxLayout(self.central_widget)
        self.layout.addWidget(self.textEdit)
        self.layout.addWidget(self.text_browser)
        self.layout.addWidget(self.load_button)
        self.layout.addWidget(self.save_button)
        self.layout.addWidget(self.edit_show_button)
        self.central_widget.setLayout(self.layout)

        self.setCentralWidget(self.central_widget)

    def insert_file(self):
        file_path, _ = QFileDialog.getOpenFileName(self, '选择文件', '', '所有文件 (*.*);;文本文件 (*.txt)')

        if file_path:
            filename, file_extension = os.path.splitext(os.path.basename(file_path))
            local_folder_path = os.path.join(os.getcwd(), file_extension[1:])
            
            if not os.path.exists(local_folder_path):
                os.makedirs(local_folder_path)

            new_file_name = get_md5(file_path)+file_extension
            shutil.copy(file_path, os.path.join(local_folder_path, new_file_name))
            
            file_link = "["+filename + file_extension+"]"+"(file:///" + os.path.join(local_folder_path, new_file_name).replace("\\", "/")+")"
            
            cursor = QTextCursor(self.textEdit.textCursor())
            cursor.insertText(file_link)


    def insert_image(self):
        image_path, _ = QFileDialog.getOpenFileName(self, '选择图片', '', '图片文件 (*.png *.xpm *.jpg)')

        if not image_path:
            return

        image_extension = image_path.split('.')[-1]
        image_name = os.path.basename(image_path)
        local_folder_path = os.path.join(os.getcwd(), image_extension)
        if not os.path.exists(local_folder_path):
            os.makedirs(local_folder_path)

        new_image_name = get_md5(image_path)+"."+image_extension
        shutil.copy(image_path, local_folder_path + '/' + new_image_name)

        local_folder_path = f'./{image_extension}'
        image_url = f'![{image_name}](' + local_folder_path + '/' + new_image_name + ')'
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

    def load_mark_down(self):
        options = QFileDialog.Options()
        options |= QFileDialog.ReadOnly
        filePath, _ = QFileDialog.getOpenFileName(self, 'Open Markdown File', '', 'Markdown Files (*.md);;All Files (*)', options=options)
        
        if filePath:
            with open(filePath, 'r', encoding='utf-8') as file:
                self.text_content = file.read()
                self.text_content = preprocessing(self.text_content)
                self.show_mark_down()

    def save_mark_down(self):
        options = QFileDialog.Options()
        options |= QFileDialog.ReadOnly
        filePath, _ = QFileDialog.getSaveFileName(self, 'Save Markdown File', '', 'Markdown Files (*.md);;All Files (*)', options=options)
        
        if filePath:
            with open(filePath, 'w', encoding='utf-8') as file:
                file.write(self.text_content)
                
    def edit_or_show_markdown(self):
        button_text = self.edit_show_button.text()
        if button_text == "Edit":
            self.edit_mark_down()
        else:
            self.show_mark_down()
            
    def edit_mark_down(self):
        self.edit_show_button.setText("Show")
        self.textEdit.setText(self.text_content)
        self.textEdit.show()
        self.text_browser.hide()

    def show_mark_down(self):
        self.edit_show_button.setText("Edit")
        html_text = markdown.markdown(self.text_content)
        html_text = format_html_text(html_text)
        self.text_browser.setText(html_text)
        self.text_browser.show()
        self.textEdit.hide()

def main():
    app = QApplication(sys.argv)
    editor = MarkdownEditor()
    editor.show()
    sys.exit(app.exec_())

if __name__ == '__main__':
    main()