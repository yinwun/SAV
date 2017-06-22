#pragma once


// CDialogAccount dialog

class CDialogAccount : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogAccount)

public:
	CDialogAccount(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDialogAccount();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DlgAccount };
#endif

	CListCtrl m_listAct;
	

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
