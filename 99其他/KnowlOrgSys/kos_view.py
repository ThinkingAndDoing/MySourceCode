# -*- coding: UTF-8 -*-

# pip install PyQt5 -> pip install PyQt5-tools
# http://code.py40.com/2540.html#title-1 QtDesigner安装
# http://code.py40.com/pyqt5/14.html PyQt5教程
# http://code.py40.com/face 使用教程

import os
from PyQt5 import QtCore, QtGui
from PyQt5.QtCore import Qt, QModelIndex
from PyQt5.QtWidgets import QHeaderView, QMenu, QFileDialog
from kos_markdown import MarkdownEditor
import kos_markdown

class View(MarkdownEditor):
    def __init__(self):
        MarkdownEditor.__init__(self)

        self.initViewUI()
        
        self.treeModel = None
        self.viewModel = None
        self.currentRow = ""
        self.itemToBePaste = None
        self.nodeToBePaste = ""


    def initViewUI(self):
        self.setWindowTitle("我的笔记")

        #self.setFixedSize(self.width(), self.height())
        # setStretchLastSection(False) and setSectionResizeMode(QHeaderView.ResizeToContents) for horizontal scroll
        self.tree_view.header().setSectionResizeMode(QHeaderView.ResizeToContents)
        self.tree_view.header().hide()
        # self.tree_view.setDragDropMode(QAbstractItemView.InternalMove)
        # mouse right click menu
        self.tree_view.setContextMenuPolicy(Qt.CustomContextMenu)
        self.tree_view.customContextMenuRequested.connect(self.on_show_menu)
        # mouse left click
        self.tree_view.clicked.connect(self.on_clicked)

        self.textEdit.textChanged.connect(self.on_text_changed)
        # self.tree_view.viewport().installEventFilter(self)

        self.open_file_action.triggered.connect(self.load_info_base)


    def load_info_base(self):
        folder_path = QFileDialog.getExistingDirectory(self, "Select a Folder", "")
        
        if folder_path:
            self.viewModel.model.set_md_file_path(folder_path)
            self.update_tree_model()

    def eventFilter(self, object, event):
        if object is self.tree_view.viewport():
            if event.type() == QtCore.QEvent.Drop:
                print(f"currentIndex={self.tree_view.currentIndex().data()}")
                print(f"currentIndex.parent={self.tree_view.currentIndex().parent().data()}")

            return super(View, self).eventFilter(object, event)

    def set_view_model(self, viewmodel):
        self.viewModel = viewmodel
        self.update_tree_model()

    def update_tree_model(self):
        self.treeModel = self.viewModel.load_treemodel()
        self.tree_view.setModel(self.treeModel)
        self.set_md_file_path(self.viewModel.model.get_md_file_path())
        # tree item data changed
        self.tree_view.selectionModel().model().dataChanged.connect(self.on_item_name_changed)

    def on_show_menu(self, pos):
        self.contextMenu = QMenu(self)
        menu_actions = {
            "增加": self.menu_action_add,
            "删除": self.menu_action_del,
            "剪切": self.menu_action_cut,
            "粘贴": self.menu_action_paste
        }
        for action_text, action_method in menu_actions.items():
            action = self.contextMenu.addAction(action_text)
            action.triggered.connect(action_method)
            if action_text == "粘贴" and self.itemToBePaste is None:
                action.setEnabled(False)
            elif action_text == "粘贴":
                action.setEnabled(True)

        self.currentRow = self.tree_view.currentIndex()
        self.tree_view.expand(self.currentRow)
        self.contextMenu.move(self.pos() + pos)
        self.contextMenu.show()

    def menu_action_add(self):
        # item add
        curItem = self.treeModel.itemFromIndex(self.currentRow)
        nodefullname = os.path.join(curItem.data(Qt.UserRole), curItem.text())
        newItemName = self.viewModel.model.create_md_file(nodefullname)
        newItem = QtGui.QStandardItem(newItemName)
        newItem.setData(nodefullname, Qt.UserRole)
        curItem.appendRow(newItem)

    def menu_action_del(self):
        # item del
        curItem = self.treeModel.itemFromIndex(self.currentRow)
        nodefullname = os.path.join(curItem.data(Qt.UserRole), curItem.text())
        self.viewModel.model.remove_md_file(f"{nodefullname}.md")

        self.treeModel.removeRow(self.currentRow.row(), self.currentRow.parent())

    def menu_action_cut(self):
        # item cut
        parentItem = self.treeModel.itemFromIndex(self.currentRow.parent())
        self.itemToBePaste = parentItem.takeRow(self.currentRow.row())[0]
        self.nodeToBePaste = os.path.join(self.itemToBePaste.data(Qt.UserRole), self.itemToBePaste.text())

    def menu_action_paste(self):
        # item paste
        self.tree_view.selectionModel().model().dataChanged.disconnect()

        curItem = self.treeModel.itemFromIndex(self.currentRow)
        curItem.appendRow(self.itemToBePaste)
        distPath = os.path.join(curItem.data(Qt.UserRole), curItem.text())
        self.viewModel.move_node(self.itemToBePaste, self.nodeToBePaste, distPath)
        self.tree_view.selectionModel().model().dataChanged.connect(self.on_item_name_changed)
        self.itemToBePaste = None

    def on_item_name_changed(self, topLeft, bottomRight):
        # If only one data item has changed, the values of topLeft and bottomRight will be the same.
        # rename_node will change QStandardItem.data, stop monitoring dataChanged before run rename_node to avoid useless events

        # stop monitoring dataChanged
        self.tree_view.selectionModel().model().dataChanged.disconnect()

        newItemName = topLeft.data()
        selectedFileName = self.viewModel.model.get_name_of_file_selected()
        oldItemName = os.path.basename(selectedFileName)[:-3]
        if newItemName!=oldItemName:
            newItemName = self.viewModel.rename_node(selectedFileName[:-3], newItemName)
            curItem = self.treeModel.itemFromIndex(topLeft)
            curItem.setText(newItemName)

        # reconnect dataChanged event
        self.tree_view.selectionModel().model().dataChanged.connect(self.on_item_name_changed)

    @QtCore.pyqtSlot("QModelIndex")
    def on_clicked(self, ix):
        gp = QtGui.QCursor.pos()
        lp = self.tree_view.viewport().mapFromGlobal(gp)
        ix_ = self.tree_view.indexAt(lp)
        curItem = self.treeModel.itemFromIndex(ix_)
        nodefullname = os.path.join(curItem.data(Qt.UserRole), curItem.text())
        # print(f"on_clicked nodefullname={nodefullname}")
        self.viewModel.model.set_name_of_file_selected(f"{nodefullname}.md")

        if not self.comboBox.isEnabled():
            self.comboBox.setDisabled(False)
        if self.text_browser.isHidden():
            self.status_bar.showMessage("当前在编辑模式！")
        else:
            self.status_bar.showMessage("当前在阅读模式！")
        self.text_content = self.viewModel.model.get_content_of_file_selected()
        html_text = kos_markdown.get_html_text(self.text_content)
        self.text_browser.setText(html_text)
        self.textEdit.setText(self.text_content)
        self.setWindowTitle("我的笔记" + "-" + ix_.data())

    def on_text_changed(self):
        if self.text_content!=self.viewModel.model.get_content_of_file_selected():
            self.viewModel.model.set_content_of_file_selected(self.text_content)


