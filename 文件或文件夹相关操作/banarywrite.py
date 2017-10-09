#!/usr/bin/python3
# -*- coding: UTF-8 -*-

import pickle as p # 这里使用 as 简称,方便更改模块时只需改一行代码

if __name__=="__main__":
	shoplistfile = 'shoplist.data'
	shoplist = ['apple', 'mango', '香蕉', 2, 5]
	f = open(shoplistfile, "wb") # 以二进制写入,Python2.x时可不用二进制,但3.x必须
	p.dump(shoplist, f) # dump the object to a file
	f.close()
	f = open(shoplistfile, "rb") # 以二进制读取
	storedlist2 = p.load(f)
	print(storedlist2)
	f.close()