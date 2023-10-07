# -*- coding: UTF-8 -*-

import os
import sys
from PyQt5 import QtGui, QtWidgets, QtCore
from PyQt5.QtCore import Qt
import kos_multitree


class TreeModel(object):
    def __init__(self):
        pass

    def recurse_replace_item_path(self, node, key_pair):
        item_data_pre = node.data(Qt.UserRole)
        item_data = node.data(Qt.UserRole).replace(key_pair[0], key_pair[1])
        if item_data_pre!=item_data:
            # print(f"{item_data_pre} is changed to {item_data}!")
            node.setData(item_data, Qt.UserRole)

        if node.hasChildren():
            for row in range(node.rowCount()):
                child_node = node.child(row)
                self.recurse_replace_item_path(child_node, key_pair)

    def replace_tree_item_path(self, model, key_pair, parent_index=QtCore.QModelIndex()):
        if not parent_index.isValid():
            parent_item = model.invisibleRootItem()
        else:
            parent_item = model.itemFromIndex(parent_index)

        for row in range(parent_item.rowCount()):
            item = parent_item.child(row)
            item_data_pre = item.data(Qt.UserRole)
            item_data = item.data(Qt.UserRole).replace(key_pair[0], key_pair[1])
            if item_data_pre!=item_data:
                # print(f"{item_data_pre} is changed to {item_data}!")
                item.setData(item_data, Qt.UserRole)

            if item.hasChildren():
                child_index = model.index(row, 0, parent_index)
                self.replace_tree_item_path(model, key_pair, child_index)

    def traverse_tree(self, model, parent_index=QtCore.QModelIndex()):
        if not parent_index.isValid():
            parent_item = model.invisibleRootItem()
        else:
            parent_item = model.itemFromIndex(parent_index)

        for row in range(parent_item.rowCount()):
            item = parent_item.child(row)
            item_data = item.data(Qt.UserRole)

            if item.hasChildren():
                child_index = model.index(row, 0, parent_index)
                self.traverse_tree(model, child_index)

    def create_standard_item_model(self, tree):
        if tree is None:
            return None
        model = QtGui.QStandardItemModel()
        parentItem = model.invisibleRootItem()
        self.recurse_tree_to_item(tree.root, parentItem)
        self.traverse_tree(model)
        return model

    def recurse_tree_to_item(self, node, parent):
        if node is None:
            return
        # current node name
        item_text = os.path.basename(node.FullName)
        # parent node path
        item_data = os.path.dirname(node.FullName)
        item = QtGui.QStandardItem(item_text)
        item.setData(item_data, Qt.UserRole)
        parent.appendRow(item)
        for child_node in node.lChild:
            self.recurse_tree_to_item(child_node, item)

    def show_tree(self, tree):
        model = self.create_standard_item_model(tree)
        self.display(model)

    def display(self, model):
        app = QtWidgets.QApplication.instance()
        if not app:  # create QApplication if it doesnt exist
            app = QtWidgets.QApplication(sys.argv)
        treeView = QtWidgets.QTreeView()
        treeView.setModel(model)
        treeView.show()
        app.exec_()
        return treeView


def main():
    multiTree = kos_multitree.MultiTree("root")
    multiTree.add("root", "Python")
    multiTree.add("Python", "pyhton1")
    multiTree.add("Python", "pyhton2")

    treeModel = TreeModel()
    treeModel.show_tree(multiTree)


if __name__ == "__main__":
    main()
