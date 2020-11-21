#!/usr/bin/python3
# -*- coding: UTF-8 -*-

import re


def run_re_example():
    # 将从被替换文字中匹配到的内容，作为替换后内容的一部分
    text = 'Today is 11/27/2018. PyCon starts 3/13/2018.'
    print(re.sub(r'(\d+)/(\d+)/(\d+)', r'\3-\1-\2', text))
    print("-" * 20)

    # 前向界定
    text = 'aa<div>test1</div>bb<div>test2</div>cc'
    print(re.search(r'.*(?=bb)', text).group())
    print(re.search(r'(?<=bb).*(?=cc)', text).group())
    print("-" * 20)

    # 贪婪与非贪婪匹配
    text = 'aa<div>test1</div>bb<div>test2</div>cc'
    print(re.search(r'<div>.*</div>', text).group())  # 贪婪式
    print(re.search(r'<div>.*?</div>', text).group())  # 非贪婪式
    print(re.search(r'<div>.*</div>cc', text).group())  # 贪婪式
    print(re.search(r'<div>.*?</div>cc', text).group())  # 非贪婪式
    print("-" * 20)

    # 匹配中文字符的正则表达式： [\u4e00 -\u9fa5], 匹配双字节字符(包括汉字在内)：[^\x00-\xff]
    text = '你好吗 world. I will come! 这个世界'
    pattern = re.compile('([\u4e00-\u9fa5]+)')
    results = pattern.findall(text)
    print(results)


if __name__ == "__main__":
    run_re_example()
