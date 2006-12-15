
// Definice pro zrychleni vypoctu faktorialu
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _FAKTORIAL_H_
#define _FAKTORIAL_H_

// Zde definovano
/**
 * This class was designed to store the logarithms of the factorials.
 *
 * @author Milan Simunek
 */
class CLnFaktTab;

// Include definic potrebnych v teto hlavicce

// Pro externi pouziti

extern CLnFaktTab gLnFaktTab;

// Pomocne definice

/**
 * target type of logarithm of the factorial
 */
typedef double		FAKTVALUE;
/**
 * pointer to the target type of logarithm of the factorial (table of values)
 */
typedef FAKTVALUE*	LNFAKTTAB;

/////////////////////////////////////////////////////////////////////////////
// 
// CLnFaktTab
//
// Tabulka logaritmu faktorialu
//

// Zde definovano
/**
 * This class was designed to store the logarithms of the factorials.
 *
 * @author Milan Simunek
 */
class CLnFaktTab
{
public:
	CLnFaktTab();

	/**
 * Creates the table of the logarithms of the factorial from 0 to n.
 *
 * @param n 
 * @return Returns true, if the table was created, otherwise returns false.
 */
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

	/**
 * Returns the logarithm of the i-th factorial
 *
 * @param i 
 * @return double 
 */
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

	void Dealloc();/// releases the memory allocated for the table of logarithms of factorials, called from destructor
		// Provede uvolneni pameti po tabulce
};

/////////////////////////////////////////////////////////////////////////////

#endif
