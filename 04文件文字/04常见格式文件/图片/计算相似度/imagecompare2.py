#!/usr/bin/env python3
# -*- cofing: utf-8 -*-
import cv2


def image_difference(image1, image2):
    image11 = cv2.imread(image1)
    gray_image11 = cv2.cvtColor(image11, cv2.COLOR_BGR2GRAY)
    histogram11 = cv2.calcHist([gray_image11], [0], None, [256], [0, 256])

    image22 = cv2.imread(image2)
    gray_image22 = cv2.cvtColor(image22, cv2.COLOR_BGR2GRAY)
    histogram122 = cv2.calcHist([gray_image22], [0], None, [256], [0, 256])
    c = 0
    # Euclidean Distance between image1 and image2
    i = 0
    while i < len(histogram11) and i < len(histogram122):
        c += (histogram11[i] - histogram122[i]) ** 2
        i += 1
    c = c ** (1 / 2)

    return c


if __name__ == "__main__":
    print(image_difference("new_msg.png", "new_msg2.png"))
    print(image_difference("new_msg.png", "new_msg1.png"))
