#!/usr/bin/python3
# -*- coding: UTF-8 -*-

import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

# 加这个两句 可以显示中文
plt.rcParams["font.sans-serif"] = ["SimHei"]
plt.rcParams["axes.unicode_minus"] = False
colname = "<CLOSE>"


def drawCurve(array, legend_=colname, label_="XAUUSD"):
    array.plot(figsize=(12, 6), grid=True, legend=legend_, label=label_)


def loadFromLocal(fn):
    df = pd.read_csv(fn, dtype={"<TIME>": np.str})
    # print(df[960:961])
    del df["<TICKER>"]
    df[["<DTYYYYMMDD>", "<TIME>"]] = df[["<DTYYYYMMDD>", "<TIME>"]].astype(str)
    df["<TIME>"] = df["<TIME>"].map(lambda x: x[:-4] + ":" + x[-4:-2] + ":" + x[-2:])
    df["<TIME>"] = df["<DTYYYYMMDD>"] + " " + df["<TIME>"]
    # df['<TIME>'] = df['<TIME>'].map(lambda x:parse(x))
    del df["<DTYYYYMMDD>"]
    df[["<VOL>"]] = df[["<VOL>"]].astype(int)
    df[["<OPEN>", "<HIGH>", "<LOW>", "<CLOSE>"]] = df[
        ["<OPEN>", "<HIGH>", "<LOW>", "<CLOSE>"]
    ].astype(float)
    df.set_index("<TIME>", inplace=True)
    return df


if __name__ == "__main__":
    df = loadFromLocal("XAUUSD.txt")
    df = df.iloc[:100]
    # print(df.loc["20180102 07:01:00":"20180102 07:04:00"])
    drawCurve(df[colname], "X", "K")
    print(df[colname])
    plt.scatter(
        list(df.index.values).index("20180102 07:21:00"),
        df.loc["20180102 07:21:00"]["<CLOSE>"],
        marker="o",
        c="",
        edgecolors="r",
    )
    plt.scatter(
        list(df.index.values).index("20180102 07:41:00"),
        df.loc["20180102 07:41:00"]["<CLOSE>"],
        marker="o",
        c="",
        edgecolors="r",
    )
    plt.show()
