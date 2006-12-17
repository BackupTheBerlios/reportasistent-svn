// DirectoriesManager.cpp: implementation of the CDirectoriesManager class.
//
//////////////////////////////////////////////////////////////////////
/*
This file is part of LM Report Asistent.

Authors: Jan Dedek, Jan Kodym, Martin Chrz, Iva Bartunkova

LM Report Asistent is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

LM Report Asistent is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with LM Report Asistent; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include "stdafx.h"
#include "ReportAsistent.h"
#include "DirectoriesManager.h"
#include <Shlwapi.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDirectoriesManager::CDirectoriesManager()
{
//	CString dbg = AfxGetApp()->getmo;

//   AfxMessageBox("111dirctories");


	//dedek: tohle chci zprovoznit
	//GetModuleFileName

	TCHAR module_path[MAX_PATH];


	GetModuleFileName(NULL, module_path, MAX_PATH);

	//smaze posledeni tri lomitka: "D:\lmra\ReportAsistent\Debug\ReportAsistent.exe" -> "D:\lmra"
	PathFindFileName(module_path)[-1] = 0;
	exe_dir = module_path;

	PathFindFileName(module_path)[-1] = 0;
	PathFindFileName(module_path)[-1] = 0;

	application_root_path = module_path;

//  AfxMessageBox("222");
}

CDirectoriesManager::~CDirectoriesManager()
{

}

CString CDirectoriesManager::getPluginsDirectory()
{
	return application_root_path + "\\ReportAsistent\\Plugin";
}

CString CDirectoriesManager::getSourcesConfigFilePath()
{
	return application_root_path + "\\ReportAsistent\\ConfigDir\\sources.xml";
}

CString CDirectoriesManager::getElementsDirectory()
{
	return application_root_path + "\\elements";
}

CString CDirectoriesManager::getXMLFilesDirectory()
{
	return application_root_path + "\\XML";
}

CString CDirectoriesManager::getLMRA_WB_WordLoaderPath()
{	
	return application_root_path + "\\VB-LMRA_WordLoader\\LMRA_WordLoader.exe";
}

CString CDirectoriesManager::getAttrLinkTableStylesDirectory()
{
	return application_root_path + "\\XML\\attr_link_table_styles";
}

CString CDirectoriesManager::getApplicationRoot()
{
	return application_root_path + "\\ReportAsistent";
}

CString CDirectoriesManager::getWordTemplateDirectory()
{
	return application_root_path + "\\Word";
}

CString CDirectoriesManager::getExeFileDirectory()
{
	return exe_dir;
}

CString CDirectoriesManager::getWordStylesConfigFilePath(void)
{
	return application_root_path + "\\ReportAsistent\\ConfigDir\\word_styles.xml";
}
