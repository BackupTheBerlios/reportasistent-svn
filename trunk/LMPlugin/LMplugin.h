
#ifndef _LMplugin
#define _LMplugin


#include <afx.h>
#include <afxdisp.h>
#include "SockInterface.h"
#include "functions.h"

// !!! zde definujte pocet AP, ktere tato zasuvka podporuje
#define _LM_AP_COUNT 2


// =========== TYPY ===============================

typedef CString (* pFn_t) (void*);
  // ukazatel na funkci, ktera vyridi pozadavek na AP urciteho typu



// =========== TRIDY ==============================

// ------------ class CLMSock
/*
tato trida vytvori a spravuje v zasuvce pro LM tabulku podporovanych AP a funkci, ktere je vyrizuji
poskytuje:
- pocet AP, ktere zasuvka podporuje
- seznam vsech AP, ktere zasuvka podporuje
- funkci perform() : adresu funkce, ktera vyrizuje zadost o AP s danym ID
*/

class CLMSock {

// TYPY

  typedef struct Item_t {	// polozka tabulky nazvu podporovanych AP a ukazatelu na funkce, ktere je obslouzi
	  CString AP_ID;	// ID aktivniho prvku
	  pFn_t   pFn;		// uk. na funkci ktera ho obslouzi
  };

// DATA

  int APCount;	// pocet AP, ktere zasuvka podporuje

  Item_t APTable[_LM_AP_COUNT];	// tabulka AP a funkci

// METODY

  pFn_t getFnAddress(CString APName);	// vrati adresu funkce obsluhujici AP s AP_ID=APName nebo NULL (neexistuje-li)

public:
  
  CLMSock();	// konstruktor
  
  CString getAPList();	// vrati seznam vsech identifikatoru AP, ktere zasuvka podporuje

// FRIENDS

  friend BOOL performLM (void* hSource, const char* APName, BSTR* Result); // funkce perform zasuvky pro LM
};


// =========== GLOBALNI PROMENNE ==================


extern CLMSock LMSock;
extern CSockInterface SockInterfaceLM;  // rozhrani zasuvky





/////////////////////////////////////////
/////// initSock
// inicializuje globalni instanci SockInterface a vrati volajicimu (jadru) pointer na ni

CSockInterface* initSock();



#endif	// _LMplugin