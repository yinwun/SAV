// Dialog_CharInfo.cpp : implementation file
//

#include "stdafx.h"
#include "SAV.h"
#include "DialogCharInfo.h"
#include "afxdialogex.h"


// CDialog_CharInfo dialog

IMPLEMENT_DYNAMIC(CDialogCharInfo, CDialogEx)

CDialogCharInfo::CDialogCharInfo(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DlgCharInfo, pParent)
{

}

CDialogCharInfo::~CDialogCharInfo()
{
}

void CDialogCharInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialogCharInfo, CDialogEx)
END_MESSAGE_MAP()


// CDialog_CharInfo message handlers
