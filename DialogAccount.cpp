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


	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE

	
}

void CDialogAccount::OnSinglelogin()
{
	UpdateData(TRUE);
		
}

