# -*- coding: UTF-8 -*-


class Node(object):
    def __init__(self, item):
        self.elem = item
        self.lChild = []


class MultiTree(object):
    def __init__(self, rootNode):
        self.root = Node(rootNode)

    def add(self, parent, child):
        node = self.find_node(parent, self.root)

        if node is not None:
            new_child = Node(child)
            node.lChild.append(new_child)
            return True
        else:
            return False

    def find_node(self, key, node):
        if node.elem == key:
            return node
        for n in node.lChild:
            childNode = self.find_node(key, n)
            if childNode is not None:
                return childNode

    def preorder(self, node):
        if node is None:
            return
        for n in node.lChild:
            self.preorder(n)


if __name__ == "__main__":
    multiTree = MultiTree("root")
    multiTree.add("root", "Python")
    multiTree.add("Python", "CommonFunctions")
    multiTree.add("Python", "FrequentlyAskedQuestions")
    multiTree.add("FAQ", "pipInstallation")
    multiTree.preorder(multiTree.root)
