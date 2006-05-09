// DirectoriesManager.h: interface for the CDirectoriesManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIRECTORIESMANAGER_H__230CE075_CAD7_4653_B7B5_39D4A6DC3DDD__INCLUDED_)
#define AFX_DIRECTORIESMANAGER_H__230CE075_CAD7_4653_B7B5_39D4A6DC3DDD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDirectoriesManager  
{
public:
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
};

#endif // !defined(AFX_DIRECTORIESMANAGER_H__230CE075_CAD7_4653_B7B5_39D4A6DC3DDD__INCLUDED_)
