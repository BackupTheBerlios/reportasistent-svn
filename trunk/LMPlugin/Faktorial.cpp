
// implementace definic pro faktorial
//
/////////////////////////////////////////////////////////////////////////////
#include "Faktorial.h"

#include "math.h"

// Pomocne definice

CLnFaktTab gLnFaktTab;

// Pro externi pouziti

/////////////////////////////////////////////////////////////////////////////
// CLnFaktTab

// Construction & Destruction

CLnFaktTab::CLnFaktTab()
{
	m_n= 0;
	//m_LnFaktTab= NULL;
}

CLnFaktTab::~CLnFaktTab()
{
	Dealloc();
}

bool CLnFaktTab::Init( long n)
// Vytvori tabulku logaritmu faktorialu od 0 do n
// Pri nedostatku pameti vraci FALSE
{
	if ( !m_LnFaktTab ||
		 n > m_n)
	{
		Dealloc();

		m_LnFaktTab= new FAKTVALUE[n+ 1];
		if ( !m_LnFaktTab) return false;

		m_n= n;

		m_LnFaktTab[0]= 0;

		long i;

		for (i= 1; i <= n; i++) m_LnFaktTab[i]= m_LnFaktTab[i-1]+ log((double) i);
			// ln( n!) == ln(1)+ ln(2)+ ...+ ln(n)
			// ln( n!) == ln((n-1)!)+ ln( n)
	}

	return true;
}

void CLnFaktTab::Dealloc()
// Provede uvolneni pameti po tabulce
{
	if ( m_LnFaktTab)
	{
		delete[] m_LnFaktTab;
		//m_LnFaktTab= NULL;
	}
}
