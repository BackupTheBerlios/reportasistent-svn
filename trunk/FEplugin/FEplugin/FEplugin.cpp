#include "stdafx.h"
 

#include "FEplugin.h"
#include "SockInterface.h"
#include "functions.h"
#include "InterfaceFunctions.h"

using namespace System;
using namespace FEplugin_cs;
 

// =========== GLOBALNI PROMENNE =================

CFESock FESock;
CSockInterface SockInterfaceFE;  // rozhrani zasuvky


// =========== class CFESock =====================

// -- konstruktor

CFESock::CFESock()
{
	APCount = _FE_AP_COUNT;
	
	// naplneni tabulky APTable

	APTable[0].AP_ID = "attribute";
	APTable[0].pFn = & fFEAttribute;

	APTable[1].AP_ID = "category";
	APTable[1].pFn = & fFECategory;

	APTable[2].AP_ID = "bool_cedent";
	APTable[2].pFn = & fFEBool_cedent;

	APTable[3].AP_ID = "KL_cedent";
	APTable[3].pFn = & fFEKL_cedent;

	APTable[4].AP_ID = "CF_cedent";
	APTable[4].pFn = & fFECF_cedent;

	// AP hypotezy

	APTable[5].AP_ID = "hyp_4ft";	//  4FT
	APTable[5].pFn = & fFE4fthyp;

	APTable[6].AP_ID = "hyp_sd4ft";  // SD-4FT
	APTable[6].pFn = & fFEsd4fthyp;

	APTable[7].AP_ID = "hyp_kl";	// KL
	APTable[7].pFn = & fFEklhyp;


	APTable[8].AP_ID = "hyp_sdkl";	// SD-KL
	APTable[8].pFn = & fFEsdklhyp;

	APTable[9].AP_ID = "hyp_cf";	// CF
	APTable[9].pFn = & fFEcfhyp;

	APTable[10].AP_ID = "hyp_sdcf";	// SD-CF
	APTable[10].pFn = & fFEsdcfhyp;

	// AP Kvantifikator

	APTable[11].AP_ID = "quantifier";
	APTable[11].pFn = & fFEQuantifier;

	// AP Task

	APTable[12].AP_ID = "task";
	APTable[12].pFn = & fFETask;

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

