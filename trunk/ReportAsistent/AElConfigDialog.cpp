// AElConfigDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ReportAsistent.h"
#include "AElConfigDialog.h"


// CAElConfigDialog dialog

IMPLEMENT_DYNAMIC(CAElConfigDialog, CPropertyPage)

CAElConfigDialog::CAElConfigDialog(MSXML2::IXMLDOMElementPtr & active_element, MSXML2::IXMLDOMElementPtr & cloned_element)
	: CPropertyPage(CAElConfigDialog::IDD)
	, m_active_element(active_element)
	, m_cloned_active_element(cloned_element)
{

}

CAElConfigDialog::~CAElConfigDialog()
{
}

void CAElConfigDialog::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAElConfigDialog, CPropertyPage)
END_MESSAGE_MAP()


// CAElConfigDialog message handlers
