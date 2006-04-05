
#include "FEplugin.h"
#include "SockInterface.h"
#include "functions.h"
#include "InterfaceFunctions.h"
#include "SQL_Pomocnik.cpp"



 

// =========== GLOBALNI PROMENNE =================

CFESock FESock;
CSockInterface SockInterfaceFE;  // rozhrani zasuvky


// =========== class CFESock =====================

// -- konstruktor

CFESock::CFESock()
{
	APCount = _FE_AP_COUNT;
	
	// naplneni tabulky APTable   !!!! prozatimni  TODO
	APTable[0].AP_ID = "hyp_4ft";	//na hyp_4ft prepsal deda
	APTable[0].pFn = & fFE4fthyp;

	
	APTable[1].AP_ID = "category";
	APTable[1].pFn = & fFECategory;
}


// ---

pFn_t CFESock::getFnAddress(CString APName)
{
	int i=0;
	while (i<APCount-1   &&   APTable[i].AP_ID != APName)
		i++;
	if (APTable[i].AP_ID == APName)
		return APTable[i].pFn;
	else
		return NULL;
}


// ---
/* vrati seznam vsech ID aktivnich prvku, ktere zasuvka podporuje v tomto XML formatu: 
<LIST>
    <APID NAME="jmeno identifikatoru AP 1"/>
	<APID NAME="jmeno identifikatoru AP 2"/>
	...
</LIST>



*/
CString CFESock::getAPList()
{
	CString result;
	result = "<LIST>";

	for (int i=0; i<APCount; i++)
	{
		result += ("<APID NAME=\"" + APTable[i].AP_ID + "\"/>");
	}

	result += "</LIST>";
	
	return result;
}



// ========== performFE ============================
/*

Nove definovana v InterfaceFunctions.cpp

BOOL performFE (hSource_t hSource, const char* APName, BSTR* Result)
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

hSource_t fNewSourceFE (BSTR* pPerzistID)
{
	// TODO
	return NULL;
}


// ---------- fOpenSourceFE

hSource_t fOpenSourceFE (BSTR PerzistID)
{
	// TODO
	return NULL;
}


// ---------- fCloseSourceFE

BOOL fCloseSourceFE (hSource_t hSource)
{
	// TODO
	return FALSE;
}


*/

///////////////////////////////////////////////
// ---------- initSock

CSockInterface* initSock()
{
	SockInterfaceFE.hPerform = & performFE;
	SockInterfaceFE.hGetAPList = & getAPListFE;
	SockInterfaceFE.hNewSource = & fNewSourceFE;
	SockInterfaceFE.hOpenSource = & fOpenSourceFE;
	SockInterfaceFE.hCloseSource = & fCloseSourceFE;

	return (& SockInterfaceFE);
}

