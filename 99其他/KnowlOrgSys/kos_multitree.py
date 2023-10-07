# -*- coding: UTF-8 -*-
import os

class Node(object):
    def __init__(self, fullname):
        # current node path
        self.FullName = fullname
        self.lChild = []


class MultiTree(object):
    def __init__(self, rootNode):
        self.root = Node(rootNode)

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


if __name__ == "__main__":
    multiTree = MultiTree("root")
    multiTree.add("root", "Python")
    multiTree.add("Python", "CommonFunctions")
    multiTree.add("Python", "FrequentlyAskedQuestions")
    multiTree.add("FAQ", "pipInstallation")
    multiTree.preorder(multiTree.root)
