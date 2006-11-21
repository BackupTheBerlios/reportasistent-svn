# Microsoft Developer Studio Project File - Name="ReportAsistent" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=ReportAsistent - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ReportAsistent.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ReportAsistent.mak" CFG="ReportAsistent - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ReportAsistent - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ReportAsistent - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ReportAsistent - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x405 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x405 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 Shlwapi.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "ReportAsistent - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x405 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x405 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 Shlwapi.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "ReportAsistent - Win32 Release"
# Name "ReportAsistent - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ActiveElementDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\AElConfigDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\AElFiltersConfigDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\AElInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\APTransform.cpp
# End Source File
# Begin Source File

SOURCE=.\AttributeLinkDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\AttributeLinkDialogBase.cpp
# End Source File
# Begin Source File

SOURCE=.\AttributeLinkTableDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\ComplexFilterDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\CSkeletonDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\DataSourceManager.cpp
# End Source File
# Begin Source File

SOURCE=.\DirectoriesManager.cpp
# End Source File
# Begin Source File

SOURCE=.\ElementChapterDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\ElementIncludeDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\ElementManager.cpp
# End Source File
# Begin Source File

SOURCE=.\ElementParagraphDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\ElementReportDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\ElementTextDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\EToolBar.cpp
# End Source File
# Begin Source File

SOURCE=.\GenerateDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\InsertElementTrace.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\OptionsDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\PropertyEditor.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportAsistent.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportAsistent.rc
# End Source File
# Begin Source File

SOURCE=.\SimpleFilterDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\SkeletonView.cpp
# End Source File
# Begin Source File

SOURCE=.\SourcesDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TransformationsDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\WaitAnimation.cpp
# End Source File
# Begin Source File

SOURCE=.\WaitDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\WordEventHandler.cpp
# End Source File
# Begin Source File

SOURCE=.\WordManager.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ActiveElementDialog.h
# End Source File
# Begin Source File

SOURCE=.\AElConfigDialog.h
# End Source File
# Begin Source File

SOURCE=.\AElFiltersConfigDialog.h
# End Source File
# Begin Source File

SOURCE=.\AElInfo.h
# End Source File
# Begin Source File

SOURCE=.\APTransform.h
# End Source File
# Begin Source File

SOURCE=.\AttributeLinkDialog.h
# End Source File
# Begin Source File

SOURCE=.\AttributeLinkDialogBase.h
# End Source File
# Begin Source File

SOURCE=.\AttributeLinkTableDialog.h
# End Source File
# Begin Source File

SOURCE=.\ComplexFilterDialog.h
# End Source File
# Begin Source File

SOURCE=.\CSkeletonDoc.h
# End Source File
# Begin Source File

SOURCE=.\DataSourceManager.h
# End Source File
# Begin Source File

SOURCE=.\DirectoriesManager.h
# End Source File
# Begin Source File

SOURCE=.\ElementChapterDialog.h
# End Source File
# Begin Source File

SOURCE=.\ElementIncludeDialog.h
# End Source File
# Begin Source File

SOURCE=.\ElementManager.h
# End Source File
# Begin Source File

SOURCE=.\ElementParagraphDialog.h
# End Source File
# Begin Source File

SOURCE=.\ElementReportDialog.h
# End Source File
# Begin Source File

SOURCE=.\ElementTextDialog.h
# End Source File
# Begin Source File

SOURCE=.\EToolBar.h
# End Source File
# Begin Source File

SOURCE=.\GenerateDialog.h
# End Source File
# Begin Source File

SOURCE=.\InsertElementTrace.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\OptionsDialog.h
# End Source File
# Begin Source File

SOURCE=.\PropertyEditor.h
# End Source File
# Begin Source File

SOURCE=.\ReportAsistent.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SimpleFilterDialog.h
# End Source File
# Begin Source File

SOURCE=.\SkeletonManager.h
# End Source File
# Begin Source File

SOURCE=.\SkeletonView.h
# End Source File
# Begin Source File

SOURCE=.\SourcesDialog.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TransformationsDialog.h
# End Source File
# Begin Source File

SOURCE=.\WaitAnimation.h
# End Source File
# Begin Source File

SOURCE=.\WaitDialog.h
# End Source File
# Begin Source File

SOURCE=.\WordEventHandler.h
# End Source File
# Begin Source File

SOURCE=.\WordManager.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\4ftHypoteza.bmp
# End Source File
# Begin Source File

SOURCE=.\res\attrLink.bmp
# End Source File
# Begin Source File

SOURCE=.\res\attrLinkTable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmtreebi.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Chapter.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CSkeletonDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\include.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Paragraph.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Report.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ReportAsistent.ico
# End Source File
# Begin Source File

SOURCE=.\res\ReportAsistent.rc2
# End Source File
# Begin Source File

SOURCE=.\res\skeleton_DTD.xml
# End Source File
# Begin Source File

SOURCE=.\res\Table.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Text.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\transformations_logo.bmp
# End Source File
# Begin Source File

SOURCE=.\res\unknowni.bmp
# End Source File
# Begin Source File

SOURCE=.\res\visualization_options_DTD.xml
# End Source File
# End Group
# Begin Source File

SOURCE=.\IvaUzitKonstrukce.txt
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\ReportAsistent.reg
# End Source File
# Begin Source File

SOURCE=..\XML\skeleton_DTD.xml
# End Source File
# Begin Source File

SOURCE=..\XML\visualization_options_DTD.xml
# End Source File
# Begin Source File

SOURCE=.\zlepseni_ovladani.txt
# End Source File
# End Target
# End Project
