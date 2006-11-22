
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

	APTable[2].AP_ID = "attribute";
	APTable[2].pFn = & fLMAttribute;

	APTable[3].AP_ID = "bool_cedent";
	APTable[3].pFn = & fLMBoolCedent;

	APTable[4].AP_ID = "CF_cedent";
	APTable[4].pFn = & fLMCFCedent;

	APTable[5].AP_ID = "KL_cedent";
	APTable[5].pFn = & fLMKLCedent;

	APTable[6].AP_ID = "task";
	APTable[6].pFn = & fLMTask;

	APTable[7].AP_ID = "quantifier";
	APTable[7].pFn = & fLMQuantifier;

	APTable[8].AP_ID = "hyp_cf";
	APTable[8].pFn = & fLMCFhyp;

	APTable[9].AP_ID = "hyp_sd4ft";
	APTable[9].pFn = & fLMSD4fthyp;

	APTable[10].AP_ID = "hyp_sdcf";
	APTable[10].pFn = & fLMSDCFhyp;

	APTable[11].AP_ID = "hyp_kl";
	APTable[11].pFn = & fLMKLhyp;

	APTable[12].AP_ID = "hyp_sdkl";
	APTable[12].pFn = & fLMSDKLhyp;

	APTable[13].AP_ID = "hyp_4ft_ar2nl";
	APTable[13].pFn = & fLM4fthyp_ar2nl;
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


//============ ReportError() -------------------

int CLMSock::ReportError(UINT nErrorID, const char* FormatString, ...)
{
	CString sFormatStr = FormatString;
	
	va_list params;
	va_start(params, FormatString);

	CString sMessgeText;
	sMessgeText.FormatV(sFormatStr, params);
	
	va_end(params);
	
	CString sOutputText;
	sOutputText.Format("Program error: LMP%03d\n\n%s", nErrorID, (LPCTSTR) sMessgeText);

	return AfxMessageBox(sOutputText);
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