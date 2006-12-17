//Faktorial.cpp
/*
This file is part of LM Report Asistent.

Author: Milan Simunek

LM Report Asistent is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

LM Report Asistent is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with LM Report Asistent; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
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
