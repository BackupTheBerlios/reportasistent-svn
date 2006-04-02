; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CActiveElementDialog
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ReportAsistent.h"
LastPage=0

ClassCount=11
Class1=CReportAsistentApp
Class2=CSkeletonDoc
Class3=CSkeletonView
Class4=CMainFrame

ResourceCount=10
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class5=CAboutDlg
Resource3=IDD_ACTIVE_ELEMENT_DIALOG (English (U.S.))
Resource4=IDD_DIALOGTEXT (English (U.S.))
Class6=CElementTextDialog
Resource5=IDD_SOURCES_DIALOG
Class7=CSimpleFilterDialog
Resource6=IDD_ABOUTBOX (English (U.S.))
Class8=CGenerateDialog
Resource7=IDD_SIMPLE_FILTER_DIALOG (English (U.S.))
Class9=CSourcesDialog
Resource8=IDD_GENERATE_DIALOG (English (U.S.))
Class10=CActiveElementDialog
Resource9=IDD_TRANSFORMATIONS_DIALOG (English (U.S.))
Class11=CTransformationsDialog
Resource10=IDR_MAINFRAME (English (U.S.))

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
LastObject=CSkeletonDoc

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
Command12=ID_MMDELETE
Command13=ID_MMNEWTEXT
Command14=ID_MMNEWPARAGRAPH
Command15=ID_MMNEWCHAPTER
Command16=ID_MMNEW4FTHYP
Command17=ID_VIEW_TOOLBAR
Command18=ID_VIEW_STATUS_BAR
Command19=ID_MMSOURCES
Command20=ID_APP_ABOUT
CommandCount=20

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_EDIT_COPY
Command2=ID_FILE_NEW
Command3=ID_FILE_OPEN
Command4=ID_FILE_SAVE
Command5=ID_EDIT_PASTE
Command6=ID_EDIT_UNDO
Command7=ID_MMDELETE
Command8=ID_EDIT_CUT
Command9=ID_NEXT_PANE
Command10=ID_PREV_PANE
Command11=ID_MMNEW4FTHYP
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_ELEMENT_EDIT
Command15=ID_EDIT_CUT
Command16=ID_EDIT_UNDO
CommandCount=16

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

[DLG:IDD_DIALOGTEXT (English (U.S.))]
Type=1
Class=CElementTextDialog
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_DIALTEXT_EDIT,edit,1350631552

[CLS:CSimpleFilterDialog]
Type=0
HeaderFile=SimpleFilterDialog.h
ImplementationFile=SimpleFilterDialog.cpp
BaseClass=CDialog
Filter=N
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
ControlCount=11
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDC_PLUGINS_COMBO,combobox,1344340227
Control4=IDC_STATIC,button,1342177287
Control5=IDC_ADD_SOURCE_BUTTON,button,1342242816
Control6=IDC_SOURCES_LIST,SysListView32,1350631941
Control7=IDC_OPEN_BUTTON,button,1342242816
Control8=IDC_CLOSE_BUTTON,button,1342242816
Control9=IDC_REMOVE_BUTTON,button,1342242816
Control10=IDC_RENAME_BUTTON,button,1342242816
Control11=IDC_SET_DEFAULT_BUTTON,button,1342242816

[CLS:CSourcesDialog]
Type=0
HeaderFile=SourcesDialog.h
ImplementationFile=SourcesDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=CSourcesDialog
VirtualFilter=dWC

[CLS:CElementTextDialog]
Type=0
HeaderFile=elementtextdialog.h
ImplementationFile=elementtextdialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CElementTextDialog

[CLS:CActiveElementDialog]
Type=0
HeaderFile=ActiveElementDialog.h
ImplementationFile=ActiveElementDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=CActiveElementDialog
VirtualFilter=dWC

[CLS:CTransformationsDialog]
Type=0
HeaderFile=TransformationsDialog.h
ImplementationFile=TransformationsDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=CTransformationsDialog
VirtualFilter=dWC

[DLG:IDD_TRANSFORMATIONS_DIALOG (English (U.S.))]
Type=1
Class=CTransformationsDialog
ControlCount=3
Control1=IDC_STATIC,static,1342177284
Control2=IDC_STATIC,static,1342177284
Control3=IDCANCEL,button,1342242816

[DLG:IDD_SIMPLE_FILTER_DIALOG (English (U.S.))]
Type=1
Class=CSimpleFilterDialog
ControlCount=5
Control1=IDC_FILTER_LIST,SysListView32,1350631449
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_DATA_SOURCE_COMBO,combobox,1344340227

[DLG:IDD_ACTIVE_ELEMENT_DIALOG (English (U.S.))]
Type=1
Class=CActiveElementDialog
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_APPLY_BUTTON,button,1342242816
Control4=IDC_TAB1,SysTabControl32,1342177280
Control5=IDC_SWITCH_BUTTON,button,1342242816

