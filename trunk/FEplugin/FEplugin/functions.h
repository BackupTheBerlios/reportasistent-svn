// Funkce pro vyrizeni pozadavku na AP v zasuvce pro Ferdu
// functions.h

#ifndef _FUNCTIONS_FE
#define _FUNCTIONS_FE

// ===== INCLUDE =======

#include <afx.h>

// ===== FUNKCE ========


// --- AP Kategorie

CString fFECategory(void* hSource);


// --- AP 4ft-hypoteza

CString fFE4fthyp(void* hSource);

// --- AP Atribut

CString fFEAttribute(void* hSource);

// --- AP Boolsky cedent

CString fFEBool_cedent(void* hSource);




#endif /* _FUNCTIONS*/