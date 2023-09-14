# -*- coding: UTF-8 -*-

import sys
from PyQt5 import QtGui, QtWidgets
import multitree


class TreeModel(object):
    def __init__(self, tree):
        self.tree = tree

    def get_tree(self):
        return self.tree

    def show_tree(self):
        model = self.get_treemodel()
        self.display(model)

    def get_treemodel(self):
        model = QtGui.QStandardItemModel()
        parentItem = model.invisibleRootItem()
        self.recurse_tree_to_item(self.tree.root, parentItem)
        return model

    def recurse_tree_to_item(self, node, parent):
        if node is None:
            return

        item = QtGui.QStandardItem(node.elem)
        parent.appendRow(item)
        for n in node.lChild:
            self.recurse_tree_to_item(n, item)

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
    multiTree = multitree.MultiTree("root")
    multiTree.add("root", "Python")
    multiTree.add("Python", "pyhton1")
    multiTree.add("Python", "pyhton2")

    treeModel = TreeModel(multiTree)
    treeModel.show_tree()


if __name__ == "__main__":
    main()
