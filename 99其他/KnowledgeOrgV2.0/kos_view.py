# -*- coding: UTF-8 -*-

# pip install PyQt5 -> pip install PyQt5-tools
# http://code.py40.com/2540.html#title-1 QtDesigner安装
# http://code.py40.com/pyqt5/14.html PyQt5教程
# http://code.py40.com/face 使用教程


from PyQt5.QtCore import Qt
from PyQt5.QtWidgets import QMainWindow, QHeaderView, QMenu
from ui import *


class View(QMainWindow, Ui_MainWindow):
    def __init__(self, parent=None):
        super(View, self).__init__(parent)

        self.treeModel = None
        self.viewModel = None
        self.currentRow = ""
        self.itemToBePaste = None
        self.setupUi(self)
        self.setWindowTitle("我的笔记")
        self.setFixedSize(self.width(), self.height())
        # setStretchLastSection(False) and setSectionResizeMode(QHeaderView.ResizeToContents) for horizontal scroll
        self.treeView.header().setSectionResizeMode(QHeaderView.ResizeToContents)
        self.treeView.header().hide()
        # self.treeView.setDragDropMode(QAbstractItemView.InternalMove)

        self.textEdit.textChanged.connect(self.on_text_changed)
        self.toolBar.actionTriggered[QtWidgets.QAction].connect(self.on_toolbtn_pressed)
        # self.treeView.viewport().installEventFilter(self)

    def eventFilter(self, object, event):
        if object is self.treeView.viewport():
            if event.type() == QtCore.QEvent.Drop:
                print("currentIndex=" + self.treeView.currentIndex().data())
                print(
                    "currentIndex.parent="
                    + self.treeView.currentIndex().parent().data()
                )

            return super(View, self).eventFilter(object, event)

    def set_view_model(self, viewmodel):
        self.viewModel = viewmodel
        self.set_tree_model(self.viewModel.get_treemodel())

    def set_tree_model(self, treemodel):
        self.treeModel = treemodel
        self.treeView.setModel(self.treeModel)

        # mouse right click menu
        self.treeView.setContextMenuPolicy(Qt.CustomContextMenu)
        self.treeView.customContextMenuRequested.connect(self.on_show_menu)
        # mouse left click
        self.treeView.clicked.connect(self.on_clicked)
        # tree item data changed
        self.treeView.selectionModel().model().dataChanged.connect(self.on_item_changed)

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
        self.currentRow = self.treeView.currentIndex()
        # expand selected QTreeView Item
        self.treeView.expand(self.currentRow)

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
        lp = self.treeView.viewport().mapFromGlobal(gp)
        ix_ = self.treeView.indexAt(lp)
        if ix_.parent().isValid():
            self.viewModel.set_active_node((ix_.parent().data(), ix_.data()))
        else:
            self.viewModel.set_active_node(("ROOT", ix_.data()))

        self.textEdit.setText(self.viewModel.load_active_node())
        self.setWindowTitle("我的笔记" + "-" + ix_.data())

    def on_text_changed(self):
        self.viewModel.update_active_node(self.textEdit.toPlainText())

    def on_toolbtn_pressed(self, qAction):
        # https://blog.csdn.net/qq_27061049/article/details/89566904

        if self.textEdit.textCursor().selection().toPlainText() != "":
            selectionTextList = (
                self.textEdit.textCursor().selection().toPlainText().split("\n")
            )
            newSelectionLines = []
            if qAction.text() == "一级缩进":
                newSelectionLines.append("■ " + selectionTextList[0].lstrip())
                newSelectionLines.extend([" " * 3 + x for x in selectionTextList[1:]])
            elif qAction.text() == "二级缩进":
                newSelectionLines.append("  ◆ " + selectionTextList[0].lstrip())
                newSelectionLines.extend([" " * 2 + x for x in selectionTextList[1:]])
            else:
                newSelectionLines.append("    ◇ " + selectionTextList[0].lstrip())
                newSelectionLines.extend([" " * 2 + x for x in selectionTextList[1:]])
            newSelectionText = "\n".join(newSelectionLines)
            self.textEdit.textCursor().removeSelectedText()
            self.textEdit.textCursor().insertText(newSelectionText)
