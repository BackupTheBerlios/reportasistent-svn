// FEPtestap.cpp : Defines the entry point for the console application.
//
#include <afx.h>
#include "stdafx.h"
#include "FEPtestap.h"
#include "../FEplugin/SockInterface.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define _SOCK_IFACE_FN_NAME "initSock"
// typ ukazatel na funkci _SOCK_IFACE_FN_NAME
typedef CSockInterface* (* pSockIfaceFn_t) ();

// The one and only application object

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	
	//BOOL bol = SetCurrentDirectory(L"D:/Projekt/Ferda/Ferda_checkout/bin/FrontEnd/");
	int nRetCode = 0;

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		_tprintf(_T("Fatal Error: MFC initialization failed\n"));
		nRetCode = 1;
	}
	else
	{
		// TODO: code your application's behavior here.
	}

	// pripojeni DLL
	HINSTANCE hLib = LoadLibrary(L"D:/Projekt/Vyvoj/ReportAsistent/Plugin/FEplugin.dll");
	if(hLib == NULL)
	{
		printf("Nepodarilo se pripojit knihovnu\n");
		return -1;
	}
	
	pSockIfaceFn_t pInitFn;
	CSockInterface* SockInterface;

	pInitFn = (pSockIfaceFn_t) GetProcAddress(hLib, _SOCK_IFACE_FN_NAME);
			if(pInitFn != NULL)		// byla nalezena inicializacni funkce knihovny
			{
				// volani inicializacni funkce a nastaveni SockInterface
				SockInterface = pInitFn();
			}
	

	// vyzadani si seznamu vsech AP typu 4ft-hypoteza
	BSTR vys;
	SockInterface->hPerform(NULL, "hyp_4ft", &vys);
	CString vysl(vys);
	printf("%S\n", vysl);
	printf("Size of int:  %d\n", sizeof(int));
	printf("Size of void*:  %d\n", sizeof(void*));

	// vytvoreni noveho zdroje
	PersistID_t NSN;
	hSource_t hSource =	SockInterface->hNewSource(&NSN);
	int vysledek = (int) hSource;
	printf("vratilo to %d\n", vysledek);
	CString s = NSN;
	printf("otevirany soubor: %S\n", NSN);
	


	return nRetCode;
}
