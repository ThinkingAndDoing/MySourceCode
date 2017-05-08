#coding=utf-8
import  xml.dom.minidom
from xml.dom.minidom import Document

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

dom = xml.dom.minidom.parse('Strings.xml')
rootSrc = dom.documentElement

docDist = Document()
resources = docDist.createElement("Resources")
docDist.appendChild(resources)
type = docDist.createElement("Type")
resources.appendChild(type)
type.appendChild(docDist.createTextNode("Strings"))
childNodeList = rootSrc.getElementsByTagName('Resource')

quickSortByAttrib(childNodeList, 0, len(childNodeList)-1)

for node in childNodeList:
	resource = docDist.createElement('Resource')
	resources.appendChild(resource)
	resource.setAttribute("Name", node.attributes['Name'].value)
	resource.setAttribute("EnsurePreturn", node.attributes['EnsurePreturn'].value)
	for value in node.getElementsByTagName('Value'):
		resource.appendChild(value)

filename = "new.xml"
f = open(filename, "w", encoding='utf-8')
f.write(docDist.toprettyxml(indent="  "))
f.close()