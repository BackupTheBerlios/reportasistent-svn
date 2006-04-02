
#include "LMplugin.h"
#include "SockInterface.h"
#include "functions.h"
#include "InterfaceFunctions.h"
#include "SQL_Pomocnik.cpp"



 

// =========== GLOBALNI PROMENNE =================

CLMSock LMSock;
CSockInterface SockInterfaceLM;  // rozhrani zasuvky


// =========== class CLMSock =====================

// -- konstruktor

CLMSock::CLMSock()
{
	APCount = _LM_AP_COUNT;
	
	// naplneni tabulky APTable   !!!! prozatimni  TODO
	APTable[0].AP_ID = "hyp_4ft";	//na hyp_4ft prepsal deda
	APTable[0].pFn = & fLM4fthyp;

	
	APTable[1].AP_ID = "category";
	APTable[1].pFn = & fLMCategory;
}


// ---

pFn_t CLMSock::getFnAddress(CString APName)
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
CString CLMSock::getAPList()
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



// ========== performLM ============================
/*

Nove definovana v InterfaceFunctions.cpp

BOOL performLM (hSource_t hSource, const char* APName, BSTR* Result)
{
	CString CStrResult; // mezivysledek CString
	pFn_t pFn = LMSock.getFnAddress(APName);	// ukazatel na funkci, ktera vyridi pozadavek
	if (pFn == NULL) // chyba - neexistuje funkce vyrizujici tento AP
		return FALSE;
	CStrResult = pFn(hSource);
	*Result =  CStrResult.AllocSysString();
	return TRUE;
}




// ---------- getAPListLM

BSTR getAPListLM()
{
	CString CStrResult = LMSock.getAPList();
	BSTR Result = CStrResult.AllocSysString();
	return Result;
}


///// funkce rozhrani pro praci se zdroji

// ---------- fNewSourceLM

hSource_t fNewSourceLM (BSTR* pPerzistID)
{
	// TODO
	return NULL;
}


// ---------- fOpenSourceLM

hSource_t fOpenSourceLM (BSTR PerzistID)
{
	// TODO
	return NULL;
}


// ---------- fCloseSourceLM

BOOL fCloseSourceLM (hSource_t hSource)
{
	// TODO
	return FALSE;
}


*/

///////////////////////////////////////////////
// ---------- initSock

CSockInterface* initSock()
{
	SockInterfaceLM.hPerform = & performLM;
	SockInterfaceLM.hGetAPList = & getAPListLM;
	SockInterfaceLM.hNewSource = & fNewSourceLM;
	SockInterfaceLM.hOpenSource = & fOpenSourceLM;
	SockInterfaceLM.hCloseSource = & fCloseSourceLM;

	return (& SockInterfaceLM);
}

/*
// =============== DLL MAIN =======================

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			LMSock = new CLMSock;	// vytvoreni instance tridy CLMSock
			break;

		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			delete(LMSock); // zruseni instance LMSock
			break;
    }
    return TRUE;
}

*/