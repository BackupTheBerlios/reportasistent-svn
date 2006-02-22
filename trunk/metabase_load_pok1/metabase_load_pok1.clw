; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMetabase_load_pok1Dlg
LastTemplate=CStatic
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "metabase_load_pok1.h"

ClassCount=5
Class1=CMetabase_load_pok1App
Class2=CMetabase_load_pok1Dlg

ResourceCount=4
Resource2=IDD_METABASE_LOAD_POK1_DIALOG
Resource1=IDR_MAINFRAME
Class3=CtiHypothesis_Recordset
Resource3=IDD_METABASE_LOAD_POK1_DIALOG (English (U.S.))
Class4=CXMLTree
Class5=CWordView
Resource4=25002 (English (U.S.))

[CLS:CMetabase_load_pok1App]
Type=0
HeaderFile=metabase_load_pok1.h
ImplementationFile=metabase_load_pok1.cpp
Filter=N

[CLS:CMetabase_load_pok1Dlg]
Type=0
HeaderFile=metabase_load_pok1Dlg.h
ImplementationFile=metabase_load_pok1Dlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_WORD_VIEW



[DLG:IDD_METABASE_LOAD_POK1_DIALOG]
Type=1
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Class=CMetabase_load_pok1Dlg

[DLG:IDD_METABASE_LOAD_POK1_DIALOG (English (U.S.))]
Type=1
Class=CMetabase_load_pok1Dlg
ControlCount=7
Control1=IDC_LOAD_BUTTON,button,1342251008
Control2=IDC_RESULT_EDIT,edit,1353777348
Control3=IDC_XML_BUTTON,button,1342242816
Control4=IDC_XML_PATH_EDIT,edit,1350631552
Control5=IDC_TREE1,SysTreeView32,1350631463
Control6=IDC_GENERXML_BUTTON,button,1342242816
Control7=IDC_WORD_VIEW,static,1342177287

[CLS:CtiHypothesis_Recordset]
Type=0
HeaderFile=tiHypothesis_Recordset.h
ImplementationFile=tiHypothesis_Recordset.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r
LastObject=CtiHypothesis_Recordset

[DB:CtiHypothesis_Recordset]
DB=1
DBType=ODBC
ColumnCount=8
Column1=[HypothesisID], 4, 4
Column2=[TaskID], 4, 4
Column3=[FreqA], 4, 4
Column4=[FreqB], 4, 4
Column5=[FreqC], 4, 4
Column6=[FreqD], 4, 4
Column7=[Weight], 8, 8
Column8=[Ord], 4, 4

[DLG:25002 (English (U.S.))]
Type=1
Class=?
ControlCount=8
Control1=65535,button,1342177287
Control2=65535,static,1342308352
Control3=40960,listbox,1352728993
Control4=1012,button,1342242816
Control5=40964,button,1342242816
Control6=1013,button,1342242816
Control7=2,button,1342242816
Control8=40962,button,1342242817

[CLS:CXMLTree]
Type=0
HeaderFile=XMLTree.h
ImplementationFile=XMLTree.cpp
BaseClass=CTreeCtrl
Filter=W
VirtualFilter=GWC

[CLS:CWordView]
Type=0
HeaderFile=WordView.h
ImplementationFile=WordView.cpp
BaseClass=CStatic
Filter=W
VirtualFilter=WC

