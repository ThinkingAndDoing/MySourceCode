#!/usr/bin/env python3
# -*- cofing: utf-8 -*-

import cv2
import os
import time

output_dir = ""

# 5分钟采样，时间作为图片名称（相似图片删除时间早的），30分钟发送一次，图片压缩


def camera_capture(fn):
    cap = cv2.VideoCapture(0, cv2.CAP_DSHOW)
    ret, frame = cap.read()
    # cv2.imshow('cap', frame)
    output_path = os.path.join(output_dir, fn)
    cv2.imwrite(output_path, frame)
    cap.release()
    cv2.destroyAllWindows()


if __name__ == "__main__":
    camera_capture("capture.png")
    # time.sleep(10)
    # get_current_capture("capture2.png")
