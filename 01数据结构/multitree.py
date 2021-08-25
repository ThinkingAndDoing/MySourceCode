#!/usr/bin/python3
# -*- coding: UTF-8 -*-

class Node(object):
	def __init__(self,item):
		self.elem = item
		self.lChild = []

class Tree(object):
	"""多叉树"""
	def __init__(self):
		self.root=Node("root")

	def add(self, parent, child):
		node = self.find_node(parent, self.root)
		
		if node is not None:
			new_child = Node(child)
			node.lChild.append(new_child)
			#print(parent+" : "+child+" is added.")
			return True
		else:
			#print(parent+" is not found! Failed to add "+child)
			return False
				
	def find_node(self, key, node):
		"""找到对应Node"""
		if node.elem==key:
			return node
		for n in node.lChild:
			childNode = self.find_node(key, n)
			if childNode is not None:
				return childNode
		
	def preorder(self,node):
		"""先序变历中左右"""
		if node is None:
			return
		print(node.elem,end=" ")
		for n in node.lChild:
			self.preorder(n)



	
if __name__=="__main__":
	
	tree=Tree()
	tree.add('root','Python')
	tree.add('Python','常用功能')
	tree.add('Python','常见问题解决')
	tree.add('常见问题解决','pip安装')
	tree.add('常见问题解','pip安')
	tree.preorder(tree.root)






	
	