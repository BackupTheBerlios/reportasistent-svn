#pragma once

#ifndef _FEplugin
#define _FEplugin


#include <afx.h>
#include <Windows.h>
//#include <afxdisp.h>
#include "SockInterface.h"
#include "functions.h"





// !!! zde definujte pocet AP, ktere tato zasuvka podporuje
#define _FE_AP_COUNT 13


// =========== TYPY ===============================

typedef CString (* pFn_t) (void*);
  // ukazatel na funkci, ktera vyridi pozadavek na AP urciteho typu



// =========== TRIDY ==============================

// ------------ class CFESock
/*
tato trida vytvori a spravuje v zasuvce pro FE tabulku podporovanych AP a funkci, ktere je vyrizuji
poskytuje:
- pocet AP, ktere zasuvka podporuje
- seznam vsech AP, ktere zasuvka podporuje
- funkci perform() : adresu funkce, ktera vyrizuje zadost o AP s danym ID
*/

class CFESock {

// TYPY

  typedef struct Item_t {	// polozka tabulky nazvu podporovanych AP a ukazatelu na funkce, ktere je obslouzi
	  CString AP_ID;	// ID aktivniho prvku
	  pFn_t   pFn;		// uk. na funkci ktera ho obslouzi
  };

// DATA

  int APCount;	// pocet AP, ktere zasuvka podporuje

  Item_t APTable[_FE_AP_COUNT];	// tabulka AP a funkci

// METODY

  pFn_t getFnAddress(CString APName);	// vrati adresu funkce obsluhujici AP s AP_ID=APName nebo NULL (neexistuje-li)

public:
  
  CFESock();	// konstruktor
  
  CString getAPList();	// vrati seznam vsech identifikatoru AP, ktere zasuvka podporuje

// FRIENDS

  friend BOOL performFE (void* hSource, const char* APName, BSTR* Result); // funkce perform zasuvky pro FE
};





// =========== GLOBALNI PROMENNE ==================


extern CFESock FESock;
extern CSockInterface SockInterfaceFE;  // rozhrani zasuvky





/////////////////////////////////////////
/////// initSock
// inicializuje globalni instanci SockInterface a vrati volajicimu (jadru) pointer na ni

//__declspec(dllexport)
CSockInterface* initSock();





#endif	// _FEplugin