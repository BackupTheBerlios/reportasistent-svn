
//FEplugin.cpp: implementation(file)
//
//
// This file is part of LM Report Asistent. (http://reportasistent.berlios.de, reportasistent-list@lists.berlios.de)
//
// Authors: Jan Dedek, Jan Kodym, Martin Chrz, Iva Bartunkova 
//
// LM Report Asistent is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// LM Report Asistent is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with LM Report Asistent; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
#include "stdafx.h"
 

#include "FEplugin.h"
#include "SockInterface.h"
#include "functions.h"
#include "InterfaceFunctions.h"

using namespace System;
using namespace FEplugin_cs;
 

// =========== GLOBAL VARIABLES =================

CFESock FESock; /// Global instance of CFESock structure
CSockInterface SockInterfaceFE;  /// Interface structure of FEplugin


// =========== class CFESock =====================

// -- construktor

CFESock::CFESock()
{
	APCount = _FE_AP_COUNT;
	
	// filling the table APTable

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

	// AP hypotheses

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

	// AP Quantifier

	APTable[11].AP_ID = "quantifier";
	APTable[11].pFn = & fFEQuantifier;

	// AP Task

	APTable[12].AP_ID = "task";
	APTable[12].pFn = & fFETask;

	// AP Ferda box

	APTable[13].AP_ID = "ferda_box";
	APTable[13].pFn = & fFEferda_box;

	// AP Column
	APTable[14].AP_ID = "column";
	APTable[14].pFn = & fFEColumn;

	// AP Data matrix
	APTable[15].AP_ID = "data_matrix";
	APTable[15].pFn = & fFEData_matrix;
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
/* returns list of all active elements IDs supported by FEplugin in XML string with structure: 
<LIST>
    <APID NAME="active element ID 1"/>
	<APID NAME="active element ID 2"/>
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

	// inicialization of FEplugin
	if(! FEplugin_cs::FEplugin_init::initialize())  // initialization failed
		return NULL;

	
	return (& SockInterfaceFE);
	
}

