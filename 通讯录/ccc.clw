; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CCccView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ccc.h"
LastPage=0

ClassCount=7
Class1=CCccApp
Class2=CCccDoc
Class3=CCccView
Class4=CMainFrame
Class6=CAboutDlg

ResourceCount=4
Resource1=IDR_MAINFRAME
Resource2=IDD_CCC_FORM
Class5=CCccSet
Resource3=IDD_ABOUTBOX
Class7=CPersonDlg
Resource4=IDD_PERSON

[CLS:CCccApp]
Type=0
HeaderFile=ccc.h
ImplementationFile=ccc.cpp
Filter=N

[CLS:CCccDoc]
Type=0
HeaderFile=cccDoc.h
ImplementationFile=cccDoc.cpp
Filter=N

[CLS:CCccView]
Type=0
HeaderFile=cccView.h
ImplementationFile=cccView.cpp
Filter=D
LastObject=CCccView
BaseClass=CRecordView
VirtualFilter=RVWC


[CLS:CCccSet]
Type=0
HeaderFile=cccSet.h
ImplementationFile=cccSet.cpp
Filter=N

[DB:CCccSet]
DB=1
DBType=ODBC
ColumnCount=6
Column1=[name], 12, 100
Column2=[type], 12, 100
Column3=[email], 12, 100
Column4=[address], 12, 100
Column5=[phone], 12, 100
Column6=[describe], 12, 100


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T




[CLS:CAboutDlg]
Type=0
HeaderFile=ccc.cpp
ImplementationFile=ccc.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_RECORD_FIRST
Command2=ID_RECORD_PREV
Command3=ID_RECORD_NEXT
Command4=ID_RECORD_LAST
Command5=ID_APP_ABOUT
CommandCount=5

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_RECORD_FIRST
Command9=ID_RECORD_PREV
Command10=ID_RECORD_NEXT
Command11=ID_RECORD_LAST
Command12=ID_APP_ABOUT
CommandCount=12

[DLG:IDD_CCC_FORM]
Type=1
Class=CCccView
ControlCount=20
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT_NAME,edit,1350631552
Control7=IDC_EDIT_TYPE,edit,1350631552
Control8=IDC_EDIT_ADDRESS,edit,1350631552
Control9=IDC_EDIT_MAIL,edit,1350631552
Control10=IDC_STATIC,static,1342308352
Control11=IDC_EDIT_QUERY,edit,1350631552
Control12=IDC_BUTTON_QUERY,button,1342242817
Control13=IDC_REC_DEL,button,1342242816
Control14=IDC_REC_ADD,button,1342242816
Control15=IDC_REC_EDIT,button,1342242816
Control16=IDC_STATIC,static,1342308352
Control17=IDC_EDIT_PHONE,edit,1350631552
Control18=IDC_STATIC,static,1342308352
Control19=IDC_EDIT_DESCRIBE,edit,1350631552
Control20=IDC_STATIC,static,1342308865

[DLG:IDD_PERSON]
Type=1
Class=CPersonDlg
ControlCount=14
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_EDIT_NAME,edit,1350631552
Control8=IDC_EDIT_TYPE,edit,1350631552
Control9=IDC_EDIT_ADDRESS,edit,1350631552
Control10=IDC_EDIT_MAIL,edit,1350631552
Control11=IDC_STATIC,static,1342308352
Control12=IDC_EDIT_PHONE,edit,1350631552
Control13=IDC_STATIC,static,1342308352
Control14=IDC_EDIT_DESCRIBE,edit,1350631620

[CLS:CPersonDlg]
Type=0
HeaderFile=PersonDlg.h
ImplementationFile=PersonDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDOK

