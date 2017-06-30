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
	ON_BN_CLICKED(IDC_btnActLogin, &CDialogAccount::OnBnClickedbtnactlogin)
END_MESSAGE_MAP()


// CDialogAccount message handlers


BOOL CDialogAccount::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here

	//BindInfoList();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}



void CDialogAccount::OnSinglelogin()
{
	int pos = 0;
	pos = (int)m_listAct.GetFirstSelectedItemPosition() - 1;
	if (pos < 0)
	{
		MessageBox(L"请先选中要操作的帐号！", L"提示信息", MB_OK | MB_ICONINFORMATION);
		return;
	}
	else
	{

		MessageBox(L"AAAAAA！", L"提示信息", MB_OK | MB_ICONINFORMATION);
		return;
	}

}



void CDialogAccount::OnBnClickedbtnactlogin()
{
	// TODO: Add your control notification handler code here
	int pos = 0;
	pos = (int)m_listAct.GetFirstSelectedItemPosition() - 1;
	if (pos < 0)
	{
		MessageBox(L"请先选中要操作的帐号！", L"提示信息", MB_OK | MB_ICONINFORMATION);
		return;
	}
	else
	{
		

	}
}

