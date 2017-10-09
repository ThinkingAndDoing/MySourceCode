#!/usr/bin/python3
# -*- coding: UTF-8 -*-

import re
import os
import shutil

global _CurPos
global _BCTool

_CurPos = os.getcwd()
_BCTool = "C:\Program Files (x86)\Beyond Compare 3"

_InputFile = ".\\pkg\\apisub\\pkg\\apimgr\\adapt\\API_Device_WDA\\API_Device_WDA_Api.c"
functypelist = ["u16", "bo", "v", "u8", "u32"]

def readFile(fn):
	f = open(fn, "r", encoding='utf-8')
	data = f.read()
	f.close()
	return data
	
def writeFile(fn, data):
	f = open(fn, "w", encoding='utf-8')
	f.write(data)
	f.close()

def funcModify(fn, funcbody):
	if funcbody.find(fn)!=-1:
		#print(fn)
		thefuncbody = re.search( r''+ fn +'[ ]*\([ ]*[\w]+[ ]*[\w_]+[ ]*\)[^\{]+{[^\}]+}', funcbody, re.I).group()
		remainlist = funcbody.split(thefuncbody)
		thenewfuncbody = funcBodyModify(thefuncbody)
		return remainlist[0] + thenewfuncbody + remainlist[1]
	else:
		return funcbody
	
def funcBodyModify(funcbody):
	if funcbody.find('_u16Set')!=-1 or funcbody.find('_boSet')!=-1 or funcbody.find('_vSet')!=-1\
	 or funcbody.find('_u8Set')!=-1 or funcbody.find('_u32Set')!=-1:
		newbody = ""
		pattern = re.compile(r'\( [\w]+ ([\w]+) \)')
		match = re.findall(pattern, funcbody)
		if match==[]:
			print("Error! Please check!")
			return newbody
		funcname = match[0]
		_getfuncname = re.sub(r'_u16', '_u16Get', funcname)
		_getfuncname = re.sub(r'_bo', '_boGet', _getfuncname)
		_getfuncname = re.sub(r'_v', '_vGet', _getfuncname)
		_getfuncname = re.sub(r'_u8', '_u8Get', _getfuncname)
		_getfuncname = re.sub(r'_u32', '_u32Get', _getfuncname)
		newstr = "    APIM_boSetData( APIM_nDId_"+_getfuncname+" , &"+funcname+", (uint16)sizeof("+funcname+") );\n}"
		newbody = funcbody.replace("}", newstr)
		return newbody
	else:
		return funcbody

'''
void WRN_vSetSelectedWarningCount ( uint16 WRN_u16SelectedWarningCount ) /* @status Prototype */ 
{
    /****************************************************************************************** 
     * Setter : 
     * @response  => NONE
     * @return    => void
      * @param	 WRN_u16SelectedWarningCount - value to setWRN_u16SelectedWarningCount to.
     ******************************************************************************************/

}
'''
if __name__ == "__main__":
	'''
	if os.path.isfile(_OutputFile):
		os.remove(_OutputFile)
	'''
	#step 1
	''''''
	data = readFile(_InputFile)
	newdata = re.sub(r'@status Prototype', "@status Implemented", data)
	#newdata = re.sub(r'void [a-zA-Z]+_[a-zA-Z]+Set[a-zA-Z]+ ( [a-zA-Z]+ [a-zA-Z_]+ ) /* @status Prototype */', "Divider=\"3\"", data)
	writeFile(_InputFile, newdata)
	
	#step 2

	data = readFile(_InputFile)
	#pattern = re.compile(r'(void [\w]+_[\w]+Set[\w]+ \( [\w]+ [\w_]+ \))')
	vpattern = re.compile(r'(void[ ]*[a-zA-Z0-9]+_vSet[a-zA-Z0-9]+)[ ]*\([ ]*')
	u16pattern = re.compile(r'(void[ ]*[a-zA-Z0-9]+_u16Set[a-zA-Z0-9]+)[ ]*\([ ]*')
	bopattern = re.compile(r'(void[ ]*[a-zA-Z0-9]+_boSet[a-zA-Z0-9]+)[ ]*\([ ]*')
	u8pattern = re.compile(r'(void[ ]*[a-zA-Z0-9]+_u8Set[a-zA-Z0-9]+)[ ]*\([ ]*')
	u32pattern = re.compile(r'(void[ ]*[a-zA-Z0-9]+_u32Set[a-zA-Z0-9]+)[ ]*\([ ]*')
	allfunnames = re.findall(vpattern, data) + re.findall(u16pattern, data) + re.findall(bopattern, data) + re.findall(u8pattern, data) + re.findall(u32pattern, data)
	print(allfunnames)
	for fn in allfunnames:
		data = funcModify(fn, data)
	writeFile(_InputFile, data)
	
	#step 3 open beyond compare	 ([\w]+ [\w]+_[\w]+Get[\w]+ \( void \) /[^/]+/[^{]+{[^}]+}) | (void [\w]+_[\w]+Set[\w]+ \( [\w]+ [\w_]+ \)[^\{]+{[^\}]+})

	#_CurPos = D:\Project\Saic\EP22\EP22Target\pkg_mks
	#D:\Project\Saic\EP22\EP22Target\pkg_mks\pkg\apisub\pkg\apimgr\adapt\API_Device_WDA
	#D:\Project\Saic\EP22\EP22Target\pkg_mks\pkg\artemmis\adapt\WDA_WidgetDummyApp\core
	''''''
	if os.path.exists(_BCTool):
		os.chdir(_BCTool)
		os.system("BCompare.exe "+_CurPos+"\\pkg\\apisub\\pkg\\apimgr\\adapt\\API_Device_WDA "+_CurPos+"\\pkg\\artemmis\\adapt\\WDA_WidgetDummyApp\\core")
		os.chdir(_CurPos)
	else:
		print("What a pity! Beyond compare is not found!")
	

