#pragma once


// CDialog_CharInfo dialog

class CDialogCharInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogCharInfo)

public:
	CDialogCharInfo(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDialogCharInfo();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DlgCharInfo };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
