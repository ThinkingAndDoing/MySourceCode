#!/usr/bin/python3
# -*- coding: UTF-8 -*-

import tushare as ts
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import talib

from talib import *


if __name__ == "__main__":
    df = ts.get_hist_data("000001", start="2017-08-01", end="2018-08-01")
    # print(df.head(10))
    # df.to_csv("out.csv")
    sz = df.sort_index(axis=0, ascending=True)  # 对index进行升序排列
    sz_return = sz[["p_change"]]  # 选取涨跌幅数据
    train = sz_return[0:255]  # 划分训练集
    test = sz_return[255:]  # 测试集
    # 对训练集与测试集分别做趋势图
    plt.figure(figsize=(10, 5))
    train["p_change"].plot()
    plt.legend(loc="best")
    plt.show()
    plt.figure(figsize=(10, 5))
    test["p_change"].plot(c="r")
    plt.legend(loc="best")
    plt.show()
