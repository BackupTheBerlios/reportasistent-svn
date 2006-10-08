
// Definice pro zrychleni vypoctu faktorialu
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _FAKTORIAL_H_
#define _FAKTORIAL_H_

// Zde definovano

class CLnFaktTab;

// Include definic potrebnych v teto hlavicce

// Pro externi pouziti

extern CLnFaktTab gLnFaktTab;

// Pomocne definice

typedef double		FAKTVALUE;
typedef FAKTVALUE*	LNFAKTTAB;

/////////////////////////////////////////////////////////////////////////////
// 
// CLnFaktTab
//
// Tabulka logaritmu faktorialu
//

class CLnFaktTab
{
public:
	CLnFaktTab();

	bool Init( long n);
		// Vytvori tabulku logaritmu faktorialu od 0 do n
		// Pri nedostatku pameti vraci FALSE

// Attributes
protected:
	long		m_n;
	LNFAKTTAB   m_LnFaktTab;

// Operations
public:

// Interface
public:

	double  GetLnFakt( long i) {
		// Vrati logaritmus faktorialu
		//ASSERT( m_LnFaktTab != NULL);
		//ASSERT( i <= m_n); 
		return m_LnFaktTab[i];
	}

	long n() {return m_n;}

// Implementation
public:
	virtual ~CLnFaktTab();

protected:

	void Dealloc();
		// Provede uvolneni pameti po tabulce
};

/////////////////////////////////////////////////////////////////////////////

#endif
