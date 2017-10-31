#coding=utf-8
import sys
import  xml.dom.minidom
from xml.dom.minidom import Document

sys.setrecursionlimit(10000)

_InputXML = 'SAIC_IP31_Images.xml'
_OutputXML = 'SAIC_IP31_Images_Sorted.xml'

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
	f = open(filename, "w", encoding='utf-8')
	f.write(doc.toprettyxml(indent="  "))
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



