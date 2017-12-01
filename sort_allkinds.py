#!/usr/bin/python3
# -*- coding: UTF-8 -*-

import math

def radix_sort(lists, radix=10):
	#基数排序，仅仅支持对数字的排序
    k = int(math.ceil(math.log(max(lists), radix)))
    bucket = [[] for i in range(radix)]
    for i in range(1, k+1):
        for j in lists:
            bucket[j/(radix**(i-1)) % (radix**i)].append(j)
        del lists[:]
        for z in bucket:
            lists += z
            del z[:]
    return lists

def merge_sort(lists):
    # 归并排序
    if len(lists) <= 1:
        return lists
    num = int( len(lists) / 2 )
    left = merge_sort(lists[:num])
    right = merge_sort(lists[num:])
    return merge(left, right)
def merge(left, right):
    i, j = 0, 0
    result = []
    while i < len(left) and j < len(right):
        if left[i] <= right[j]:
            result.append(left[i])
            i += 1
        else:
            result.append(right[j])
            j += 1
    result += left[i:]
    result += right[j:]
    return result

def heap_sort(lists):
	#堆排序
    size = len(lists)
    build_heap(lists, size)
    for i in range(0, size)[::-1]:
        lists[0], lists[i] = lists[i], lists[0]
        adjust_heap(lists, 0, i)
def adjust_heap(lists, i, size):
    lchild = 2 * i + 1
    rchild = 2 * i + 2
    max = i
    if i < size / 2:
        if lchild < size and lists[lchild] > lists[max]:
            max = lchild
        if rchild < size and lists[rchild] > lists[max]:
            max = rchild
        if max != i:
            lists[max], lists[i] = lists[i], lists[max]
            adjust_heap(lists, max, size)
def build_heap(lists, size):
    for i in range(0, int(size/2))[::-1]:
        adjust_heap(lists, i, size)

def select_sort(lists):
    # 选择排序
    count = len(lists)
    for i in range(0, count):
        min = i
        for j in range(i + 1, count):
            if lists[min] > lists[j]:
                min = j
        lists[min], lists[i] = lists[i], lists[min]
    return lists

def bubble_sort(lists):
    # 冒泡排序
    count = len(lists)
    for i in range(0, count):
        for j in range(i + 1, count):
            if lists[i] > lists[j]:
                lists[i], lists[j] = lists[j], lists[i]
    return lists

def shell_sort(lists):
	# 希尔排序
	count = len(lists)
	step = 2
	group = count / step
	group = int(group)
	while group > 0:
		for i in range(0, group):
			j = i + group
			while j < count:
				k = j - group
				key = lists[j]
				while k >= 0:
					if lists[k] > key:
						lists[k + group] = lists[k]
						lists[k] = key
					k -= group
				j += group
		group /= step
		group = int(group)
	return lists

def insert_sort(lists):
	# 插入排序
	count = len(lists)
	for i in range(1, count):
		key = lists[i]
		j = i - 1
		while j >= 0:
			if lists[j] > key:
				lists[j + 1] = lists[j]
				lists[j] = key
			j -= 1
	return lists

def quick_sort(L, low, high):
	# 快速排序
    i = low 
    j = high
    if i >= j:
        return L
    key = L[i]
    while i < j:
        while i < j and L[j] >= key:
            j = j-1                                                             
        L[i] = L[j]
        while i < j and L[i] <= key:
            i = i+1 
        L[j] = L[i]
    L[i] = key 
    quick_sort(L, low, i-1)
    quick_sort(L, j+1, high)
    return L

if __name__ == "__main__":

	listA = ["23", "43", "62", "12", "34", "73", "53", "52", "82", "3"]
	listC = [23, 43, 62, 12, 34, 73, 53, 52, 82, 3]
	listB = ["hello","wei","xie","abc","def"]
	
	list_test = listC
	print("原始数据")
	print(list_test)
	
	print("快速排序")
	print(quick_sort(list_test, 0, len(list_test)-1))
	print("插入排序")
	print(insert_sort(list_test))
	print("Shell排序")
	print(shell_sort(list_test))
	print("冒泡排序")
	print(bubble_sort(list_test))
	print("选择排序")
	print(select_sort(list_test))
	print("堆排序")
	print(heap_sort(list_test))
	print("归并排序")
	print(merge_sort(list_test))
	#print("基数排序")
	#print(radix_sort(list_test))
	
	
	
	
	