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

