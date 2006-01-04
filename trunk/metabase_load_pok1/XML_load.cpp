#include "stdafx.h"


#import "..\VB-LMRA_WordLoader\LMRA_WordLoader.exe" raw_interfaces_only, raw_native_types, no_namespace, named_guids


void LoadXLMFileToWord(LPCTSTR FilePath)
{
	_LMRA_XML_WordLoader * pWL = NULL;

	IUnknown * pU = NULL;
	
	CoCreateInstance(CLSID_LMRA_XML_WordLoader, NULL, CLSCTX_INPROC_SERVER, IID_IUnknown, (void **) & pU);

	
	if (pU != NULL)
	{
		//pU->QueryInterface(IID__LMRA_XML_WordLoader, (void **) & pWL);

		pU->Release();
		if (pWL != NULL) pWL->Release();
	}


}