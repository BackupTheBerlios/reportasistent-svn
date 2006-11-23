#pragma once

#ifndef _FEplugin
#define _FEplugin


#include <afx.h>
#include <Windows.h>
//#include <afxdisp.h>
#include "SockInterface.h"
#include "functions.h"





// !!! here define number of active elements supported by plugin !!!!!

#define _FE_AP_COUNT 16


// =========== TYPES ===============================
/**
*Pointer to function which evaluates a query about active element with given type
*@see CFESock#Item_t 
*/
typedef CString (* pFn_t) (void*);
 



// =========== CLASSES ==============================

// ------------ class CFESock

/**
*This class creates and manages in FEplugin a table of supported active elements and functions, which evaluates a queries about active elements
*it offers:
*<ul>
*	<li>number of active elements supported by FEplugin</li>
*	<li>list of active elements supported by FEplugin</li>
*	<li>function perform() : adress of function, which evaluates queries about active elements with given ID</li>
*</ul>
*/
class CFESock {

// TYPES
/**
*Item of table of supported active elements names and pointers to functions, which evaluates queries about them
*/
  typedef struct Item_t
  {	

	  CString AP_ID;  /// ID of active element

	  pFn_t   pFn; /// Pointer to function which resolves a query about given active element
  };

// DATA

  int APCount; ///Number of active elements supported by FEplugin

  Item_t APTable[_FE_AP_COUNT];	 ///Table of active elements and functions

// METHODS

  /**
  *Returns address of function (evaluating active element with ID=APName) or NULL (if it does not exist)
  *@return Address of function (evaluating active element with ID=APName) or NULL (if it does not exist)
  *@param APName ID of active element
  */
  pFn_t getFnAddress(CString APName);	

public:
  
  CFESock();
  
  /**
  *Returns a list of identifiers of all active element IDs supported by FEplugin.
  *@return XML string with list of active element IDs
  */
  CString getAPList();

// FRIENDS

  friend BOOL performFE (void* hSource, const char* APName, BSTR* Result); // "perform" function of FEplugin
};





// =========== GLOBAL VARIABLES ==================


extern CFESock FESock; 
extern CSockInterface SockInterfaceFE;  





/////////////////////////////////////////
/////// initSock

/**
*
*Initializes a global instance of SockInterface, is called by LM-Report Asistent kernell
*<br>
*Each plugin MUST contain an initialization function 
*<code>
*  CSockInterface* initSock()
*</code>
*
*which creates and initializes an instance of CSockInterface structure. This function must be accessible for LM-RA kernell
*(exported from DLL)
*While start of LM-Report Asistent, kernell connects plugins by calling initSock() in each DLL found in "Plugin" directory.
*If initSock() is not found, plugin is signed as invalid
*
*@see CSockInterface CSockInterface 
*@return pointer to initialized CSockInterface structure
*/
CSockInterface* initSock();





#endif	// _FEplugin