#!/usr/bin/python3

import json


def writeJson(fn, js):
	with open(fn, 'w') as f:
		json.dump(js, f, indent=4, ensure_ascii=False)


_FileList = {
    '_InputExcelName' : 'WarningConfiguration.xlsm',
    '_WarningDispatcherFile' : 'WarningDispatchers.xml',
    '_WarningObjectFile' : 'WarningObjects.xml',
    '_GenStrFile' : 'Generated_String.xml',
    '_GenImgFile' : 'Generated_Image.xml'
}

_LangSetting = {'_LangColNum' : 4,
				'_ListLan' : ("Language : 中文","Language : 英语","Language : 西班牙语","Language : 阿拉伯语")
				}
				
_CarType = {'_ModeSuffix' : ("","_SV","_CV"),
			'_ListMode' : ("CarType : Car_Normal", "CarType : Car_SV", "CarType : Car_CV")
			}

_ImgPathList= {'_ListImgPath' : [['.\\..\\..\\GraphicalResources\\Bitmaps\\Bitmaps\\Warning\\Telltales\\', ".\\Bitmaps\\Warning\\Telltales\\", "Telltale_"], ['.\\..\\..\\GraphicalResources\\Bitmaps\\Bitmaps\\Warning\\DoorOpen\\', ".\\Bitmaps\\Warning\\DoorOpen\\", "DoorOpen_"], ['.\\..\\..\\GraphicalResources\\Bitmaps\\Bitmaps\\Warning\\Message\\', ".\\Bitmaps\\Warning\\Message\\", "Message_"]]
}

_WrnObjConf = {"TelltaleP14ExtensionSupportType[]" : ["TelltalesP14","1","No"],
		"WarningExtensionSupportType[]" : ["Warnings","3","Yes","ID","Type","TextWPopup","PopupBitmap","SoundId"]
				}
		
_WrnDispatConf = {"DispatcherName" : "GE_FE_7DA_5DB_Display",
				"WarningStrategy" : {"WSTT1Pos" : ["InsertReversePrioAndSubprio", "SelectCustom"],
									"WSPopup" : ["InsertReversePrioAndSubprio", "SelectCustom"]
									}
				}

if __name__ == "__main__":
	writeJson('data\\filelist.json', _FileList)
	writeJson('data\\langsetting.json', _LangSetting)
	writeJson('data\\cartype.json', _CarType)
	writeJson('data\\imgpathlist.json', _ImgPathList)
	writeJson('data\\wrnobjconf.json', _WrnObjConf)
	writeJson('data\\wrndispatconf.json', _WrnDispatConf)





















