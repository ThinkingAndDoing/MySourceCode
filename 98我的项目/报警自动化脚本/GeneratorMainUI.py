#!/usr/bin/env python3
#-*- coding:utf-8 -*-

'''
author : zhu cuicui
date   : 2016-10-09 
input: Object.xls output: Object.xml
'''

import tkinter.messagebox
import tkinter.filedialog
from tkinter import *

import os
import sys
import xlrd
import glob

import GeneratorStringXml
import GeneratorDispatcherXml
import GeneratorObjectXml
import GeneratorImgXml
import GeneratorCheckResource
import GeneratorCommonConfig as Config
from GeneratorCommonConfig import AddRunLog

try:
    import xml.etree.cElementTree as ET
except ImportError:
    import xml.etree.ElementTree as ET
    
from xml.dom import minidom 

'''
global variable
'''
thisFile = sys._getframe().f_code.co_filename

Config.requestConfig()

inputExcelName = Config._FileList['_InputExcelName']

LogFile = Config._LogFile

'''
functions
'''
def GetAllIndex(table):
    global indexWLText
    global indexTextWL
    global indexText0
    global indexText1
    global indexPopupBitmap

    keyName = table.row_values(0)
    indexWLText = keyName.index("WLText")
    indexTextWL = keyName.index("TextWL")
    indexText0 = keyName.index("Text0")
    indexText1 = keyName.index("Text1")
    indexPopupBitmap = keyName.index("PopupBitmap")

def exec_function():
    
    print('enter ....',var1.get(),var2.get())
    
    if(var1.get() == 1):
        ret = GeneratorStringXml.Main_GeneratedString()
        if(ret != 0):
            tkinter.messagebox.showerror('Error', 'Please check the log file,Generated string xml  Failed ...')
            return   
    if(var2.get() == 1):
        ret = GeneratorImgXml.Main_GeneratedImg()
        if(ret != 0):
            tkinter.messagebox.showerror('Error', 'Please check the log file,Generated Image xml  Failed ...')
            return      
    if(var3.get() == 1):
        ret = GeneratorObjectXml.Main_GeneratedObject()
        if(ret != 0):
            tkinter.messagebox.showerror('Error', 'Please check the log file,Generated Object xml  Failed ...')
            return  
    if(var4.get() == 1):
        ret = GeneratorDispatcherXml.Main_GeneratedDispatcher()
        if(ret != 0):
            tkinter.messagebox.showerror('Error', 'Please check the log file,Generated Dispatcher xml  Failed ...')
            return  
    
    if(ret == 0):
        tkinter.messagebox.showinfo('information', 'Generated success ...')
 
def Dialog_askDirectory():
    global Fullpath
     
    Fullpath = tkinter.filedialog.askdirectory()
    Lvar1.set(Fullpath)      
 
def AddFilePR():
    if(Lvar2.get() != 'Please enter prefix ...'):
        _path = Lvar1.get()
        _path = _path.replace('/','\\')+r'\\*.png'
        print(_path)
        for filename in glob.glob(_path):
            _filename = filename.split('\\',filename.count('\\'))[filename.count('\\')]
            _filepath = filename.split(_filename,1)[0]
            os.rename(filename,_filepath+Lvar2.get()+_filename)
        tkinter.messagebox.showinfo('information', 'Rename success ...') 
    else:
        tkinter.messagebox.showinfo('information', 'please enter prefix')    

def Check_Configure():
	if GeneratorCheckResource.resourceCheck()==False:
		tkinter.messagebox.showerror('Result','Checked Failed! Please refer to '+ LogFile)
	else:
		tkinter.messagebox.showinfo('info','Checked sucess!')

if __name__ == '__main__':
    root = Tk()
    
    global var1,var2,var3,var4
    
    var1 = IntVar()
    var2 = IntVar()
    var3 = IntVar()
    var4 = IntVar()
    
    root.title('WarningGenerator')
    root.geometry('400x280')
    root.resizable(width = True, height = False)
    
    checkbutton1 = Checkbutton(root,text='Generate String xml',variable = var1,font =('Arial',12))
    checkbutton1.grid(row = 0,column=0,stick = W,padx = 10,pady = 10)
    
    checkbutton2 = Checkbutton(root,text='Generate Image xml',variable = var2,font =('Arial',12))
    checkbutton2.grid(row = 1,column=0,stick = W,padx = 10,pady = 10)
    
    checkbutton3 = Checkbutton(root,text='Generate Object xml',variable = var3,font =('Arial',12))
    checkbutton3.grid(row = 2,column=0,stick = W,padx = 10,pady = 10)
    
    checkbutton4 = Checkbutton(root,text='Generate dispatcher xml',variable = var4,font =('Arial',12))
    checkbutton4.grid(row = 3,column=0,stick = W,padx = 10,pady = 10)
    
    try:
        photo = PhotoImage(file = 'python.gif')
    except:
        tkinter.messagebox.showerror('error','Open python.gif failed !')
        label = Label()
    else:
        label = Label(image = photo)
    #label.image = photo
    label.grid(row = 0,column = 1,columnspan =3,rowspan = 3,stick = W+E+N+S,padx = 5,pady = 5 )

    btn = Button(root,text = 'Generating',font = ('Arial',12),bg = 'green',command = exec_function)
    btn.grid(row = 3,column = 1,stick = W+E,columnspan =3,)

    #Lvar1 = Variable()
    #Lvar2 = Variable()
    
    #lineEdit = Entry(root,textvariable = Lvar1,font =('Arial',10),borderwidth = 2)
    #lineEdit1 = Entry(root,textvariable = Lvar2,font =('Arial',10),borderwidth = 2)
    #Lvar1.set('.\\WarningConfiguration.xlsm')
    #Lvar2.set('Please enter prefix ...')
    
    # Img_check = PhotoImage(file = 'check.gif')
    
    bitcheck1 = Button(root,text = 'Check Strings And Images',font = ('Arial',12),compound = 'left',relief=GROOVE,bg = 'green',command = lambda:Check_Configure())
    bitcheck1.grid(row = 4,column = 0,stick = W,columnspan =2,padx = 10,pady =5)
    
    #bitcheck2 = Button(root,text = 'Check Image',font = ('Arial',12),compound = 'left',relief=GROOVE,bg = 'green',command = lambda:Check_Configure(1))
    #bitcheck2.grid(row = 4,column = 1,stick = W,columnspan =2,pady =5)
    
    #lineEdit.grid(row = 5,column = 0,rowspan = 1,stick = W+E+N+S,padx = 10,pady =5)
    #lineEdit1.grid(row = 6,column = 0,rowspan = 1,stick = W+E+N+S,padx = 10,pady = 5)
    
    #Img_folder = PhotoImage(file = 'folder1.gif')
    #Img_Rename = PhotoImage(file = 'rename1.gif')
     
    #btn1 = Button(root,text = 'Open ....',font = ('Arial',12),compound = 'left',relief=GROOVE,bg = 'green',command = Dialog_askDirectory)
    #btn1.grid(row = 5,column = 1,stick = W,columnspan =2,pady =5)
    
    #btn2 = Button(root,text = 'Rename',font = ('Arial',12),compound = 'left',relief=GROOVE,bg = 'green',command = AddFilePR)
    #btn2.grid(row = 6,column = 1,stick = W,columnspan =2,pady =5)
    
    root.mainloop()