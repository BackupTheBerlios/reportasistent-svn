// InsertElementTrace.cpp: implementation of the CInsertElementTrace class.
//
//////////////////////////////////////////////////////////////////////

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
