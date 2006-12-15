// InsertElementTrace.h: interface for the CInsertElementTrace class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INSERTELEMENTTRACE_H__784B21D5_633F_4797_8900_CBBC0A3D542D__INCLUDED_)
#define AFX_INSERTELEMENTTRACE_H__784B21D5_633F_4797_8900_CBBC0A3D542D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define IET_IN 1
#define IET_BEFORE 2
#define IET_UP 3
#define IET_TOP 4

/** Class CInsertElementTrace reprezents a route of enclosing elements that must be created to hold the target element, that a user wants to create.
*/

/**
 * class CInsertElementTrace:
 *
 * @author 
 */
class CInsertElementTrace  
{
public:
	CElementManager::elId_t Inter1;
	CElementManager::elId_t Inter2;
	int Direction;
	CInsertElementTrace();
	virtual ~CInsertElementTrace();
	void FindTrace(CElementManager::elId_t elm_what, CElementManager::elId_t elm_where);
protected:
	void Clear();
};

#endif // !defined(AFX_INSERTELEMENTTRACE_H__784B21D5_633F_4797_8900_CBBC0A3D542D__INCLUDED_)
