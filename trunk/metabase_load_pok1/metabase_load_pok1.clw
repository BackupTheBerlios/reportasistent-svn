; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CtiHypothesis_Recordset
LastTemplate=CRecordset
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "metabase_load_pok1.h"

ClassCount=5
Class1=CMetabase_load_pok1App
Class2=CMetabase_load_pok1Dlg

ResourceCount=3
Resource2=IDD_METABASE_LOAD_POK1_DIALOG
Resource1=IDR_MAINFRAME
Class5=CtiHypothesis_Recordset
Resource3=IDD_METABASE_LOAD_POK1_DIALOG (English (U.S.))

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
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LOAD_BUTTON,button,1342251008
Control4=IDC_RESULT_EDIT,edit,1353777348

[CLS:CtiHypothesis_Recordset]
Type=0
HeaderFile=tiHypothesis_Recordset.h
ImplementationFile=tiHypothesis_Recordset.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r

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

