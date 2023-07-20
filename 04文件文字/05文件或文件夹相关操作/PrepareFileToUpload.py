#!/usr/bin/python3
# -*- coding: UTF-8 -*-

import re
import os
import shutil

global _CurPos
_CurPos = os.getcwd()

_BCTool = "C:\\Program Files (x86)\\Beyond Compare 3"
_CurrentVariant = _CurPos + "\\CurrentVariant.txt"


def getVariant():
    if os.path.exists(_CurrentVariant):
        if os.path.isfile(_CurrentVariant):
            f = open(_CurrentVariant, "r", encoding="utf-8")
            lines = f.readlines()
            f.close()
            if lines != []:
                return lines[0].replace("\n", "")
    return ""


def copy():
    vari = getVariant()
    if vari != "":
        if os.path.exists(_CurPos + "\\variants\\" + vari + "\\hmi\\Model"):
            shutil.rmtree(_CurPos + "\\variants\\" + vari + "\\hmi\\Model")
        shutil.copytree(
            _CurPos + "\\tool\\Model", _CurPos + "\\variants\\" + vari + "\\hmi\\Model"
        )


def compare():
    vari = getVariant()
    if os.path.exists(_BCTool):
        os.chdir(_BCTool)
        os.system(
            "BCompare.exe "
            + _CurPos
            + "\\pkg\\artemmis "
            + _CurPos
            + "\\variants\\"
            + vari
            + "\\hmi\\artemmis"
        )
        os.system(
            "BCompare.exe "
            + _CurPos
            + "\\pkg\\apisub "
            + _CurPos
            + "\\variants\\"
            + vari
            + "\\hmi\\apisub"
        )
        os.system(
            "BCompare.exe "
            + _CurPos
            + "\\pkg\\gs4 "
            + _CurPos
            + "\\variants\\"
            + vari
            + "\\hmi\\gs4"
        )
        os.chdir(_CurPos)
    else:
        print("What a pity! Beyond compare is not found!")


if __name__ == "__main__":
    """
    if os.path.isfile(_OutputFile):
            os.remove(_OutputFile)
    """
    # step 1 open beyond compare and copy files
    copy()
    compare()
