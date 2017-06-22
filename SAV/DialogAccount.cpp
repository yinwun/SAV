// DialogAccount.cpp : implementation file
//

#include "stdafx.h"
#include "SAV.h"
#include "DialogAccount.h"
#include "afxdialogex.h"


// CDialogAccount dialog

IMPLEMENT_DYNAMIC(CDialogAccount, CDialogEx)

CDialogAccount::CDialogAccount(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DlgAccount, pParent)
{
	//CRect rs;
	//CDialog *p = (CDialog*)GetDlgItem(IDD_DlgAccount);
	//p->GetClientRect(&rs);

	////rs.top += 22;
	////rs.bottom -= 1;
	////rs.left += 1;
	////rs.right -= 1;

	//CListCtrl *pa = (CListCtrl*)GetDlgItem(IDC_LstAccount);
	//pa->MoveWindow(&rs);
}

CDialogAccount::~CDialogAccount()
{
	 
}

void CDialogAccount::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LstAccount, m_listAct);
	
}


BEGIN_MESSAGE_MAP(CDialogAccount, CDialogEx)
END_MESSAGE_MAP()


// CDialogAccount message handlers


BOOL CDialogAccount::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here

	LV_COLUMN lvcol;
	lvcol.mask = LVCF_WIDTH | LVCF_TEXT | LVCF_FMT | LVCF_SUBITEM;
	lvcol.fmt = LVCFMT_LEFT;
	lvcol.cx = 70;
	lvcol.iSubItem = 0;
	lvcol.pszText = "»ÀŒÔ";
	m_listAct.InsertColumn(0, &lvcol);

	

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE

	
}
