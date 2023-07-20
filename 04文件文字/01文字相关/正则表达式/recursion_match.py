#!/usr/bin/python3
# -*- coding: UTF-8 -*-
# re does not support recursion, but regex supports recursive mode.
import regex


if __name__ == "__main__":
    pattern = r"\((?:[^()]+|(?R))*+\)"
    test_str = "hello (world (Python))"
    result = regex.findall(pattern, test_str)
    print(result)  # ['(world (Python))']
