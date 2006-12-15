// InsertElementTrace.cpp: implementation of the CInsertElementTrace class.
//
//////////////////////////////////////////////////////////////////////
/*
This file is part of LM Report Asistent.

Authors: Jan Dedek, Jan Kodym, Martin Chrz, Iva Bartunkova

LM Report Asistent is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

Foobar is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Foobar; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include "stdafx.h"
#include "ReportAsistent.h"
#include "InsertElementTrace.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CInsertElementTrace::CInsertElementTrace()
{
	Clear();
}

CInsertElementTrace::~CInsertElementTrace()
{

}

void CInsertElementTrace::FindTrace(CElementManager::elId_t elm_what, CElementManager::elId_t elm_where)
{
	Clear();

	CElementManager & OElementManager = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->ElementManager;

	ASSERT (elm_what > OElementManager.getFirstStaticElementID() ||
		elm_what < OElementManager.getLastElementId() ||
		elm_where > OElementManager.getFirstStaticElementID() ||
		elm_where < OElementManager.getLastElementId() );
	


	switch (elm_where)
	{
		case ELID_REPORT:
			switch (elm_what)
			{
				case ELID_TEXT:
				case ELID_ATTR_LINK:
					Inter1=ELID_CHAPTER;
					Inter2=ELID_PARAGRAPH;
					break;
				case ELID_CHAPTER:	
				case ELID_INCLUDE:
					break;
				case ELID_PARAGRAPH:						
				case ELID_ATTR_LINK_TABLE:
					Inter1=ELID_CHAPTER;
					break;
				default: //aktivni prvky
					if (elm_what >= OElementManager.getFirstActiveElementID() )
						Inter1=ELID_CHAPTER;
					break;
			}
			break;
		case ELID_TEXT:
		case ELID_ATTR_LINK:
			switch (elm_what)
			{
				case ELID_TEXT:
				case ELID_ATTR_LINK:
					Direction=IET_BEFORE;
					break;	
				case ELID_INCLUDE:
					Direction=IET_TOP;
					break;
				case ELID_CHAPTER:
				case ELID_PARAGRAPH:						
				case ELID_ATTR_LINK_TABLE:
					Direction=IET_UP;
					break;
				default: //aktivni prvky
					if (elm_what >= OElementManager.getFirstActiveElementID() )
						Direction=IET_UP;
					break;
			}
			break;

		case ELID_PARAGRAPH:
			switch (elm_what)
			{
				case ELID_TEXT:
				case ELID_ATTR_LINK:
					break;	
				case ELID_INCLUDE:
					Direction=IET_TOP;
					break;
				case ELID_CHAPTER:
				case ELID_PARAGRAPH:						
				case ELID_ATTR_LINK_TABLE:
					Direction=IET_BEFORE;
					break;
				default: //aktivni prvky
					if (elm_what >= OElementManager.getFirstActiveElementID() )
						Direction=IET_BEFORE;
					break;
			}
			break;			
		case ELID_CHAPTER:	
			switch (elm_what)
			{
				case ELID_TEXT:
				case ELID_ATTR_LINK:
					Inter1=ELID_PARAGRAPH;
					break;	
				case ELID_INCLUDE:
					Direction=IET_TOP;
					break;
				case ELID_CHAPTER:
				case ELID_PARAGRAPH:						
				case ELID_ATTR_LINK_TABLE:
					break;
				default: //aktivni prvky
					//if (elm_what >= OElementManager.getFirstActiveElementID() ) ;
					break;
			}
			break;			
		case ELID_INCLUDE:
			switch (elm_what)
			{
				case ELID_TEXT:
				case ELID_ATTR_LINK:
					Direction=IET_BEFORE;
					Inter1=ELID_CHAPTER;
					Inter2=ELID_PARAGRAPH;
					break;	
				case ELID_INCLUDE:
					Direction=IET_TOP;
					break;
				case ELID_CHAPTER:
					Direction=IET_BEFORE;
					break;
				case ELID_PARAGRAPH:						
				case ELID_ATTR_LINK_TABLE:
					Direction=IET_BEFORE;
					Inter1=ELID_CHAPTER;
					break;
				default: //aktivni prvky
					if (elm_what >= OElementManager.getFirstActiveElementID() )
					Direction=IET_BEFORE;
					Inter1=ELID_CHAPTER;
					break;
			}
			break;			


			case ELID_ATTR_LINK_TABLE:
				switch (elm_what)
				{
					case ELID_TEXT:
					case ELID_ATTR_LINK:
						Direction=IET_BEFORE;
						Inter1=ELID_PARAGRAPH;
						break;	
					case ELID_INCLUDE:
						Direction=IET_TOP;
						break;
					case ELID_CHAPTER:
					case ELID_PARAGRAPH:						
					case ELID_ATTR_LINK_TABLE:
						Direction=IET_BEFORE;
						break;
					default: //aktivni prvky
						if (elm_what >= OElementManager.getFirstActiveElementID() )
							Direction=IET_BEFORE;
						break;
				}
				break;			
			default:
				if (elm_where >= OElementManager.getFirstActiveElementID() )
				{
					switch (elm_what)
					{
						case ELID_TEXT:
						case ELID_ATTR_LINK:
							Direction=IET_BEFORE;
							Inter1=ELID_PARAGRAPH;
							break;	
						case ELID_INCLUDE:
							Direction=IET_TOP;
							break;
						case ELID_CHAPTER:
						case ELID_PARAGRAPH:						
						case ELID_ATTR_LINK_TABLE:
							Direction=IET_BEFORE;
							break;
						default: //aktivni prvky
							if (elm_what >= OElementManager.getFirstActiveElementID() )
								Direction=IET_BEFORE;
							break;
					}
				}
				break;


	}

}

void CInsertElementTrace::Clear()
{

	Inter1=ELID_UNKNOWN; //==0
	Inter2=ELID_UNKNOWN;
	Direction = IET_IN;

}
