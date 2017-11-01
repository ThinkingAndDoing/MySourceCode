#coding=utf-8
import sys
import os
import re
import  xml.dom.minidom
from xml.dom.minidom import Document

sys.setrecursionlimit(10000)

sourceFile = sys.argv[1]

_InputXML = sourceFile
_OutputXML = os.path.splitext(sourceFile)[0] + "_Sorted" + os.path.splitext(sourceFile)[1]

print(_InputXML)
print(_OutputXML)
def quickSortByAttrib(L, low, high):
    i = low 
    j = high
    if i >= j:
        return L
    key = L[i]
    while i < j:
        while i < j and L[j].attributes['Name'].value >= key.attributes['Name'].value:
            j = j-1                                                             
        L[i] = L[j]
        while i < j and L[i].attributes['Name'].value <= key.attributes['Name'].value:    
            i = i+1 
        L[j] = L[i]
    L[i] = key 
    quickSortByAttrib(L, low, i-1)
    quickSortByAttrib(L, j+1, high)
    return L

def createXml(filename, doc):
	f = open(filename, "w")
	xml_str = doc.toprettyxml(indent="\t", newl="\n", encoding="utf-8")
	pretty_str = re.sub(r'\n[\s]*\n', '\n', xml_str)
	f.write(pretty_str)
	f.close()

def copyNodeList(childNodeList, doc):

	resources = doc.createElement("Resources")
	doc.appendChild(resources)
	type = doc.createElement("Type")
	resources.appendChild(type)
	type.appendChild(doc.createTextNode("Images"))

	for node in childNodeList:
		'''
		resource = doc.createElement('Resource')
		resource.setAttribute("Name", node.attributes['Name'].value)
		resource.setAttribute("EnsurePreturn", node.attributes['EnsurePreturn'].value)
		for value in node.getElementsByTagName('Value'):
			resource.appendChild(value)
		'''
		resources.appendChild(node)


if __name__=="__main__":

	rootSrc = xml.dom.minidom.parse(_InputXML).documentElement
	childNodeList = rootSrc.getElementsByTagName('Resource')
	quickSortByAttrib(childNodeList, 0, len(childNodeList)-1)

	docDist = Document()
	copyNodeList(childNodeList, docDist)
	createXml(_OutputXML, docDist)



