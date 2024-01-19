# -*- coding: UTF-8 -*-

# pip install PyQt5 -> pip install PyQt5-tools
# http://code.py40.com/2540.html#title-1 QtDesigner安装
# http://code.py40.com/pyqt5/14.html PyQt5教程
# http://code.py40.com/face 使用教程

import os
from PyQt5 import QtCore, QtGui
from PyQt5.QtCore import Qt
from PyQt5.QtWidgets import QHeaderView, QMenu, QFileDialog
from kos_markdownview import MarkdownView

class View(MarkdownView):
    def __init__(self, view_model):
        MarkdownView.__init__(self, view_model.model)

        self.init_view_ui()
        
        self.view_model = view_model
        self.current_row = ""
        self.item_to_be_pasted = None
        self.node_to_be_pasted = ""


    def init_view_ui(self):
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

        self.text_edit_view.textChanged.connect(self.on_text_changed)
        # self.tree_view.viewport().installEventFilter(self)

        self.open_file_action.triggered.connect(self.load_info_base)


    def load_info_base(self):
        folder_path = QFileDialog.getExistingDirectory(self, "Select a Folder", "")
        
        if folder_path:
            self.view_model.model.set_md_file_path(folder_path)
            self.update_tree_view()

    def eventFilter(self, object, event):
        if object is self.tree_view.viewport():
            if event.type() == QtCore.QEvent.Drop:
                print(f"currentIndex={self.tree_view.currentIndex().data()}")
                print(f"currentIndex.parent={self.tree_view.currentIndex().parent().data()}")

            return super(View, self).eventFilter(object, event)

    def update_tree_view(self):
        self.view_model.create_standard_model()
        self.tree_view.setModel(self.view_model.standard_model)
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
            if action_text == "粘贴" and self.item_to_be_pasted is None:
                action.setEnabled(False)
            elif action_text == "粘贴":
                action.setEnabled(True)

        self.current_row = self.tree_view.currentIndex()
        self.tree_view.expand(self.current_row)
        self.contextMenu.move(self.pos() + pos)
        self.contextMenu.show()

    def menu_action_add(self):
        # item add
        curItem = self.view_model.standard_model.itemFromIndex(self.current_row)
        nodefullname = os.path.join(curItem.data(Qt.UserRole), curItem.text())
        newItemName = self.view_model.model.create_md_file(nodefullname)
        newItem = QtGui.QStandardItem(newItemName)
        newItem.setData(nodefullname, Qt.UserRole)
        curItem.appendRow(newItem)

    def menu_action_del(self):
        # item del
        curItem = self.view_model.standard_model.itemFromIndex(self.current_row)
        nodefullname = os.path.join(curItem.data(Qt.UserRole), curItem.text())
        os.remove(f"{nodefullname}.md")

        self.view_model.standard_model.removeRow(self.current_row.row(), self.current_row.parent())

    def menu_action_cut(self):
        # item cut
        parentItem = self.view_model.standard_model.itemFromIndex(self.current_row.parent())
        self.item_to_be_pasted = parentItem.takeRow(self.current_row.row())[0]
        self.node_to_be_pasted = os.path.join(self.item_to_be_pasted.data(Qt.UserRole), self.item_to_be_pasted.text())

    def menu_action_paste(self):
        # item paste
        self.tree_view.selectionModel().model().dataChanged.disconnect()

        curItem = self.view_model.standard_model.itemFromIndex(self.current_row)
        curItem.appendRow(self.item_to_be_pasted)
        distPath = os.path.join(curItem.data(Qt.UserRole), curItem.text())
        self.view_model.move_node(self.item_to_be_pasted, self.node_to_be_pasted, distPath)
        self.tree_view.selectionModel().model().dataChanged.connect(self.on_item_name_changed)
        self.item_to_be_pasted = None

    def on_item_name_changed(self, topLeft, bottomRight):
        # If only one data item has changed, the values of topLeft and bottomRight will be the same.
        # rename_node will change QStandardItem.data, stop monitoring dataChanged before run rename_node to avoid useless events

        # stop monitoring dataChanged
        self.tree_view.selectionModel().model().dataChanged.disconnect()

        newItemName = topLeft.data()
        selectedFileName = self.view_model.model.file_selected
        oldItemName = os.path.basename(selectedFileName)[:-3]
        if newItemName!=oldItemName:
            newItemName = self.view_model.rename_node(selectedFileName[:-3], newItemName)
            curItem = self.view_model.standard_model.itemFromIndex(topLeft)
            curItem.setText(newItemName)

        # reconnect dataChanged event
        self.tree_view.selectionModel().model().dataChanged.connect(self.on_item_name_changed)

    @QtCore.pyqtSlot("QModelIndex")
    def on_clicked(self, ix):
        gp = QtGui.QCursor.pos()
        lp = self.tree_view.viewport().mapFromGlobal(gp)
        ix_ = self.tree_view.indexAt(lp)
        curItem = self.view_model.standard_model.itemFromIndex(ix_)
        nodefullname = os.path.join(curItem.data(Qt.UserRole), curItem.text())
        # print(f"on_clicked nodefullname={nodefullname}")
        self.view_model.model.file_selected = f"{nodefullname}.md"

        if not self.comboBox.isEnabled():
            self.comboBox.setDisabled(False)
        if self.text_browser_view.isHidden():
            self.status_bar.showMessage("当前在编辑模式！")
        else:
            self.status_bar.showMessage("当前在阅读模式！")
        self.text_content = self.view_model.model.get_content_of_file_selected()
        html_text = self.get_html_text(self.text_content)
        self.text_browser_view.setText(html_text)
        self.text_edit_view.setText(self.text_content)
        self.setWindowTitle("我的笔记" + "-" + ix_.data())

    def on_text_changed(self):
        if self.text_content!=self.view_model.model.get_content_of_file_selected():
            self.view_model.model.set_content_of_file_selected(self.text_content)


