#!/usr/bin/python3
# -*- coding: UTF-8 -*-

import cv2


def cut_image(cutarea, srcimage):
    if cutarea is not None:
        x, y, w, h = cutarea
        src = cv2.imread(srcimage, cv2.IMREAD_UNCHANGED)
        dst = src[y : h + y, x : w + x]
        cv2.imwrite(srcimage, dst)


if __name__ == "__main__":
    cut_image((100, 100, 200, 200), "3.jpg")
