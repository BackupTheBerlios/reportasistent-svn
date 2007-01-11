//LMplugin.cpp
/*
This file is part of LM Report Asistent.

Authors: Jan Dedek, Jan Kodym, Martin Chrz, Iva Bartunkova

LM Report Asistent is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

LM Report Asistent is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with LM Report Asistent; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include "LMplugin.h"
#include "SockInterface.h"
#include "functions.h"
#include "InterfaceFunctions.h"
#include "SQL_Pomocnik.cpp"



 

// =========== GLOBAL VARIABLES =================

CLMSock LMSock;
CSockInterface SockInterfaceLM;  // socket interface


// =========== class CLMSock =====================

// -- constructor

CLMSock::CLMSock()
{
	APCount = _LM_AP_COUNT;
	
	APTable[0].AP_ID = "hyp_4ft";
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

	APTable[14].AP_ID = "data_matrix";
	APTable[14].pFn = & fLMdata_matrix;

	APTable[15].AP_ID = "column";
	APTable[15].pFn = & fLMcolumn;
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
