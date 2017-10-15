#!/usr/bin/python3

import json


_LangSetting = {'_LangColNum' : 4,
				'_ListLan' : ("Language : 中文","Language : 英语","Language : 西班牙语","Language : 阿拉伯语")
				}


def writeJson(fn, js):
	with open(fn, 'w') as f:
		json.dump(js, f, indent=4, ensure_ascii=False)


def readJson(fn):
	with open(fn, 'r') as f:
		data = json.load(f)
		return eval(str(data))


if __name__ == "__main__":
	writeJson('langsetting.json', _LangSetting)

	LangSetting = readJson("langsetting.json")

	print(LangSetting)


















