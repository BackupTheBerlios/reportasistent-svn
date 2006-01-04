#include "stdafx.h"


#import "..\VB-LMRA_WordLoader\LMRA_WordLoader.exe" raw_interfaces_only, raw_native_types, no_namespace, named_guids


void LoadXLMFileToWord(LPCTSTR FilePath)
{
	_LMRA_XML_WordLoader * pWL = NULL;

	IUnknown * pU = NULL;
	
	CoInitialize(NULL);
	HRESULT hr = REGDB_E_CLASSNOTREG;
	hr = CoCreateInstance(CLSID_LMRA_XML_WordLoader, NULL, CLSCTX_LOCAL_SERVER, IID_IUnknown, (void **) & pU);
	if (hr == REGDB_E_CLASSNOTREG)
		MessageBox(NULL, "LMRA_WordLoader.exe neni registorvany - spustte LMRA_WordLoader.exe", "chyba", MB_ICONERROR);
//	CoRegisterClassObject(

	
	if (pU != NULL)
	{
		pU->QueryInterface(IID__LMRA_XML_WordLoader, (void **) & pWL);

		pU->Release();

		
		if (pWL != NULL) 
		{
			BSTR bs;
			TCHAR cd[500];
			
			GetFullPathName(FilePath, 500, cd, NULL);			

			CString s(cd);
			
			hr = pWL->LoadFromFile(s.AllocSysString(), & bs);
			if (hr != S_OK)
				MessageBox(NULL, "XML soubor se nepodarilo precist.", "chyba", MB_ICONERROR);
			
			pWL->Release();
		}
	}


}