#!/usr/bin/python3
# -*- coding: UTF-8 -*-
import docx


def readDocx(docName):
    fullText = []
    doc = docx.Document(docName)
    paras = doc.paragraphs
    for p in paras:
        fullText.append(p.text)
    return "\n".join(fullText)


content = readDocx("mydoc.docx")

print(content)
