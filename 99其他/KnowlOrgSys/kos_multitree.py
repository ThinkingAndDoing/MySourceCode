# -*- coding: UTF-8 -*-
import os

class Node:
    def __init__(self, full_name):
        # current node path
        self.FullName = full_name
        self.lChild = []


class MultiTree(object):
    def __init__(self, root_node):
        self.root = Node(root_node)

    def add(self, nodefullname):
        node = self.find_node(self.root, os.path.dirname(nodefullname))

        if node is not None:
            new_child = Node(nodefullname)
            node.lChild.append(new_child)
            return True
        else:
            return False

    def find_node(self, node, nodefullname):
        if node.FullName == nodefullname:
            return node
        for n in node.lChild:
            childNode = self.find_node(n, nodefullname)
            if childNode is not None:
                return childNode

    def preorder(self, node):
        if node is None:
            return
        print(f"preorder = {node.FullName}")
        for n in node.lChild:
            self.preorder(n)

    def create_node_tree(self, node, node_tree_list):
        if node is None:
            return
        depth = len(node.FullName.split(os.sep)) - len(self.root.FullName.split(os.sep))
        node_tree_list.append("\t"*depth + "* " + os.path.basename(node.FullName))
        for n in node.lChild:
            self.create_node_tree(n, node_tree_list)


if __name__ == "__main__":
    multiTree = MultiTree("root")
    multiTree.add("root", "Python")
    multiTree.add("Python", "CommonFunctions")
    multiTree.add("Python", "FrequentlyAskedQuestions")
    multiTree.add("FAQ", "pipInstallation")
    multiTree.preorder(multiTree.root)
