
#define UNICODE
//#define DllExport   __declspec( dllexport )

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#include <windows.h>
#include <objbase.h>
#include <wchar.h>
#include <shlwapi.h>

int WINAPI FindEnumValInTypeLib(LPCSTR _strObjProgId, LPCSTR _strEnumValueName)
//extern "C" DllExport int WINAPI FindEnumValInTypeLib(LPCSTR _strObjProgId, LPCSTR _strEnumValueName)
{
	int retval = -1;

	LPTSTR strObjProgId = NULL;
	LPTSTR strEnumValueName = NULL;

	CLSID		idObjProg;
	CLSID		idLib;
	
	LPOLESTR	strObjClasID = NULL;
	TCHAR		strKeyAdr[500];
	TCHAR		strLibID[500];
	TCHAR		strLibVersion[50];
	
	DWORD dwStrLibID_size = sizeof strLibID;
	DWORD dwStrLibVersion_size = sizeof strLibVersion;
	
	DWORD dwKeyType = REG_SZ;
	
	WORD  wdLibMajorVer;
	WORD  wdLibMinorVer;

	ITypeLib * ptLib = NULL;
	ITypeInfo * ptInfo = NULL;

	MEMBERID rgMemId;
	USHORT pcFound = 1;
	
	VARDESC * pVarDesc = NULL;
	
	HRESULT hr;


	if ((_strObjProgId == NULL) || (_strEnumValueName == NULL)) goto clean_up;

	strObjProgId = new TCHAR[strlen(_strObjProgId)+1];
	strEnumValueName = new TCHAR[strlen(_strEnumValueName)+1];

	//konvertuj vstupni retezce na UNICODE
	MultiByteToWideChar(CP_THREAD_ACP, MB_USEGLYPHCHARS, _strObjProgId,		-1, strObjProgId,	  strlen(_strObjProgId)+1);
	MultiByteToWideChar(CP_THREAD_ACP, MB_USEGLYPHCHARS, _strEnumValueName, -1, strEnumValueName, strlen(_strEnumValueName)+1);

//	ladici vypis
//	MessageBox(NULL, strObjProgId, strEnumValueName, 0);

	
	//ziskej CSID z ProgID
	hr = CLSIDFromProgID(strObjProgId, & idObjProg);
	if (hr != S_OK) goto clean_up;
	
	//preved CSID na string
	hr = StringFromCLSID(idObjProg, & strObjClasID);
	if (hr != S_OK) goto clean_up;

	//vytvor string adresy typelib v registry
	swprintf(strKeyAdr, L"SOFTWARE\\Classes\\CLSID\\%s\\TypeLib", strObjClasID);

	//ziskej TypeLibID z registry
	hr = SHGetValue(HKEY_LOCAL_MACHINE, strKeyAdr, NULL, & dwKeyType, strLibID, & dwStrLibID_size);	
	if (hr != ERROR_SUCCESS) goto clean_up;

	//vytvor string adresy version v registry
	swprintf(strKeyAdr, L"SOFTWARE\\Classes\\CLSID\\%s\\Version", strObjClasID);

	//ziskej Version z registry
	hr = SHGetValue(HKEY_LOCAL_MACHINE, strKeyAdr, NULL, & dwKeyType, strLibVersion, & dwStrLibVersion_size);	
	if (hr != ERROR_SUCCESS) goto clean_up;

	//parsuj strLibVersion
	swscanf(strLibVersion, L"%d.%d", & wdLibMajorVer, & wdLibMinorVer);

	//preved strLibID na idLib
	hr = CLSIDFromString(strLibID, & idLib);
	if (hr != NOERROR) goto clean_up;

	//load TypeLib
	hr = LoadRegTypeLib(idLib, wdLibMajorVer, wdLibMinorVer, SUBLANG_DEFAULT, & ptLib);
	if (hr != S_OK) goto clean_up;

	//vyhledej strEnumValueName v TypeLib-u
	hr = ptLib->FindName(strEnumValueName, 0, & ptInfo, & rgMemId, & pcFound);
	if ((hr != S_OK) || (pcFound == 0)) goto clean_up;

	//zjisti hodnotu pro strEnumValueName
	hr = ptInfo->GetVarDesc(rgMemId & 0x0000FFFF, & pVarDesc);
	if (hr != S_OK) goto clean_up;

	//uloz navratovou hodnotu
	retval = pVarDesc->lpvarValue->lVal;
	
clean_up:		
	delete [] strObjProgId;
	delete [] strEnumValueName;
	
	if (strObjClasID != NULL) CoTaskMemFree(strObjClasID);

	if (ptInfo != NULL)
	{
		if (pVarDesc != NULL) ptInfo->ReleaseVarDesc(pVarDesc);
		ptInfo->Release();
	}


	if (ptLib != NULL) ptLib->Release();

	return retval;
}


