// DialogAccount.cpp : implementation file
//

#include "stdafx.h"
#include "SAV.h"
#include "DialogAccount.h"
#include "afxdialogex.h"



USERINFO *g_userinfo = NULL;
int g_userNum = 0;
SALib *pDp = NULL;
long gametime; // Timer seed
CALLBACK_Func f_Callback = NULL;
WPARAM f_Param = NULL;

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

	BindInfoList();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialogAccount::BindInfoList()
{
	//Bind List Control
	LONG styles;
	styles = m_listAct.GetExtendedStyle();
	//LVS_EX_FULLROWSELECT����ѡ��
	//LVS_EX_GRIDLINES��������
	//LVS_EX_CHECKBOXESǰ��Ӹ�ѡ��
	m_listAct.SetExtendedStyle(styles | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	LV_COLUMN lvcol;
	lvcol.mask = LVCF_WIDTH | LVCF_TEXT | LVCF_FMT | LVCF_SUBITEM;
	lvcol.fmt = LVCFMT_LEFT;
	lvcol.cx = 70;
	lvcol.iSubItem = 0;
	lvcol.pszText = L"�ʺ�";
	m_listAct.InsertColumn(0, &lvcol);
	lvcol.cx = 40;
	lvcol.iSubItem = 0;
	lvcol.pszText = L"����";
	m_listAct.InsertColumn(1, &lvcol);
	lvcol.cx = 30;
	lvcol.iSubItem = 0;
	lvcol.pszText = L"��ȫ��";
	m_listAct.InsertColumn(2, &lvcol);
	lvcol.cx = 40;
	lvcol.iSubItem = 0;
	lvcol.pszText = L"����";
	m_listAct.InsertColumn(3, &lvcol);
	lvcol.cx = 80;
	lvcol.iSubItem = 0;
	lvcol.pszText = L"�ű�";
	m_listAct.InsertColumn(4, &lvcol);
	lvcol.cx = 80;
	lvcol.iSubItem = 0;
	lvcol.pszText = L"�����ļ�";
	m_listAct.InsertColumn(5, &lvcol);
	lvcol.cx = 70;
	lvcol.iSubItem = 0;
	lvcol.pszText = L"������·";
	m_listAct.InsertColumn(6, &lvcol);
	lvcol.cx = 70;
	lvcol.iSubItem = 0;
	lvcol.pszText = L"��������";
	m_listAct.InsertColumn(7, &lvcol);
	lvcol.cx = 70;
	lvcol.iSubItem = 0;
	lvcol.pszText = L"��Ա����";
	m_listAct.InsertColumn(8, &lvcol);
	lvcol.cx = 70;
	lvcol.iSubItem = 0;
	lvcol.pszText = L"����״̬";
	m_listAct.InsertColumn(9, &lvcol);
	lvcol.cx = 0;
	lvcol.iSubItem = 0;
	lvcol.pszText = L"������IP";
	m_listAct.InsertColumn(10, &lvcol);
	lvcol.cx = 0;
	lvcol.iSubItem = 0;
	lvcol.pszText = L"�������˿�";
	m_listAct.InsertColumn(11, &lvcol);

	//Load account into the List control
	CString szAccount, szPwd, szSafeCode, szchar, szScript, szSetting, szLine, szTeam, szTeammate, szStatus, szServer, szPort;
	CString szVal;
	int nRow, pos, i = 0;
	try{
		CStdioFile f(_T("data.txt"), CFile::modeRead | CFile::typeText);
		while (f.ReadString(szVal)){
			i++;
			pos = szVal.Find(_T("\r"));
			if (pos > 0)
				szVal = szVal.Left(pos);
			else{
				pos = szVal.Find(_T("\n"));
				if (pos > 0)
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
			szServer = szVal.Tokenize(L"|", pos);
			szPort = szVal.Tokenize(L"|", pos);

			nRow = m_listAct.InsertItem(m_listAct.GetItemCount(), szAccount);
			m_listAct.SetItemText(nRow, 1, szPwd);
			m_listAct.SetItemText(nRow, 2, szSafeCode);
			m_listAct.SetItemText(nRow, 3, szchar);
			m_listAct.SetItemText(nRow, 4, szScript);
			m_listAct.SetItemText(nRow, 5, szSetting);
			m_listAct.SetItemText(nRow, 6, szLine);
			m_listAct.SetItemText(nRow, 7, szTeam);
			m_listAct.SetItemText(nRow, 8, szTeammate);
			m_listAct.SetItemText(nRow, 10, szServer);
			m_listAct.SetItemText(nRow, 11, szPort);
			//}
		}

		f.Close();
	}
	catch (...){
	}

	//�ʺŴ���
	g_userNum = m_listAct.GetItemCount();
	if (g_userNum > 0)
	{
		g_userinfo = new USERINFO[g_userNum];
		for (int i = 0; i < g_userNum; i++){
			szAccount = m_listAct.GetItemText(i, 0);
			szPwd = m_listAct.GetItemText(i, 1);
			szSafeCode = m_listAct.GetItemText(i, 2);
			szScript = m_listAct.GetItemText(i, 4);
			szLine = m_listAct.GetItemText(i, 6);

			memcpy(g_userinfo[i].charname, szAccount, szAccount.GetLength());
			memcpy(g_userinfo[i].password, szPwd, szPwd.GetLength());
			memcpy(g_userinfo[i].safecode, szSafeCode, szSafeCode.GetLength());
			memcpy(g_userinfo[i].scriptName, szScript, szScript.GetLength());
			memcpy(g_userinfo[i].servername, szServer, szServer.GetLength());
			g_userinfo[i].port = _ttoi((LPTSTR)(LPCTSTR)szPort);

			g_userinfo[i].index = i;

		}
		pDp = new SALib[g_userNum];
	}
	else
	{
		g_userinfo = NULL;
	}
	gametime = 0;
	
	
	Set_Callback(Callback_func, WPARAM(this));
	/*
	GetDlgItem(IDC_STOP)->EnableWindow(FALSE);
	GetDlgItem(IDC_START)->EnableWindow(TRUE);*/
}


void CDialogAccount::OnSinglelogin()
{
	UpdateData(TRUE);



}



void CDialogAccount::OnBnClickedbtnactlogin()
{
	// TODO: Add your control notification handler code here
	int pos = 0;
	pos = (int)m_listAct.GetFirstSelectedItemPosition() - 1;
	if (pos < 0)
	{
		MessageBox(L"����ѡ��Ҫ�������ʺţ�", L"��ʾ��Ϣ", MB_OK | MB_ICONINFORMATION);
		return;
	}
	else
	{
		

	}
}

void CDialogAccount::CallbackMsg(NOTIFYPARA *pNotifyPara)
{
	/*
	CString szVal, szTemp, szStr, szName, szError;
	int i, n, nRow, pos;
	CTime cTime = CTime::GetCurrentTime();
	if (m_message.GetCount()>500)
		m_message.ResetContent();
	switch (pNotifyPara->nNotityType){
	case NOTIFY_TIME:
		if (!TimerOn)
			TimerOn = SetTimer(1, 1000, NULL);
		break;
	case NOTIFY_MSG:
		szVal.Format("%s %s", cTime.Format(_T("%H:%M:%S")), (LPCTSTR)pNotifyPara->lpNotifyData);
		m_message.AddString(szVal);
		m_message.SendMessage(WM_VSCROLL, SB_BOTTOM, 0);
		break;
	case NOTIFY_LOGIN:
		szVal = (LPCTSTR)pNotifyPara->lpNotifyData;
		pos = 0;
		//ȡ�ʺ�
		szName = szVal.Tokenize("|", pos);
		n = m_charinfo.GetItemCount();
		//ȡ������
		szTemp = szVal.Tokenize("|", pos);
		//ָ���ʺ��Ƿ����б����
		for (i = 0; i<n; i++){
			szStr = m_charinfo.GetItemText(i, 0);
			if (szStr == szTemp)
				break;
		}
		if (i >= n){
			nRow = m_charinfo.InsertItem(n, szTemp);
			szTemp = szVal.Tokenize("|", pos);
			m_charinfo.SetItemText(nRow, 1, szTemp);
			szTemp = szVal.Tokenize("|", pos);
			m_charinfo.SetItemText(nRow, 2, szTemp);
			szTemp = szVal.Tokenize("|", pos);
			m_charinfo.SetItemText(nRow, 3, szTemp);
			szTemp = szVal.Tokenize("|", pos);
			m_charinfo.SetItemText(nRow, 4, szTemp);
			szTemp = szVal.Tokenize("|", pos);
			m_charinfo.SetItemText(nRow, 5, szTemp);
			szTemp = szVal.Tokenize("|", pos);
			m_charinfo.SetItemText(nRow, 6, szTemp);
			szTemp = szVal.Tokenize("|", pos);
			m_charinfo.SetItemText(nRow, 7, szTemp);
			szTemp = szVal.Tokenize("|", pos);
			m_charinfo.SetItemText(nRow, 8, szTemp);
			szTemp = szVal.Tokenize("|", pos);
			m_charinfo.SetItemText(nRow, 9, szTemp);
			szTemp = szVal.Tokenize("|", pos);
			m_charinfo.SetItemText(nRow, 10, szTemp);
			szTemp = szVal.Tokenize("|", pos);
			m_charinfo.SetItemText(nRow, 11, szTemp);
			szTemp = szVal.Tokenize("|", pos);
			m_charinfo.SetItemText(nRow, 12, szTemp);
			szTemp = szVal.Tokenize("|", pos);
			m_charinfo.SetItemText(nRow, 13, szTemp);
			szTemp = szVal.Tokenize("|", pos);
			m_charinfo.SetItemText(nRow, 14, szTemp);
			szTemp = szVal.Tokenize("|", pos);
			m_charinfo.SetItemText(nRow, 15, szTemp);
			szTemp = szVal.Tokenize("|", pos);
			m_charinfo.SetItemText(nRow, 16, szTemp);
			szTemp = szVal.Tokenize("|", pos);
			m_charinfo.SetItemText(nRow, 17, szTemp);
			szTemp = szVal.Tokenize("|", pos);
			m_charinfo.SetItemText(nRow, 19, szTemp);
			szTemp = szVal.Tokenize("|", pos);
			m_charinfo.SetItemText(nRow, 20, szTemp);
			szTemp = szVal.Tokenize("|", pos);
			if (!szTemp.Trim().IsEmpty())
				m_charinfo.SetItemText(nRow, 21, szTemp);
			szTemp = szVal.Tokenize("|", pos);
			m_charinfo.SetItemText(nRow, 22, szTemp);
			szTemp = szVal.Tokenize("|", pos);
			m_charinfo.SetItemText(nRow, 23, szTemp);
			szVal.Format("%s %s�ʺ��ѵ��룡", cTime.Format(_T("%H:%M:%S")), szName);
			m_message.AddString(szVal);
			m_message.SendMessage(WM_VSCROLL, SB_BOTTOM, 0);
		}
		else{
			nRow = i;
			szTemp = szVal.Tokenize("|", pos);
			m_charinfo.SetItemText(nRow, 1, szTemp);
			szTemp = szVal.Tokenize("|", pos);
			m_charinfo.SetItemText(nRow, 2, szTemp);
			szTemp = szVal.Tokenize("|", pos);
			m_charinfo.SetItemText(nRow, 3, szTemp);
			szTemp = szVal.Tokenize("|", pos);
			m_charinfo.SetItemText(nRow, 4, szTemp);
			szTemp = szVal.Tokenize("|", pos);
			m_charinfo.SetItemText(nRow, 5, szTemp);
			szTemp = szVal.Tokenize("|", pos);
			m_charinfo.SetItemText(nRow, 6, szTemp);
			szTemp = szVal.Tokenize("|", pos);
			m_charinfo.SetItemText(nRow, 7, szTemp);
			szTemp = szVal.Tokenize("|", pos);
			m_charinfo.SetItemText(nRow, 8, szTemp);
			szTemp = szVal.Tokenize("|", pos);
			m_charinfo.SetItemText(nRow, 9, szTemp);
			szTemp = szVal.Tokenize("|", pos);
			m_charinfo.SetItemText(nRow, 10, szTemp);
			szTemp = szVal.Tokenize("|", pos);
			m_charinfo.SetItemText(nRow, 11, szTemp);
			szTemp = szVal.Tokenize("|", pos);
			m_charinfo.SetItemText(nRow, 12, szTemp);
			szTemp = szVal.Tokenize("|", pos);
			m_charinfo.SetItemText(nRow, 13, szTemp);
			szTemp = szVal.Tokenize("|", pos);
			m_charinfo.SetItemText(nRow, 14, szTemp);
			szTemp = szVal.Tokenize("|", pos);
			m_charinfo.SetItemText(nRow, 15, szTemp);
			szTemp = szVal.Tokenize("|", pos);
			m_charinfo.SetItemText(nRow, 16, szTemp);
			szTemp = szVal.Tokenize("|", pos);
			m_charinfo.SetItemText(nRow, 17, szTemp);
			szTemp = szVal.Tokenize("|", pos);
			m_charinfo.SetItemText(nRow, 19, szTemp);
			szTemp = szVal.Tokenize("|", pos);
			m_charinfo.SetItemText(nRow, 20, szTemp);
			szTemp = szVal.Tokenize("|", pos);
			if (!szTemp.Trim().IsEmpty())
				m_charinfo.SetItemText(nRow, 21, szTemp);
			szTemp = szVal.Tokenize("|", pos);
			m_charinfo.SetItemText(nRow, 22, szTemp);
			szTemp = szVal.Tokenize("|", pos);
			m_charinfo.SetItemText(nRow, 23, szTemp);
			szVal.Format("%s %s�ʺ����µ��룡", cTime.Format(_T("%H:%M:%S")), szName);
			m_message.AddString(szVal);
			m_message.SendMessage(WM_VSCROLL, SB_BOTTOM, 0);
		}

		break;
	case NOTIFY_LOGOUT:
		szVal = (LPCTSTR)pNotifyPara->lpNotifyData;
		pos = 0;
		n = m_charinfo.GetItemCount();
		szTemp = szVal.Tokenize("|", pos);
		for (i = 0; i<n; i++){
			szStr = m_charinfo.GetItemText(i, 0);
			if (szStr == szTemp)
				break;
		}
		if (i<n){
			szTemp = szVal.Tokenize("|", pos);
			m_charinfo.SetItemText(i, 23, szTemp);
			szTemp = szVal.Tokenize("|", pos);
			szVal.Format("%s %s���˳���", cTime.Format(_T("%H:%M:%S")), szTemp);
			m_message.AddString(szVal);
			m_message.SendMessage(WM_VSCROLL, SB_BOTTOM, 0);
		}
		break;
	case NOTIFY_STARTSCRIPT:
		szTemp = (LPCTSTR)pNotifyPara->lpNotifyData;
		szVal.Format("%s %s�ű��߳̿�ʼ���У�", cTime.Format(_T("%H:%M:%S")), szTemp);
		m_message.AddString(szVal);
		m_message.SendMessage(WM_VSCROLL, SB_BOTTOM, 0);
		break;
	case NOTIFY_STOPSCRIPT:
		szTemp = (LPCTSTR)pNotifyPara->lpNotifyData;
		pos = 0;
		szStr = szTemp.Tokenize("|", pos);
		szError = szTemp.Tokenize("|", pos);
		n = atoi(szError);
		if (n == 0)
			szVal.Format("%s %s�ű��߳����˳���", cTime.Format(_T("%H:%M:%S")), szStr);
		else
			szVal.Format("%s %s�ű��߳���%d���д���", cTime.Format(_T("%H:%M:%S")), szStr, n + 1);
		m_message.AddString(szVal);
		m_message.SendMessage(WM_VSCROLL, SB_BOTTOM, 0);
		break;
	case NOTIFY_CHARDETAIL:
		szVal = (LPCTSTR)pNotifyPara->lpNotifyData;
		pos = 0;
		n = m_charinfo.GetItemCount();
		szTemp = szVal.Tokenize("|", pos);
		for (i = 0; i<n; i++){
			szStr = m_charinfo.GetItemText(i, 0);
			if (szStr == szTemp)
				break;
		}
		if (i<n){
			nRow = i;
			szTemp = szVal.Tokenize("|", pos);
			m_charinfo.SetItemText(nRow, 1, szTemp);
			szTemp = szVal.Tokenize("|", pos);
			m_charinfo.SetItemText(nRow, 2, szTemp);
			szTemp = szVal.Tokenize("|", pos);
			m_charinfo.SetItemText(nRow, 3, szTemp);
			szTemp = szVal.Tokenize("|", pos);
			m_charinfo.SetItemText(nRow, 4, szTemp);
			szTemp = szVal.Tokenize("|", pos);
			m_charinfo.SetItemText(nRow, 5, szTemp);
			szTemp = szVal.Tokenize("|", pos);
			m_charinfo.SetItemText(nRow, 6, szTemp);
			szTemp = szVal.Tokenize("|", pos);
			m_charinfo.SetItemText(nRow, 7, szTemp);
			szTemp = szVal.Tokenize("|", pos);
			m_charinfo.SetItemText(nRow, 8, szTemp);
			szTemp = szVal.Tokenize("|", pos);
			m_charinfo.SetItemText(nRow, 9, szTemp);
			szTemp = szVal.Tokenize("|", pos);
			m_charinfo.SetItemText(nRow, 10, szTemp);
			szTemp = szVal.Tokenize("|", pos);
			m_charinfo.SetItemText(nRow, 11, szTemp);
			szTemp = szVal.Tokenize("|", pos);
			m_charinfo.SetItemText(nRow, 12, szTemp);
			szTemp = szVal.Tokenize("|", pos);
			m_charinfo.SetItemText(nRow, 13, szTemp);
			szTemp = szVal.Tokenize("|", pos);
			m_charinfo.SetItemText(nRow, 14, szTemp);
			szTemp = szVal.Tokenize("|", pos);
			m_charinfo.SetItemText(nRow, 15, szTemp);
			szTemp = szVal.Tokenize("|", pos);
			m_charinfo.SetItemText(nRow, 16, szTemp);
			szTemp = szVal.Tokenize("|", pos);
			m_charinfo.SetItemText(nRow, 17, szTemp);
		}
		break;
	case NOTIFY_MAP:
		szVal = (LPCTSTR)pNotifyPara->lpNotifyData;
		pos = 0;
		n = m_charinfo.GetItemCount();
		szTemp = szVal.Tokenize("|", pos);
		for (i = 0; i<n; i++){
			szStr = m_charinfo.GetItemText(i, 0);
			if (szStr == szTemp)
				break;
		}
		if (i<n){
			nRow = i;
			szTemp = szVal.Tokenize("|", pos);
			m_charinfo.SetItemText(nRow, 20, szTemp);//��ͼ
			szTemp = szVal.Tokenize("|", pos);
			m_charinfo.SetItemText(nRow, 21, szTemp);//��ͼ����
			szTemp = szVal.Tokenize("|", pos);
			m_charinfo.SetItemText(nRow, 22, szTemp);//����
		}
		break;
	case NOTIFY_XY:
		szVal = (LPCTSTR)pNotifyPara->lpNotifyData;
		pos = 0;
		n = m_charinfo.GetItemCount();
		szTemp = szVal.Tokenize("|", pos);
		for (i = 0; i<n; i++){
			szStr = m_charinfo.GetItemText(i, 0);
			if (szStr == szTemp)
				break;
		}
		if (i<n){
			nRow = i;
			szTemp = szVal.Tokenize("|", pos);
			m_charinfo.SetItemText(nRow, 22, szTemp);//����
		}
		break;
	case NOTIFY_UPLEVELPOINT:
		szVal = (LPCTSTR)pNotifyPara->lpNotifyData;
		pos = 0;
		n = m_charinfo.GetItemCount();
		szTemp = szVal.Tokenize("|", pos);
		for (i = 0; i<n; i++){
			szStr = m_charinfo.GetItemText(i, 0);
			if (szStr == szTemp)
				break;
		}
		if (i<n){
			nRow = i;
			szTemp = szVal.Tokenize("|", pos);
			m_charinfo.SetItemText(nRow, 19, szTemp);
		}
		break;
	case NOTIFY_ROUND:
		szVal = (LPCTSTR)pNotifyPara->lpNotifyData;
		pos = 0;
		n = m_charinfo.GetItemCount();
		szTemp = szVal.Tokenize("|", pos);
		for (i = 0; i<n; i++){
			szStr = m_charinfo.GetItemText(i, 0);
			if (szStr == szTemp)
				break;
		}
		if (i<n){
			nRow = i;
			szTemp = szVal.Tokenize("|", pos);
			m_charinfo.SetItemText(nRow, 25, szTemp);
		}
		break;
	case NOTIFY_FAME:
		szVal = (LPCTSTR)pNotifyPara->lpNotifyData;
		pos = 0;
		n = m_charinfo.GetItemCount();
		szTemp = szVal.Tokenize("|", pos);
		for (i = 0; i<n; i++){
			szStr = m_charinfo.GetItemText(i, 0);
			if (szStr == szTemp)
				break;
		}
		if (i<n){
			nRow = i;
			szTemp = szVal.Tokenize("|", pos);
			m_charinfo.SetItemText(nRow, 18, szTemp);
		}
		break;
	case NOTIFY_SCRIPT:
		szVal = (LPCTSTR)pNotifyPara->lpNotifyData;
		pos = 0;
		n = m_charinfo.GetItemCount();
		szTemp = szVal.Tokenize("|", pos);
		for (i = 0; i<n; i++){
			szStr = m_charinfo.GetItemText(i, 0);
			if (szStr == szTemp)
				break;
		}
		if (i<n){
			nRow = i;
			szTemp = szVal.Tokenize("^", pos);
			m_charinfo.SetItemText(nRow, 24, szTemp);
		}
		break;
	case NOTIFY_GAMESTATE:
		szVal = (LPCTSTR)pNotifyPara->lpNotifyData;
		pos = 0;
		n = m_charinfo.GetItemCount();
		szTemp = szVal.Tokenize("|", pos);
		for (i = 0; i<n; i++){
			szStr = m_charinfo.GetItemText(i, 0);
			if (szStr == szTemp)
				break;
		}
		if (i<n){
			szTemp = szVal.Tokenize("|", pos);
			m_charinfo.SetItemText(i, 23, szTemp);
		}
		break;
	}
	*/
}


//�ص�����
void Callback_func(WPARAM wParam, NOTIFYPARA *pNotifyPara)
{
	CDialogAccount *p = (CDialogAccount *)wParam;
	ASSERT(p);
	p->CallbackMsg(pNotifyPara);
}

//���ûص������������
void Set_Callback(CALLBACK_Func func, WPARAM wParam)
{
	f_Callback = func;
	f_Param = wParam;
}

//�ص������������������
void Callback_Notify(NOTIFYPARA *pNotifyPara)
{
	if (f_Callback)
		f_Callback(f_Param, pNotifyPara);
}

