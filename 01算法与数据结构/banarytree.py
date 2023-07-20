#!/usr/bin/python3
# -*- coding: UTF-8 -*-


class Node(object):
    def __init__(self, item):
        self.elem = item
        self.lchild = None
        self.rchild = None


class Tree(object):
    """二叉树"""

    def __init__(self):
        self.root = Node("root")

    def add(self, item):
        node = Node(item)
        # 一开始root是一个none，那么队列【None】是true的，所以要判断一下
        if self.root is None:
            self.root = node
            return
        queue = [self.root]
        # 判断队列是不是还有没取出来的，
        while queue:
            # 一个一个从头有开始判断有没有左右儿子
            cur_node = queue.pop(0)
            if cur_node.lchild is None:
                cur_node.lchild = node
                return
            else:
                queue.append(cur_node.lchild)
            if cur_node.rchild is None:
                cur_node.rchild = node
                return
            else:
                queue.append(cur_node.rchild)

    def breadth_travel(self):
        """广度变历"""
        if self.root is None:
            return
        queue = [self.root]
        while queue:
            print(queue)
            cur_node = queue.pop(0)
            print(cur_node)
            print(cur_node.elem)
            if cur_node.lchild is not None:
                queue.append(cur_node.lchild)
            if cur_node.rchild is not None:
                queue.append(cur_node.rchild)

    def preorder(self, node):
        """先序变历中左右"""
        if node is None:
            return
        print(node.elem, end=" ")
        self.preorder(node.lchild)
        self.preorder(node.rchild)

    def inorder(self, node):
        """中序变历左中右"""
        if node is None:
            return
        self.inorder(node.lchild)
        print(node.elem, end=" ")
        self.inorder(node.rchild)

    def postorder(self, node):
        """后序变历左右中"""
        if node is None:
            return
        self.postorder(node.lchild)
        self.postorder(node.rchild)
        print(node.elem, end=" ")


if __name__ == "__main__":
    tree = Tree()
    tree.add(1)
    tree.add(2)
    tree.add(3)
    tree.add(4)
    tree.add(5)
    tree.add(6)
    tree.add(7)
    tree.add(8)
    tree.add(9)
    tree.breadth_travel()
    print(" ")
    tree.preorder(tree.root)
    print(" ")
    tree.inorder(tree.root)
    print(" ")
    tree.postorder(tree.root)
