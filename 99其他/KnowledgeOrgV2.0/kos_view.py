# -*- coding: UTF-8 -*-

# pip install PyQt5 -> pip install PyQt5-tools
# http://code.py40.com/2540.html#title-1 QtDesigner安装
# http://code.py40.com/pyqt5/14.html PyQt5教程
# http://code.py40.com/face 使用教程


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
            new_treemodel = self.viewModel.get_treemodel(folder_path)
            if new_treemodel is None:
                self.status_bar.showMessage("无法找到ROOT结点！")
            else:
                self.set_tree_model(new_treemodel)

    def eventFilter(self, object, event):
        if object is self.tree_view.viewport():
            if event.type() == QtCore.QEvent.Drop:
                print("currentIndex=" + self.tree_view.currentIndex().data())
                print(
                    "currentIndex.parent="
                    + self.tree_view.currentIndex().parent().data()
                )

            return super(View, self).eventFilter(object, event)

    def set_view_model(self, viewmodel):
        self.viewModel = viewmodel
        default_treemodel = self.viewModel.get_treemodel()
        if default_treemodel is not None:
            self.set_tree_model(default_treemodel)
        else:
            self.status_bar.showMessage("无法找到ROOT结点！")

    def set_tree_model(self, treemodel):
        self.treeModel = treemodel
        self.tree_view.setModel(self.treeModel)
        self.set_md_file_path(self.viewModel.get_info_base_path())
        # tree item data changed
        self.tree_view.selectionModel().model().dataChanged.connect(self.on_item_changed)
    
    def findIndexByItem(self, model, item, parentIndex=QModelIndex()):
        if not item:
            return QModelIndex()

        for row in range(model.rowCount(parentIndex)):
            index = model.index(row, 0, parentIndex)
            if model.data(index) == item.text():  # 根据项目文本匹配
                return index
            else:
                child_index = self.findIndexByItem(model, item, index)
                if child_index.isValid():
                    return child_index

        return QModelIndex()

    def on_show_menu(self, pos):
        self.contextMenu = QMenu(self)
        self.actionAdd = self.contextMenu.addAction("增加")
        self.actionDel = self.contextMenu.addAction("删除")
        self.actionCut = self.contextMenu.addAction("剪切")
        self.actionPaste = self.contextMenu.addAction("粘贴")
        self.actionAdd.triggered.connect(self.menu_action_add)
        self.actionDel.triggered.connect(self.menu_action_del)
        self.actionCut.triggered.connect(self.menu_action_cut)
        self.actionPaste.triggered.connect(self.menu_action_paste)
        if self.itemToBePaste == None:
            self.actionPaste.setEnabled(False)
        else:
            self.actionPaste.setEnabled(True)

        # get selected QModelIndex
        self.currentRow = self.tree_view.currentIndex()
        # expand selected Qtree_view Item
        self.tree_view.expand(self.currentRow)

        self.contextMenu.move(self.pos() + pos)
        self.contextMenu.show()

    def menu_action_add(self):
        # item add
        newItemName = self.viewModel.add_child_node(self.currentRow.data())
        newItem = QtGui.QStandardItem(newItemName)
        curItem = self.treeModel.itemFromIndex(self.currentRow)
        curItem.appendRow(newItem)

    def menu_action_del(self):
        # item del
        if self.currentRow.parent().data() is not None:
            self.viewModel.del_current_node(
                (self.currentRow.parent().data(), self.currentRow.data())
            )
            self.treeModel.removeRow(self.currentRow.row(), self.currentRow.parent())

    def menu_action_cut(self):
        # item cut
        self.viewModel.rename_leaf_node(
            (self.currentRow.parent().data(), self.currentRow.data()),
            ("None", self.currentRow.data()),
        )
        parentItem = self.treeModel.itemFromIndex(self.currentRow.parent())
        self.itemToBePaste = parentItem.takeRow(self.currentRow.row())[0]

    def menu_action_paste(self):
        # item paste
        self.viewModel.rename_leaf_node(
            ("None", self.itemToBePaste.text()),
            (self.currentRow.data(), self.itemToBePaste.text()),
        )
        curItem = self.treeModel.itemFromIndex(self.currentRow)
        curItem.appendRow(self.itemToBePaste)
        self.itemToBePaste = None

    def on_item_changed(self, topLeft, bottomRight):
        # item rename
        if self.viewModel.get_active_node()[1] != topLeft.data():
            newItemName = self.viewModel.rename_non_leaf_node(bottomRight.data())
            curItem = self.treeModel.itemFromIndex(bottomRight)
            curItem.setText(newItemName)

    @QtCore.pyqtSlot("QModelIndex")
    def on_clicked(self, ix):
        gp = QtGui.QCursor.pos()
        lp = self.tree_view.viewport().mapFromGlobal(gp)
        ix_ = self.tree_view.indexAt(lp)
        if ix_.parent().isValid():
            self.viewModel.set_active_node((ix_.parent().data(), ix_.data()))
        else:
            self.viewModel.set_active_node(("ROOT", ix_.data()))

        if not self.comboBox.isEnabled():
            self.comboBox.setDisabled(False)
        if self.text_browser.isHidden():
            self.status_bar.showMessage("当前在编辑模式！")
        else:
            self.status_bar.showMessage("当前在阅读模式！")
        self.text_content = self.viewModel.load_active_node()
        html_text = kos_markdown.get_html_text(self.text_content)
        self.text_browser.setText(html_text)
        self.textEdit.setText(self.text_content)
        self.setWindowTitle("我的笔记" + "-" + ix_.data())

    def on_text_changed(self):
        if self.text_content!=self.viewModel.load_active_node():
            self.viewModel.update_active_node(self.text_content)


