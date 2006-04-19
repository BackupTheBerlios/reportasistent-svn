/*
InterfaceFunctions.h
LM - Report Asistent

- implementace funkci zasuvky pro Ferdu
- popis rozhrani - viz "SockInterface.h"
*/


#ifndef _INTERFACE_FUNCTIONS_FE
#define _INTERFACE_FUNCTIONS_FE

#include <afx.h>
#include "SockInterface.h"
#include <wtypes.h>




// =========== FUNKCE =============================

/////// funkce, ktere tvori rozhrani mezi zasuvkou a "spravcem zasuvek a zdroju"
/////// (odkaz na ne ze struktury CSockInterface)

// ---------- performFE 
/*
hlavni rozhrani mezi jadrem a FE zasuvkou - vyrizuje vsechny pozadavky jadra na poskytnuti vsech 
AP urciteho typu z nektereho zdroje  pripojeneho k teto zasuvce

parametry:  hSource - otevreny handle na zdroj
			APName  - ID aktivniho prvku, jehoz vsechny vyskyty ze zdroje hSource chci ziskat
			Result  - ukazatel na retezec, kam se ulozi vystup (musi se ale naalokovat)
navratova hodnota:	TRUE - do Result ulozen vystup,  FALSE - chyba (zasuvka nepodporuje tentu AP)
*/

BOOL performFE (hSource_t hSource, const char* APName, BSTR* Result);


// ---------- getAPListFE
/*
funkce vrati volajicimu XML string (stejny format jako CString CFESock::getAPList())
s identifikatory vsech AP, ktere tato zasuvka podporuje
*/

BSTR getAPListFE();



///// funkce rozhrani pro praci se zdroji

// --- fNewSourceFE
/*
otevre dialog pro vyber noveho zdroje
po navratu z dialogu do retezce pPerzistID ulozi connection string noveho zdroje
novy zdroj otevre a vrati na nej handler nebo NULL (chyba)
*/

hSource_t fNewSourceFE (BSTR* pPerzistID);


// --- fOpenSourceFE
/*
dostane connection string (PerzistID)
otevre zdroj a vrati na nej handle nebo NULL (chyba)
*/
hSource_t fOpenSourceFE (BSTR PerzistID);


// --- fCloseSourceFE
/*
dostane otevreny handler na zdroj (hSource)
uzavre handler a vrati TRUE (uspech) nebo FALSE (chyba)
*/

BOOL fCloseSourceFE (hSource_t hSource);


























#endif    // _INTERFACE_FUNCTIONS_FE