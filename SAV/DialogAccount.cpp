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

	BindInfoList();

	

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE

	
}

void CDialogAccount::BindInfoList()
{
	//Bind List Control
	LONG styles;
	styles = m_listAct.GetExtendedStyle();
	//LVS_EX_FULLROWSELECT整行选中
	//LVS_EX_GRIDLINES加网格线
	//LVS_EX_CHECKBOXES前面加复选框
	m_listAct.SetExtendedStyle(styles | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	LV_COLUMN lvcol;
	lvcol.mask = LVCF_WIDTH | LVCF_TEXT | LVCF_FMT | LVCF_SUBITEM;
	lvcol.fmt = LVCFMT_LEFT;
	lvcol.cx = 70;
	lvcol.iSubItem = 0;
	lvcol.pszText = L"帐号";
	m_listAct.InsertColumn(0, &lvcol);
	lvcol.cx = 40;
	lvcol.iSubItem = 0;
	lvcol.pszText = L"密码";
	m_listAct.InsertColumn(1, &lvcol);
	lvcol.cx = 30;
	lvcol.iSubItem = 0;
	lvcol.pszText = L"安全码";
	m_listAct.InsertColumn(2, &lvcol);
	lvcol.cx = 40;
	lvcol.iSubItem = 0;
	lvcol.pszText = L"人物";
	m_listAct.InsertColumn(3, &lvcol);
	lvcol.cx = 80;
	lvcol.iSubItem = 0;
	lvcol.pszText = L"脚本";
	m_listAct.InsertColumn(4, &lvcol);
	lvcol.cx = 80;
	lvcol.iSubItem = 0;
	lvcol.pszText = L"配置文件";
	m_listAct.InsertColumn(5, &lvcol);
	lvcol.cx = 70;
	lvcol.iSubItem = 0;
	lvcol.pszText = L"登入线路";
	m_listAct.InsertColumn(6, &lvcol);
	lvcol.cx = 70;
	lvcol.iSubItem = 0;
	lvcol.pszText = L"所属队伍";
	m_listAct.InsertColumn(7, &lvcol);
	lvcol.cx = 70;
	lvcol.iSubItem = 0;
	lvcol.pszText = L"成员类型";
	m_listAct.InsertColumn(8, &lvcol);
	lvcol.cx = 70;
	lvcol.iSubItem = 0;
	lvcol.pszText = L"登入状态";
	m_listAct.InsertColumn(9, &lvcol);

	//Load account into the List control
	int nRow, pos, i = 0;
	try{
		CString szAccount, szPwd, szSafeCode, szchar, szScript, szSetting, szLine, szTeam, szTeammate, szStatus;
		CString szVal;
		
		CStdioFile f(_T("data.txt"), CFile::modeRead | CFile::typeText);
		while (f.ReadString(szVal)){
			i++;
			pos = szVal.Find(_T("\r"));
			if (pos>0)
				szVal = szVal.Left(pos);
			else{
				pos = szVal.Find(_T("\n"));
				if (pos>0)
					szVal = szVal.Left(pos);
			}
			//if(pos>0){
			pos = 0;
			szAccount = szVal.Tokenize(L"|", pos);
			szPwd = szVal.Tokenize(L"|", pos);
			szSafeCode = szVal.Tokenize(L"|", pos);
			szchar = szVal.Tokenize(L"|", pos);
			szScript = szVal.Tokenize(L"|", pos);
			szSetting = szVal.Tokenize(L"|", pos);
			szLine = szVal.Tokenize(L"|", pos);
			szTeam = szVal.Tokenize(L"|", pos);
			szTeammate = szVal.Tokenize(L"|", pos);

			nRow = m_listAct.InsertItem(m_listAct.GetItemCount(), szAccount);
			m_listAct.SetItemText(nRow, 1, szPwd);
			m_listAct.SetItemText(nRow, 2, szSafeCode);
			m_listAct.SetItemText(nRow, 3, szchar);
			m_listAct.SetItemText(nRow, 4, szScript);
			m_listAct.SetItemText(nRow, 5, szSetting);
			m_listAct.SetItemText(nRow, 6, szLine);
			m_listAct.SetItemText(nRow, 7, szTeam);
			m_listAct.SetItemText(nRow, 8, szTeammate);
			//}
		}
		f.Close();
	}
	catch (...){
	}
}

void CDialogAccount::GetAccountList()
{
	int pos = 0;
	m_listAct.GetFirstSelectedItemPosition();
	if (pos < 0)
	{
		MessageBox(L"请先选中要操作的帐号！", L"提示信息", MB_OK | MB_ICONINFORMATION);
		return;
	}
	else
	{
		MessageBox(L"A");

	}
}