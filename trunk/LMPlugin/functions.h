// Funkce pro vyrizeni pozadavku na AP v zasuvce pro LM
// functions.h

#ifndef _FUNCTIONS
#define _FUNCTIONS

// ===== INCLUDE =======

#include <afx.h>

// ===== FUNKCE ========

// ---AP cedent

CString fLMCedent (void* hSource);

// ---AP attribute

CString fLMAttribute(void* hSource);

// --- AP category

CString fLMCategory(void* hSource);


// --- AP 4ft-hypothesis

CString fLM4fthyp(void* hSource);



#endif /* _FUNCTIONS*/