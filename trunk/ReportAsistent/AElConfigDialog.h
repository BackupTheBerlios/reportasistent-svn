#pragma once


// CAElConfigDialog dialog

class CAElConfigDialog : public CPropertyPage
{
	DECLARE_DYNAMIC(CAElConfigDialog)

private:
	MSXML2::IXMLDOMElementPtr & m_active_element;
	MSXML2::IXMLDOMElementPtr & m_cloned_active_element;

public:
	CAElConfigDialog(MSXML2::IXMLDOMElementPtr & active_element, MSXML2::IXMLDOMElementPtr & cloned_element);
	virtual ~CAElConfigDialog();

// Dialog Data
	enum { IDD = IDD_AEL_CONFIG_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
