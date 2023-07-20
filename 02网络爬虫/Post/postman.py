#!/usr/bin/python3
# -*- coding: UTF-8 -*-
import requests
import json

url = "https://fapiao.glority.cn/v1/item/get_multiple_items_info?app_key=5c74ab6e&timestamp=1559485550&token=8c422e983e63e6f5000b6bcddf1d0b75"


def readJson(fn):
    with open(fn, "r") as f:
        data = json.load(f)
        return eval(str(data))


if __name__ == "__main__":
    headers = {"Content-Type": "application/json"}
    lv_base64data = readJson("json.txt")
    # encode = (json.dumps(lv_base64data))
    print(type(lv_base64data))
    r = requests.post(url, lv_base64data, headers)
    print(r.text)
