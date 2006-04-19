#include <stdafx.h>

#include <afx.h>
#include <afxdb.h>
#include <Shlwapi.h>

#include "SockInterface.h"
#include "InterfaceFunctions.h"
#include "FEPlugin.h"



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
	return NULL;
}


// ---------- fOpenSourceFE

hSource_t fOpenSourceFE(PersistID_t PerzistID)
{
	return NULL;
}


// ---------- fCloseSourceFE

BOOL fCloseSourceFE(hSource_t hSource)
{
	return TRUE;
}

