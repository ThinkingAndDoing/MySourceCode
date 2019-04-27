#!/usr/bin/python3
# -*- coding: UTF-8 -*-
import pip


if __name__ == '__main__':
	
	for i in pip.pep425tags.get_supported():
		print(i)
	