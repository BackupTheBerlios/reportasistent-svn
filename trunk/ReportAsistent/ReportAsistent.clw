; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSourcesDialog
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ReportAsistent.h"
LastPage=0

ClassCount=9
Class1=CReportAsistentApp
Class2=CSkeletonDoc
Class3=CSkeletonView
Class4=CMainFrame

ResourceCount=8
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class5=CAboutDlg
Resource3=IDD_SOURCES_DIALOG
Resource4=IDD_GENERATE_DIALOG (English (U.S.))
Class6=CElementText
Resource5=IDD_DIALOGTEXT (English (U.S.))
Class7=CSimpleFilterDialog
Resource6=IDD_SIMPLE_FILTER_DIALOG
Class8=CGenerateDialog
Resource7=IDD_ABOUTBOX (English (U.S.))
Class9=CSourcesDialog
Resource8=IDR_MAINFRAME (English (U.S.))

[CLS:CReportAsistentApp]
Type=0
HeaderFile=ReportAsistent.h
ImplementationFile=ReportAsistent.cpp
Filter=N
LastObject=CReportAsistentApp
BaseClass=CWinApp
VirtualFilter=AC

[CLS:CSkeletonDoc]
Type=0
HeaderFile=CSkeletonDoc.h
ImplementationFile=CSkeletonDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC

[CLS:CSkeletonView]
Type=0
HeaderFile=SkeletonView.h
ImplementationFile=SkeletonView.cpp
Filter=C
BaseClass=CTreeView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=CMainFrame
BaseClass=CFrameWnd
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=ReportAsistent.cpp
ImplementationFile=ReportAsistent.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_MRU_FILE1
Command6=ID_APP_EXIT
Command10=ID_EDIT_PASTE
Command11=ID_VIEW_TOOLBAR
Command12=ID_VIEW_STATUS_BAR
Command13=ID_APP_ABOUT
CommandCount=13
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command7=ID_EDIT_UNDO
Command8=ID_EDIT_CUT
Command9=ID_EDIT_COPY

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
CommandCount=13
Command4=ID_EDIT_UNDO
Command13=ID_PREV_PANE


[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_MM
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_MMSOURCES
Command9=ID_APP_ABOUT
CommandCount=9

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_MRU_FILE1
Command6=ID_MMGENREP
Command7=ID_APP_EXIT
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_MMNEWTEXT
Command13=ID_MMNEWPARAGRAPH
Command14=ID_MMNEW4FTHYP
Command15=ID_VIEW_TOOLBAR
Command16=ID_VIEW_STATUS_BAR
Command17=ID_MMSOURCES
Command18=ID_APP_ABOUT
CommandCount=18

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_EDIT_COPY
Command2=ID_FILE_NEW
Command3=ID_FILE_OPEN
Command4=ID_FILE_SAVE
Command5=ID_EDIT_PASTE
Command6=ID_EDIT_UNDO
Command7=ID_EDIT_CUT
Command8=ID_NEXT_PANE
Command9=ID_PREV_PANE
Command10=ID_MMNEW4FTHYP
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_ELEMENT_EDIT
Command14=ID_EDIT_CUT
Command15=ID_EDIT_UNDO
CommandCount=15

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
ControlCount=1
Control1=IDC_STATIC,static,1342308352

[CLS:CElementText]
Type=0
HeaderFile=ElementText.h
ImplementationFile=ElementText.cpp
BaseClass=CDialog
Filter=D
LastObject=CElementText
VirtualFilter=dWC

[DLG:IDD_DIALOGTEXT (English (U.S.))]
Type=1
Class=CElementText
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_DIALTEXT_EDIT,edit,1350631552

[DLG:IDD_SIMPLE_FILTER_DIALOG]
Type=1
Class=CSimpleFilterDialog
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_FILTER_LIST,SysListView32,1350631449
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_DATA_SOURCE_COMBO,combobox,1344340227

[CLS:CSimpleFilterDialog]
Type=0
HeaderFile=SimpleFilterDialog.h
ImplementationFile=SimpleFilterDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=CSimpleFilterDialog
VirtualFilter=dWC

[DLG:IDD_GENERATE_DIALOG (English (U.S.))]
Type=1
Class=CGenerateDialog
ControlCount=1
Control1=IDC_GENERATE_BUTTON,button,1342251009

[CLS:CGenerateDialog]
Type=0
HeaderFile=GenerateDialog.h
ImplementationFile=GenerateDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=CGenerateDialog
VirtualFilter=dWC

[DLG:IDD_SOURCES_DIALOG]
Type=1
Class=CSourcesDialog
ControlCount=9
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDC_PLUGINS_COMBO,combobox,1344340227
Control4=IDC_STATIC,button,1342177287
Control5=IDC_ADD_SOURCE_BUTTON,button,1342242816
Control6=IDC_SOURCES_LIST,SysListView32,1350631429
Control7=IDC_CONNECT_BUTTON,button,1342242816
Control8=IDC_DISCONNECT_BUTTON,button,1342242816
Control9=IDC_RENAME_BUTTON,button,1342242816

[CLS:CSourcesDialog]
Type=0
HeaderFile=SourcesDialog.h
ImplementationFile=SourcesDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_SOURCES_LIST
VirtualFilter=dWC

