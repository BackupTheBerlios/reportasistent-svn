// DirectoriesManager.h: interface for the CDirectoriesManager class.
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
#if !defined(AFX_DIRECTORIESMANAGER_H__230CE075_CAD7_4653_B7B5_39D4A6DC3DDD__INCLUDED_)
#define AFX_DIRECTORIESMANAGER_H__230CE075_CAD7_4653_B7B5_39D4A6DC3DDD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/**
 * class CDirectoriesManager:
 *
 * @author 
 */
class CDirectoriesManager  
{
public:
	CString getWordTemplateDirectory();
	CString getExeFileDirectory();
	CString getApplicationRoot();
	CString getAttrLinkTableStylesDirectory();
	CString getLMRA_WB_WordLoaderPath();
	CString getXMLFilesDirectory();
	CString getElementsDirectory();
	CString getSourcesConfigFilePath();
	CString getPluginsDirectory();
	CDirectoriesManager();
	
	~CDirectoriesManager();

private:
	CString application_root_path;
	CString exe_dir;

public:
	CString getWordStylesConfigFilePath(void);
};

#endif // !defined(AFX_DIRECTORIESMANAGER_H__230CE075_CAD7_4653_B7B5_39D4A6DC3DDD__INCLUDED_)
