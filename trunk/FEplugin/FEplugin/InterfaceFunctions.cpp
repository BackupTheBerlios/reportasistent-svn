#include <stdafx.h>

#include <afx.h>
#include <afxdb.h>
#include <Shlwapi.h>

#include "SockInterface.h"
#include "InterfaceFunctions.h"
#include "FEPlugin.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::IO;
using namespace FEplugin_cs;


// ---------- performFE 

BOOL performFE(hSource_t hSource, const char* APName, BSTR* Result)
{	
	CString CStrResult; // result CString
	pFn_t pFn = FESock.getFnAddress(APName);	// pointer to function which evaluates the query
	if (pFn == NULL) // error - function evaluating querries about this active element doesn't exist
		return FALSE;

	// change actual directory on home LMRA dir
	DirManager::SetHomeLMRA_dir();

	CStrResult = pFn(hSource);
	*Result =  CStrResult.AllocSysString();
	
	// revert actual directory
	DirManager::SetHomePrevious_dir();

	return TRUE;
}

// ---------- getAPListFE

BSTR getAPListFE()
{
	CString CStrResult = FESock.getAPList();
	BSTR Result = CStrResult.AllocSysString();
	return Result;
}


///// operations with data sources functions

// ---------- fNewSourceFE

hSource_t fNewSourceFE(PersistID_t * pPerzistID)
{	
	// open file dialog -> selecting the file (Ferda Project - "*.xfp" ) of new data source
	System::String^ perzist = FEPom::OpenXfpFile();

	CString s = (CString) perzist;
	(*pPerzistID) = s.AllocSysString();
	int index = 0;
	if (perzist != "")
	{
		index = CFEsourcesTab::NewSource(perzist);
		if(index != -1)
			return (hSource_t) (index + 1);
	}
	// MessageBox::Show("Data source (Perzist ID: " + perzist + ") could not be open.", "ReportAsistent - FE plugin");
	return NULL;


}


// ---------- fOpenSourceFE

hSource_t fOpenSourceFE(PersistID_t PerzistID)
{
	CString per = PerzistID;
	System::String^ perzist = gcnew String(per);

	int index = 0;
	if (perzist != "")
	{
		index = CFEsourcesTab::NewSource(perzist);
		if(index != -1)
		   return (hSource_t) (index + 1);
	}
	//MessageBox::Show("Data source (Perzist ID: " + perzist + ") could not be open.", "ReportAsistent - FE plugin");
	return NULL;

}


// ---------- fCloseSourceFE

BOOL fCloseSourceFE(hSource_t hSource)
{
	int index = ((int) hSource) - 1;  // index of CFEsource in CFEsourcesTab

	return CFEsourcesTab::CloseSource(index);
}

