#!/usr/bin/python3
# -*- coding: UTF-8 -*-


def quickSortByIndex (L, low, high, index):
    i = low 
    j = high
    if i >= j:
        return L
    key = L[i][index]
    temp = L[i]
    while i < j:
        while i < j and L[j][index] >= key:
            j = j-1                                                             
        L[i] = L[j]
        while i < j and L[i][index] <= key:
            i = i+1 
        L[j] = L[i]
    L[i] = temp 
    quickSortByIndex (L, low, i-1, index)
    quickSortByIndex (L, j+1, high, index)
    return L

def quickSort(L, low, high):
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
    quickSort(L, low, i-1)
    quickSort(L, j+1, high)
    return L

if __name__ == "__main__":
	listA = []
	listA.append(["hello",3,"wei"])
	listA.append(["hello",1,"jun"])
	listA.append(["hello",2,"qing"])
	print(listA)
	print(quickSortByIndex( listA, 0, len(listA)-1, 1))

	listB = ["hello","wei","xi","abc","def"]
	print(listB)
	print(quickSort(listB, 0, len(listB)-1))
	
	
