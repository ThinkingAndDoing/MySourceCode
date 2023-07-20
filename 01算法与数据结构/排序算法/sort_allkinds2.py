#!/usr/bin/env python3
# -*-coding:utf-8-*-


def bubble_sort(arr):
    """1.冒泡排序 平均时间复杂度O(n²)"""

    for i in range(1, len(arr)):
        for j in range(0, len(arr) - 1):
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
    return arr


def selection_sort(arr):
    """2.选择排序 平均时间复杂度O(n²)"""

    for i in range(len(arr) - 1):
        # 记录最小数的索引
        minIndex = i
        for j in range(i + 1, len(arr)):
            if arr[j] < arr[minIndex]:
                minIndex = j
        # i 不是最小数时，将 i 和最小数进行交换
        if i != minIndex:
            arr[i], arr[minIndex] = arr[minIndex], arr[i]
    return arr


def insertion_sort(arr):
    """3.插入排序 平均时间复杂度O(n²)"""

    for i in range(len(arr)):
        preIndex = i - 1
        current = arr[i]
        while preIndex >= 0 and arr[preIndex] > current:
            arr[preIndex + 1] = arr[preIndex]
            preIndex -= 1
        arr[preIndex + 1] = current
    return arr


def shell_sort(arr):
    """4.希尔排序 平均时间复杂度O(nlogn)"""

    import math

    gap = 1
    while gap < len(arr) / 3:
        gap = gap * 3 + 1
    while gap > 0:
        for i in range(gap, len(arr)):
            temp = arr[i]
            j = i - gap
            while j >= 0 and arr[j] > temp:
                arr[j + gap] = arr[j]
                j -= gap
            arr[j + gap] = temp
        gap = math.floor(gap / 3)
    return arr


def mergeSort(arr):
    """5.归并排序 平均时间复杂度O(nlogn)"""

    import math

    if len(arr) < 2:
        return arr
    middle = math.floor(len(arr) / 2)
    left, right = arr[0:middle], arr[middle:]
    return merge(mergeSort(left), mergeSort(right))


def merge(left, right):
    result = []
    while left and right:
        if left[0] <= right[0]:
            result.append(left.pop(0))
        else:
            result.append(right.pop(0))
    while left:
        result.append(left.pop(0))
    while right:
        result.append(right.pop(0))
    return result


def quickSort(arr, left=None, right=None):
    """6.快速排序 平均时间复杂度O(nlogn)"""
    left = 0 if not isinstance(left, (int, float)) else left
    right = len(arr) - 1 if not isinstance(right, (int, float)) else right
    if left < right:
        partitionIndex = partition(arr, left, right)
        quickSort(arr, left, partitionIndex - 1)
        quickSort(arr, partitionIndex + 1, right)
    return arr


def partition(arr, left, right):
    pivot = left
    index = pivot + 1
    i = index
    while i <= right:
        if arr[i] < arr[pivot]:
            swap(arr, i, index)
            index += 1
        i += 1
    swap(arr, pivot, index - 1)
    return index - 1


def swap(arr, i, j):
    arr[i], arr[j] = arr[j], arr[i]


def buildMaxHeap(arr):
    """7.堆排序 平均时间复杂度O(nlogn)"""
    import math

    for i in range(math.floor(len(arr) / 2), -1, -1):
        heapify(arr, i)


def heapify(arr, i):
    left = 2 * i + 1
    right = 2 * i + 2
    largest = i
    if left < arrLen and arr[left] > arr[largest]:
        largest = left
    if right < arrLen and arr[right] > arr[largest]:
        largest = right

    if largest != i:
        swap(arr, i, largest)
        heapify(arr, largest)


def swap(arr, i, j):
    arr[i], arr[j] = arr[j], arr[i]


def heapSort(arr):
    global arrLen
    arrLen = len(arr)
    buildMaxHeap(arr)
    for i in range(len(arr) - 1, 0, -1):
        swap(arr, 0, i)
        arrLen -= 1
        heapify(arr, 0)
    return arr


def counting_sort(arr, maxValue):
    """8.计数排序 平均时间复杂度O(n+k)"""

    bucketLen = maxValue + 1
    bucket = [0] * bucketLen
    sortedIndex = 0
    arrLen = len(arr)
    for i in range(arrLen):
        if not bucket[arr[i]]:
            bucket[arr[i]] = 0
        bucket[arr[i]] += 1
    for j in range(bucketLen):
        while bucket[j] > 0:
            arr[sortedIndex] = j
            sortedIndex += 1
            bucket[j] -= 1
    return arr


def bucket_sort(s):
    """9.桶排序 平均时间复杂度O(n+k)"""

    min_num = min(s)
    max_num = max(s)
    # 桶的大小
    bucket_range = (max_num - min_num) / len(s)
    # 桶数组
    count_list = [[] for i in range(len(s) + 1)]
    # 向桶数组填数
    for i in s:
        count_list[int((i - min_num) // bucket_range)].append(i).clear()
    # 回填，这里桶内部排序直接调用了sorted
    for i in count_list:
        for j in sorted(i):
            s.append(j)


def radix(arr):
    """10.基数排序 平均时间复杂度O(n*k)"""

    digit = 0
    max_digit = 1
    max_value = max(arr)
    # 找出列表中最大的位数
    while 10**max_digit < max_value:
        max_digit = max_digit + 1

    while digit < max_digit:
        temp = [[] for i in range(10)]
        for i in arr:
            # 求出每一个元素的个、十、百位的值
            t = int((i / 10**digit) % 10)
            temp[t].append(i)

        coll = []
        for bucket in temp:
            for i in bucket:
                coll.append(i)

        arr = coll
        digit = digit + 1

    return arr


if __name__ == "__main__":
    list_digit = [19, 23, 4, 112, 4, 26, 65, 1, 94, 12]
    print(radix(list_digit))
