# Microsoft Developer Studio Project File - Name="LMplugin" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=LMplugin - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "LMplugin.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "LMplugin.mak" CFG="LMplugin - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "LMplugin - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "LMplugin - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "LMplugin - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "LMPLUGIN_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "LMPLUGIN_EXPORTS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x405 /d "NDEBUG"
# ADD RSC /l 0x405 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib Shlwapi.lib /nologo /dll /machine:I386

!ELSEIF  "$(CFG)" == "LMplugin - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "LMPLUGIN_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "LMPLUGIN_EXPORTS" /D "_WINDLL" /D "_AFXDLL" /FR /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x405 /d "_DEBUG"
# ADD RSC /l 0x405 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 Shlwapi.lib /nologo /dll /debug /machine:I386 /out:"../ReportAsistent/plugin/LMplugin.dll" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "LMplugin - Win32 Release"
# Name "LMplugin - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Bool_Cedent_Recordset.cpp
# End Source File
# Begin Source File

SOURCE=.\CF_Cedent_Recordset.cpp
# End Source File
# Begin Source File

SOURCE=.\Equivalence_Lit_Rs.cpp
# End Source File
# Begin Source File

SOURCE=.\functions.cpp
# End Source File
# Begin Source File

SOURCE=.\Hyp_4ft_Recordset.cpp
# End Source File
# Begin Source File

SOURCE=.\InterfaceFunctions.cpp
# End Source File
# Begin Source File

SOURCE=.\KL_Cedent_Recordset.cpp
# End Source File
# Begin Source File

SOURCE=.\LM_Metabase.cpp
# End Source File
# Begin Source File

SOURCE=.\LMplugin.cpp
# End Source File
# Begin Source File

SOURCE=.\LMplugin.def
# End Source File
# Begin Source File

SOURCE=.\SQL_Pomocnik.cpp
# End Source File
# Begin Source File

SOURCE=.\Task_Recordset.cpp
# End Source File
# Begin Source File

SOURCE=.\TAttribute_Recordset.cpp
# End Source File
# Begin Source File

SOURCE=.\TCatDefEnum.cpp
# End Source File
# Begin Source File

SOURCE=.\TCatDefInt.cpp
# End Source File
# Begin Source File

SOURCE=.\TCategory_list.cpp
# End Source File
# Begin Source File

SOURCE=.\Tcategory_Recordset.cpp
# End Source File
# Begin Source File

SOURCE=.\TCategory_Scan.cpp
# End Source File
# Begin Source File

SOURCE=.\TCatOrder.cpp
# End Source File
# Begin Source File

SOURCE=.\TCFLiteral.cpp
# End Source File
# Begin Source File

SOURCE=.\TEmpty_Cedents_Recordset.cpp
# End Source File
# Begin Source File

SOURCE=.\TFTQuantifier_Recordset.cpp
# End Source File
# Begin Source File

SOURCE=.\tiHypothesis_Recordset.cpp
# End Source File
# Begin Source File

SOURCE=.\TKLLiteral.cpp
# End Source File
# Begin Source File

SOURCE=.\TLit_Scan_Recordset.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Bool_Cedent_Recordset.h
# End Source File
# Begin Source File

SOURCE=.\CF_Cedent_Recordset.h
# End Source File
# Begin Source File

SOURCE=.\Equivalence_Lit_Rs.h
# End Source File
# Begin Source File

SOURCE=.\functions.h
# End Source File
# Begin Source File

SOURCE=.\Hyp_4ft_Recordset.h
# End Source File
# Begin Source File

SOURCE=.\InterfaceFunctions.h
# End Source File
# Begin Source File

SOURCE=.\KL_Cedent_Recordset.h
# End Source File
# Begin Source File

SOURCE=.\LM_Metabase.h
# End Source File
# Begin Source File

SOURCE=.\LMplugin.h
# End Source File
# Begin Source File

SOURCE=.\pomocny.h
# End Source File
# Begin Source File

SOURCE=.\SockInterface.h
# End Source File
# Begin Source File

SOURCE=.\SQL_Pomocnik.h
# End Source File
# Begin Source File

SOURCE=.\Task_Recordset.h
# End Source File
# Begin Source File

SOURCE=.\TAttribute_Recordset.h
# End Source File
# Begin Source File

SOURCE=.\TCatDefEnum.h
# End Source File
# Begin Source File

SOURCE=.\TCatDefInt.h
# End Source File
# Begin Source File

SOURCE=.\TCategory_list.h
# End Source File
# Begin Source File

SOURCE=.\Tcategory_Recordset.h
# End Source File
# Begin Source File

SOURCE=.\TCategory_Scan.h
# End Source File
# Begin Source File

SOURCE=.\TCatOrder.h
# End Source File
# Begin Source File

SOURCE=.\TCFLiteral.h
# End Source File
# Begin Source File

SOURCE=.\TEmpty_Cedents_Recordset.h
# End Source File
# Begin Source File

SOURCE=.\TFTQuantifier_Recordset.h
# End Source File
# Begin Source File

SOURCE=.\tiHypothesis_Recordset.h
# End Source File
# Begin Source File

SOURCE=.\TKLLiteral.h
# End Source File
# Begin Source File

SOURCE=.\TLit_Scan_Recordset.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
