// Funkce pro vyrizeni pozadavku na AP v zasuvce pro LM
// functions.h

#ifndef _FUNCTIONS
#define _FUNCTIONS

#ifndef WINVER
#define WINVER 0x0400

#ifndef HYPOTHESIS_LIMIT
#define HYPOTHESIS_LIMIT 10000
#endif

#endif

// ===== INCLUDE =======

#include <afx.h>

// ===== FUNKCE ========

// ---AP Task

CString fLMTask (void* hSource);

// ---AP KL cedent

CString fLMKLCedent (void* hSource);

// ---AP CF cedent

CString fLMCFCedent (void* hSource);

// ---AP bool cedent

CString fLMBoolCedent (void* hSource);

// ---AP attribute

CString fLMAttribute(void* hSource);

// --- AP category

CString fLMCategory(void* hSource);


// --- AP 4ft-hypothesis

CString fLM4fthyp(void* hSource);



#endif /* _FUNCTIONS*/