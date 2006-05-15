#include <stdafx.h>

#include <afx.h>
#include <afxdb.h>
#include <Shlwapi.h>

#include "SockInterface.h"
#include "InterfaceFunctions.h"
#include "FEPlugin.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace FEplugin_cs;


// ---------- performFE 

BOOL performFE(hSource_t hSource, const char* APName, BSTR* Result)
{	
	CString CStrResult; // mezivysledek CString
	pFn_t pFn = FESock.getFnAddress(APName);	// ukazatel na funkci, ktera vyridi pozadavek
	if (pFn == NULL) // chyba - neexistuje funkce vyrizujici tento AP
		return FALSE;
	CStrResult = pFn(hSource);
	*Result =  CStrResult.AllocSysString();
	return TRUE;
}

// ---------- getAPListFE

BSTR getAPListFE()
{
	CString CStrResult = FESock.getAPList();
	BSTR Result = CStrResult.AllocSysString();
	return Result;
}


///// funkce rozhrani pro praci se zdroji

// ---------- fNewSourceFE

hSource_t fNewSourceFE(PersistID_t * pPerzistID)
{	
	// dialog pro otevreni souboru -> vybrani souboru (Ferda Project - "*.xfp" ) noveho zdroje
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
	MessageBox::Show("Zdroj s PerzistID=" + perzist + " se nepodarilo otevrit", "Zdroj neotevren");
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
	MessageBox::Show("Zdroj s PerzistID=" + perzist + " se nepodarilo otevrit", "Zdroj neotevren");
	return NULL;

}


// ---------- fCloseSourceFE

BOOL fCloseSourceFE(hSource_t hSource)
{
	int index = ((int) hSource) - 1;  // index prislusneho CFEsource v CFEsourcesTab

	return CFEsourcesTab::CloseSource(index);
}

