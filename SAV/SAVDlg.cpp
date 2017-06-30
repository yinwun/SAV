
// SAVDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SAV.h"
#include "SAVDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

THREADPARA g_para[100];
USERINFO *g_userinfo = NULL;
int g_userNum = 0;
SALib *pDp = NULL;

long gametime; // Timer seed
CALLBACK_Func f_Callback = NULL;
WPARAM f_Param = NULL;

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSAVDlg �Ի���



CSAVDlg::CSAVDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSAVDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSAVDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TABMain, m_tabMain);
	DDX_Control(pDX, IDC_lsMessage, m_message);
	DDX_Control(pDX, IDC_lstChar, m_charinfo);
	DDX_Control(pDX, IDC_txtTime, m_time);

	
}

BEGIN_MESSAGE_MAP(CSAVDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_btnSingleLogin, &CSAVDlg::OnBnClickedbtnsinglelogin)
END_MESSAGE_MAP()


// CSAVDlg ��Ϣ�������

BOOL CSAVDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	
	m_tabMain.InsertItem(0, _T("�˺Ź���"));
	m_tabMain.InsertItem(1, _T("�˳�����"));
	
	m_para_account.Create(IDD_DlgAccount, GetDlgItem(IDC_TABMain));
	m_para_charInfo.Create(IDD_DlgCharInfo, GetDlgItem(IDC_TABMain));

	CRect rs;
	m_tabMain.GetClientRect(&rs);
	rs.top += 22;
	rs.bottom -= 1;
	rs.left += 1;
	rs.right -= 1;

	m_para_account.MoveWindow(&rs);
	m_para_charInfo.MoveWindow(&rs);


	m_tabMain.SetCurSel(0);
	m_para_account.ShowWindow(true);
	m_para_charInfo.ShowWindow(false);

	BindInfoList();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CSAVDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSAVDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CSAVDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSAVDlg::OnTcnSelchangeTabmain(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	int curSel = m_tabMain.GetCurSel();
	switch (curSel)
	{
	case 0:
		m_para_account.ShowWindow(true);
		m_para_charInfo.ShowWindow(false);
		break;
	case 1:
		m_para_account.ShowWindow(false);
		m_para_charInfo.ShowWindow(true);
	default:
		break;
	}

	*pResult = 0;
}

void CSAVDlg::OnSinglelogin()
{
	UpdateData(TRUE);

}

void CSAVDlg::OnBnClickedbtnsinglelogin()
{
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);

	int pos = 0;
	pos = (int)m_para_account.m_listAct.GetFirstSelectedItemPosition() - 1;
	if (pos < 0)
	{
		MessageBox(L"����ѡ��Ҫ�������ʺţ�", L"��ʾ��Ϣ", MB_OK | MB_ICONINFORMATION);
		return;
	}
	else
	{

		//�ʺŵ���
		for (int i = 0; i < g_userNum; i++){
			CharLogin(i);
			Sleep(100);
		}
	}
	/*

	//��ȡ��������ַ
	vector<CString> vecLine = GetLineInConfigurationINI();
	if (vecLine.empty())
	{
		MessageBox(L"û��������ַ��", L"��ʾ��Ϣ", MB_OK | MB_ICONINFORMATION);
		return;
	}
	

	
	
	HOSTENT *lpHostEnt;
	struct in_addr inAddr;
	LPSTR lpaddr;
	char ip[30];
	char serverName[30];
	memset(ip, 0, sizeof(ip));

	strncpy_s(ip, "116.10.184.141", strlen("116.10.184.141"));
	strncpy_s(serverName, "ʯ������1", strlen("ʯ������1"));

	lpHostEnt = gethostbyname(ip);
	if (!lpHostEnt)return;
	lpaddr = lpHostEnt->h_addr_list[0];
	memmove(&inAddr, lpaddr, 4);
	sprintf_s(ip, "%d.%d.%d.%d", inAddr.S_un.S_addr & 0xff, (inAddr.S_un.S_addr >> 8) & 0xff, (inAddr.S_un.S_addr >> 16) & 0xff, (inAddr.S_un.S_addr >> 24) & 0xff);
	strcpy_s(g_serverinfo.ip, ip);
	g_serverinfo.port = 9065;

	char *serverKey = (char*)malloc(150 * sizeof(char));

	strcpy_s(user.charname, "yinwun15");
	strcpy_s(user.password, "dI34286834Y");
	strcpy_s(user.safecode, "123");
	strcpy_s(user.scriptName, "");
	SOCKET socket;
	BOOL isConnect = false;
	//ConnectServer(socket, g_serverinfo.ip, g_serverinfo.port, &*serverKey);


	//���ӷ����
	if (!isConnect) {

		MessageBox(L"A");


	}
	else

	{

		//����runningKey
		CString strtmp(serverKey);
		//AfxMessageBox(strtmp);
		CString str = strtmp.Right(strtmp.GetLength() - 1);
		SASO *so = new SASO(str);
		char *SOKey = so->RunningKey();
	}
	*/
}

void CSAVDlg::BindInfoList()
{

	//Bind List Control
	LONG styles;
	styles = m_para_account.m_listAct.GetExtendedStyle();
	//LVS_EX_FULLROWSELECT����ѡ��
	//LVS_EX_GRIDLINES��������
	//LVS_EX_CHECKBOXESǰ��Ӹ�ѡ��
	m_para_account.m_listAct.SetExtendedStyle(styles | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	LV_COLUMN lvcol;
	lvcol.mask = LVCF_WIDTH | LVCF_TEXT | LVCF_FMT | LVCF_SUBITEM;
	lvcol.fmt = LVCFMT_LEFT;
	lvcol.cx = 70;
	lvcol.iSubItem = 0;
	lvcol.pszText = L"�ʺ�";
	m_para_account.m_listAct.InsertColumn(0, &lvcol);
	lvcol.cx = 40;
	lvcol.iSubItem = 0;
	lvcol.pszText = L"����";
	m_para_account.m_listAct.InsertColumn(1, &lvcol);
	lvcol.cx = 30;
	lvcol.iSubItem = 0;
	lvcol.pszText = L"��ȫ��";
	m_para_account.m_listAct.InsertColumn(2, &lvcol);
	lvcol.cx = 40;
	lvcol.iSubItem = 0;
	lvcol.pszText = L"����";
	m_para_account.m_listAct.InsertColumn(3, &lvcol);
	lvcol.cx = 80;
	lvcol.iSubItem = 0;
	lvcol.pszText = L"�ű�";
	m_para_account.m_listAct.InsertColumn(4, &lvcol);
	lvcol.cx = 80;
	lvcol.iSubItem = 0;
	lvcol.pszText = L"�����ļ�";
	m_para_account.m_listAct.InsertColumn(5, &lvcol);
	lvcol.cx = 70;
	lvcol.iSubItem = 0;
	lvcol.pszText = L"������·";
	m_para_account.m_listAct.InsertColumn(6, &lvcol);
	lvcol.cx = 70;
	lvcol.iSubItem = 0;
	lvcol.pszText = L"��������";
	m_para_account.m_listAct.InsertColumn(7, &lvcol);
	lvcol.cx = 70;
	lvcol.iSubItem = 0;
	lvcol.pszText = L"��Ա����";
	m_para_account.m_listAct.InsertColumn(8, &lvcol);
	lvcol.cx = 70;
	lvcol.iSubItem = 0;
	lvcol.pszText = L"����״̬";
	m_para_account.m_listAct.InsertColumn(9, &lvcol);
	lvcol.cx = 0;
	lvcol.iSubItem = 0;
	lvcol.pszText = L"������IP";
	m_para_account.m_listAct.InsertColumn(10, &lvcol);
	lvcol.cx = 0;
	lvcol.iSubItem = 0;
	lvcol.pszText = L"�������˿�";
	m_para_account.m_listAct.InsertColumn(11, &lvcol);

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

			nRow = m_para_account.m_listAct.InsertItem(m_para_account.m_listAct.GetItemCount(), szAccount);
			m_para_account.m_listAct.SetItemText(nRow, 1, szPwd);
			m_para_account.m_listAct.SetItemText(nRow, 2, szSafeCode);
			m_para_account.m_listAct.SetItemText(nRow, 3, szchar);
			m_para_account.m_listAct.SetItemText(nRow, 4, szScript);
			m_para_account.m_listAct.SetItemText(nRow, 5, szSetting);
			m_para_account.m_listAct.SetItemText(nRow, 6, szLine);
			m_para_account.m_listAct.SetItemText(nRow, 7, szTeam);
			m_para_account.m_listAct.SetItemText(nRow, 8, szTeammate);
			m_para_account.m_listAct.SetItemText(nRow, 10, szServer);
			m_para_account.m_listAct.SetItemText(nRow, 11, szPort);
			//}
		}

		f.Close();
	}
	catch (...){
	}

	//�ʺŴ���
	g_userNum = m_para_account.m_listAct.GetItemCount();
	if (g_userNum > 0)
	{
		g_userinfo = new USERINFO[g_userNum];
		for (int i = 0; i < g_userNum; i++){
			szAccount = m_para_account.m_listAct.GetItemText(i, 0);
			szPwd = m_para_account.m_listAct.GetItemText(i, 1);
			szSafeCode = m_para_account.m_listAct.GetItemText(i, 2);
			szScript = m_para_account.m_listAct.GetItemText(i, 4);
			szLine = m_para_account.m_listAct.GetItemText(i, 6);

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
	GetDlgItem(IDC_START)->EnableWindow(TRUE);
	*/
}

void CSAVDlg::CallbackMsg(NOTIFYPARA *pNotifyPara)
{
	CString szVal, szTemp, szStr, szName, szError;
	int i, n, nRow, pos;
	CTime cTime = CTime::GetCurrentTime();
	if (m_message.GetCount() > 500)
		m_message.ResetContent();
	switch (pNotifyPara->nNotityType)
	{
	case NOTIFY_TIME:
		if (!TimerOn)
			TimerOn = SetTimer(1, 1000, NULL);
		break;
	case NOTIFY_MSG:
		szVal.Format(L"%s %s", cTime.Format(_T("%H:%M:%S")), (LPCTSTR)pNotifyPara->lpNotifyData);
		m_message.AddString(szVal);
		m_message.SendMessage(WM_VSCROLL, SB_BOTTOM, 0);
		break;
	case NOTIFY_LOGIN:
		szVal = (LPCTSTR)pNotifyPara->lpNotifyData;
		pos = 0;
		//ȡ�ʺ�
		szName = szVal.Tokenize(L"|", pos);
		n = m_charinfo.GetItemCount();
		//ȡ������
		szTemp = szVal.Tokenize(L"|", pos);
		//ָ���ʺ��Ƿ����б����
		for (i = 0; i < n; i++){
			szStr = m_charinfo.GetItemText(i, 0);
			if (szStr == szTemp)
				break;
		}
		if (i >= n){
			nRow = m_charinfo.InsertItem(n, szTemp);
			szTemp = szVal.Tokenize(L"|", pos);
			m_charinfo.SetItemText(nRow, 1, szTemp);
			szTemp = szVal.Tokenize(L"|", pos);
			m_charinfo.SetItemText(nRow, 2, szTemp);
			szTemp = szVal.Tokenize(L"|", pos);
			m_charinfo.SetItemText(nRow, 3, szTemp);
			szTemp = szVal.Tokenize(L"|", pos);
			m_charinfo.SetItemText(nRow, 4, szTemp);
			szTemp = szVal.Tokenize(L"|", pos);
			m_charinfo.SetItemText(nRow, 5, szTemp);
			szTemp = szVal.Tokenize(L"|", pos);
			m_charinfo.SetItemText(nRow, 6, szTemp);
			szTemp = szVal.Tokenize(L"|", pos);
			m_charinfo.SetItemText(nRow, 7, szTemp);
			szTemp = szVal.Tokenize(L"|", pos);
			m_charinfo.SetItemText(nRow, 8, szTemp);
			szTemp = szVal.Tokenize(L"|", pos);
			m_charinfo.SetItemText(nRow, 9, szTemp);
			szTemp = szVal.Tokenize(L"|", pos);
			m_charinfo.SetItemText(nRow, 10, szTemp);
			szTemp = szVal.Tokenize(L"|", pos);
			m_charinfo.SetItemText(nRow, 11, szTemp);
			szTemp = szVal.Tokenize(L"|", pos);
			m_charinfo.SetItemText(nRow, 12, szTemp);
			szTemp = szVal.Tokenize(L"|", pos);
			m_charinfo.SetItemText(nRow, 13, szTemp);
			szTemp = szVal.Tokenize(L"|", pos);
			m_charinfo.SetItemText(nRow, 14, szTemp);
			szTemp = szVal.Tokenize(L"|", pos);
			m_charinfo.SetItemText(nRow, 15, szTemp);
			szTemp = szVal.Tokenize(L"|", pos);
			m_charinfo.SetItemText(nRow, 16, szTemp);
			szTemp = szVal.Tokenize(L"|", pos);
			m_charinfo.SetItemText(nRow, 17, szTemp);
			szTemp = szVal.Tokenize(L"|", pos);
			m_charinfo.SetItemText(nRow, 19, szTemp);
			szTemp = szVal.Tokenize(L"|", pos);
			m_charinfo.SetItemText(nRow, 20, szTemp);
			szTemp = szVal.Tokenize(L"|", pos);
			if (!szTemp.Trim().IsEmpty())
				m_charinfo.SetItemText(nRow, 21, szTemp);
			szTemp = szVal.Tokenize(L"|", pos);
			m_charinfo.SetItemText(nRow, 22, szTemp);
			szTemp = szVal.Tokenize(L"|", pos);
			m_charinfo.SetItemText(nRow, 23, szTemp);
			szVal.Format(L"%s %s�ʺ��ѵ��룡", cTime.Format(_T("%H:%M:%S")), szName);
			m_message.AddString(szVal);
			m_message.SendMessage(WM_VSCROLL, SB_BOTTOM, 0);
		}
		else{
			nRow = i;
			szTemp = szVal.Tokenize(L"|", pos);
			m_charinfo.SetItemText(nRow, 1, szTemp);
			szTemp = szVal.Tokenize(L"|", pos);
			m_charinfo.SetItemText(nRow, 2, szTemp);
			szTemp = szVal.Tokenize(L"|", pos);
			m_charinfo.SetItemText(nRow, 3, szTemp);
			szTemp = szVal.Tokenize(L"|", pos);
			m_charinfo.SetItemText(nRow, 4, szTemp);
			szTemp = szVal.Tokenize(L"|", pos);
			m_charinfo.SetItemText(nRow, 5, szTemp);
			szTemp = szVal.Tokenize(L"|", pos);
			m_charinfo.SetItemText(nRow, 6, szTemp);
			szTemp = szVal.Tokenize(L"|", pos);
			m_charinfo.SetItemText(nRow, 7, szTemp);
			szTemp = szVal.Tokenize(L"|", pos);
			m_charinfo.SetItemText(nRow, 8, szTemp);
			szTemp = szVal.Tokenize(L"|", pos);
			m_charinfo.SetItemText(nRow, 9, szTemp);
			szTemp = szVal.Tokenize(L"|", pos);
			m_charinfo.SetItemText(nRow, 10, szTemp);
			szTemp = szVal.Tokenize(L"|", pos);
			m_charinfo.SetItemText(nRow, 11, szTemp);
			szTemp = szVal.Tokenize(L"|", pos);
			m_charinfo.SetItemText(nRow, 12, szTemp);
			szTemp = szVal.Tokenize(L"|", pos);
			m_charinfo.SetItemText(nRow, 13, szTemp);
			szTemp = szVal.Tokenize(L"|", pos);
			m_charinfo.SetItemText(nRow, 14, szTemp);
			szTemp = szVal.Tokenize(L"|", pos);
			m_charinfo.SetItemText(nRow, 15, szTemp);
			szTemp = szVal.Tokenize(L"|", pos);
			m_charinfo.SetItemText(nRow, 16, szTemp);
			szTemp = szVal.Tokenize(L"|", pos);
			m_charinfo.SetItemText(nRow, 17, szTemp);
			szTemp = szVal.Tokenize(L"|", pos);
			m_charinfo.SetItemText(nRow, 19, szTemp);
			szTemp = szVal.Tokenize(L"|", pos);
			m_charinfo.SetItemText(nRow, 20, szTemp);
			szTemp = szVal.Tokenize(L"|", pos);
			if (!szTemp.Trim().IsEmpty())
				m_charinfo.SetItemText(nRow, 21, szTemp);
			szTemp = szVal.Tokenize(L"|", pos);
			m_charinfo.SetItemText(nRow, 22, szTemp);
			szTemp = szVal.Tokenize(L"|", pos);
			m_charinfo.SetItemText(nRow, 23, szTemp);
			szVal.Format(L"%s %s�ʺ����µ��룡", cTime.Format(_T("%H:%M:%S")), szName);
			m_message.AddString(szVal);
			m_message.SendMessage(WM_VSCROLL, SB_BOTTOM, 0);
		}

		break;
	case NOTIFY_LOGOUT:
		szVal = (LPCTSTR)pNotifyPara->lpNotifyData;
		pos = 0;
		n = m_charinfo.GetItemCount();
		szTemp = szVal.Tokenize(L"|", pos);
		for (i = 0; i < n; i++){
			szStr = m_charinfo.GetItemText(i, 0);
			if (szStr == szTemp)
				break;
		}
		if (i < n){
			szTemp = szVal.Tokenize(L"|", pos);
			m_charinfo.SetItemText(i, 23, szTemp);
			szTemp = szVal.Tokenize(L"|", pos);
			szVal.Format(L"%s %s���˳���", cTime.Format(_T("%H:%M:%S")), szTemp);
			m_message.AddString(szVal);
			m_message.SendMessage(WM_VSCROLL, SB_BOTTOM, 0);
		}
		break;
	case NOTIFY_STARTSCRIPT:
		szTemp = (LPCTSTR)pNotifyPara->lpNotifyData;
		szVal.Format(L"%s %s�ű��߳̿�ʼ���У�", cTime.Format(_T("%H:%M:%S")), szTemp);
		m_message.AddString(szVal);
		m_message.SendMessage(WM_VSCROLL, SB_BOTTOM, 0);
		break;
	case NOTIFY_STOPSCRIPT:
		szTemp = (LPCTSTR)pNotifyPara->lpNotifyData;
		pos = 0;
		szStr = szTemp.Tokenize(L"|", pos);
		szError = szTemp.Tokenize(L"|", pos);
		n = _ttoi(szError);
		if (n == 0)
			szVal.Format(L"%s %s�ű��߳����˳���", cTime.Format(_T("%H:%M:%S")), szStr);
		else
			szVal.Format(L"%s %s�ű��߳���%d���д���", cTime.Format(_T("%H:%M:%S")), szStr, n + 1);
		m_message.AddString(szVal);
		m_message.SendMessage(WM_VSCROLL, SB_BOTTOM, 0);
		break;
	case NOTIFY_CHARDETAIL:
		szVal = (LPCTSTR)pNotifyPara->lpNotifyData;
		pos = 0;
		n = m_charinfo.GetItemCount();
		szTemp = szVal.Tokenize(L"|", pos);
		for (i = 0; i < n; i++){
			szStr = m_charinfo.GetItemText(i, 0);
			if (szStr == szTemp)
				break;
		}
		if (i < n){
			nRow = i;
			szTemp = szVal.Tokenize(L"|", pos);
			m_charinfo.SetItemText(nRow, 1, szTemp);
			szTemp = szVal.Tokenize(L"|", pos);
			m_charinfo.SetItemText(nRow, 2, szTemp);
			szTemp = szVal.Tokenize(L"|", pos);
			m_charinfo.SetItemText(nRow, 3, szTemp);
			szTemp = szVal.Tokenize(L"|", pos);
			m_charinfo.SetItemText(nRow, 4, szTemp);
			szTemp = szVal.Tokenize(L"|", pos);
			m_charinfo.SetItemText(nRow, 5, szTemp);
			szTemp = szVal.Tokenize(L"|", pos);
			m_charinfo.SetItemText(nRow, 6, szTemp);
			szTemp = szVal.Tokenize(L"|", pos);
			m_charinfo.SetItemText(nRow, 7, szTemp);
			szTemp = szVal.Tokenize(L"|", pos);
			m_charinfo.SetItemText(nRow, 8, szTemp);
			szTemp = szVal.Tokenize(L"|", pos);
			m_charinfo.SetItemText(nRow, 9, szTemp);
			szTemp = szVal.Tokenize(L"|", pos);
			m_charinfo.SetItemText(nRow, 10, szTemp);
			szTemp = szVal.Tokenize(L"|", pos);
			m_charinfo.SetItemText(nRow, 11, szTemp);
			szTemp = szVal.Tokenize(L"|", pos);
			m_charinfo.SetItemText(nRow, 12, szTemp);
			szTemp = szVal.Tokenize(L"|", pos);
			m_charinfo.SetItemText(nRow, 13, szTemp);
			szTemp = szVal.Tokenize(L"|", pos);
			m_charinfo.SetItemText(nRow, 14, szTemp);
			szTemp = szVal.Tokenize(L"|", pos);
			m_charinfo.SetItemText(nRow, 15, szTemp);
			szTemp = szVal.Tokenize(L"|", pos);
			m_charinfo.SetItemText(nRow, 16, szTemp);
			szTemp = szVal.Tokenize(L"|", pos);
			m_charinfo.SetItemText(nRow, 17, szTemp);
		}
		break;
	case NOTIFY_MAP:
		szVal = (LPCTSTR)pNotifyPara->lpNotifyData;
		pos = 0;
		n = m_charinfo.GetItemCount();
		szTemp = szVal.Tokenize(L"|", pos);
		for (i = 0; i < n; i++){
			szStr = m_charinfo.GetItemText(i, 0);
			if (szStr == szTemp)
				break;
		}
		if (i < n){
			nRow = i;
			szTemp = szVal.Tokenize(L"|", pos);
			m_charinfo.SetItemText(nRow, 20, szTemp);//��ͼ
			szTemp = szVal.Tokenize(L"|", pos);
			m_charinfo.SetItemText(nRow, 21, szTemp);//��ͼ����
			szTemp = szVal.Tokenize(L"|", pos);
			m_charinfo.SetItemText(nRow, 22, szTemp);//����
		}
		break;
	case NOTIFY_XY:
		szVal = (LPCTSTR)pNotifyPara->lpNotifyData;
		pos = 0;
		n = m_charinfo.GetItemCount();
		szTemp = szVal.Tokenize(L"|", pos);
		for (i = 0; i < n; i++){
			szStr = m_charinfo.GetItemText(i, 0);
			if (szStr == szTemp)
				break;
		}
		if (i < n){
			nRow = i;
			szTemp = szVal.Tokenize(L"|", pos);
			m_charinfo.SetItemText(nRow, 22, szTemp);//����
		}
		break;
	case NOTIFY_UPLEVELPOINT:
		szVal = (LPCTSTR)pNotifyPara->lpNotifyData;
		pos = 0;
		n = m_charinfo.GetItemCount();
		szTemp = szVal.Tokenize(L"|", pos);
		for (i = 0; i < n; i++){
			szStr = m_charinfo.GetItemText(i, 0);
			if (szStr == szTemp)
				break;
		}
		if (i < n){
			nRow = i;
			szTemp = szVal.Tokenize(L"|", pos);
			m_charinfo.SetItemText(nRow, 19, szTemp);
		}
		break;
	case NOTIFY_ROUND:
		szVal = (LPCTSTR)pNotifyPara->lpNotifyData;
		pos = 0;
		n = m_charinfo.GetItemCount();
		szTemp = szVal.Tokenize(L"|", pos);
		for (i = 0; i < n; i++){
			szStr = m_charinfo.GetItemText(i, 0);
			if (szStr == szTemp)
				break;
		}
		if (i < n){
			nRow = i;
			szTemp = szVal.Tokenize(L"|", pos);
			m_charinfo.SetItemText(nRow, 25, szTemp);
		}
		break;
	case NOTIFY_FAME:
		szVal = (LPCTSTR)pNotifyPara->lpNotifyData;
		pos = 0;
		n = m_charinfo.GetItemCount();
		szTemp = szVal.Tokenize(L"|", pos);
		for (i = 0; i < n; i++){
			szStr = m_charinfo.GetItemText(i, 0);
			if (szStr == szTemp)
				break;
		}
		if (i < n){
			nRow = i;
			szTemp = szVal.Tokenize(L"|", pos);
			m_charinfo.SetItemText(nRow, 18, szTemp);
		}
		break;
	case NOTIFY_SCRIPT:
		szVal = (LPCTSTR)pNotifyPara->lpNotifyData;
		pos = 0;
		n = m_charinfo.GetItemCount();
		szTemp = szVal.Tokenize(L"|", pos);
		for (i = 0; i < n; i++){
			szStr = m_charinfo.GetItemText(i, 0);
			if (szStr == szTemp)
				break;
		}
		if (i < n){
			nRow = i;
			szTemp = szVal.Tokenize(L"^", pos);
			m_charinfo.SetItemText(nRow, 24, szTemp);
		}
		break;
	case NOTIFY_GAMESTATE:
		szVal = (LPCTSTR)pNotifyPara->lpNotifyData;
		pos = 0;
		n = m_charinfo.GetItemCount();
		szTemp = szVal.Tokenize(L"|", pos);
		for (i = 0; i < n; i++){
			szStr = m_charinfo.GetItemText(i, 0);
			if (szStr == szTemp)
				break;
		}
		if (i < n){
			szTemp = szVal.Tokenize(L"|", pos);
			m_charinfo.SetItemText(i, 23, szTemp);
		}
		break;
	}

}

void CSAVDlg::OnTimer(UINT_PTR nIDEvent)
{
	UpdateData(TRUE);
	gametime++;
	CTime time1(gametime);

	CString szVal, szStr;
	szVal = time1.Format(_T("%d�� %H:%M:%S"));
	m_time.SetWindowText(szVal);
	int i;
	for (i = 0; i < g_userNum; i++)
	{
		//��ǰ�߳�δ�˳���������,����������Ϣ
		if (!pDp[i].bExit && pDp[i].IsOnLine)
		{
			if ((GetTickCount() - pDp[i].nStartTime) / 1000 >= 30){
				if (pDp[i].SendOnlineInfo("hoge") != SUCCESSFUL){
					CTime cTime = CTime::GetCurrentTime();
					szVal.Format(L"%s %s%s", cTime.Format(_T("%H:%M:%S")), pDp[i].user.charname, "�����������Ѷϣ�");
					m_message.AddString(szVal);
				}
			}
		}
		//�����ǰ�ʺŲ�����
		if (!pDp[i].IsOnLine){
			//�����˶����ص�,���Ҳ������ϣ�����û�ڵ�¼������
			if (pDp[i].bReLogin && !pDp[i].IsOnLine && !pDp[i].IsLogin){
				pDp[i].IsLogin = TRUE;
				//CharLogin(i);
			}
		}//END:�����ǰ�ʺŲ�����
		/*
		//�Զ���������
		if (pDp[i].bAutoEatSYC && pDp[i].charotherinfo.state == 0 && (GetTickCount() - pDp[i].nEatSYCTime) >= 3600000){
			pDp[i].SendEatSYC();
			//pDp[i].nEatSYCTime=GetTickCount();
		}
		//�Զ����ǻ۹�
		if (pDp[i].bAutoExpNut && pDp[i].charotherinfo.state == 0 && (GetTickCount() - pDp[i].nExpNutTime) >= 3600000){
			pDp[i].SendEatExpNut();
			//pDp[i].nExpNutTime=GetTickCount();
		}
		*/
	}
	CDialogEx::OnTimer(nIDEvent);
}

BOOL CSAVDlg::CharLogin(int index)
{
	CString szVal;
	DWORD thread;
	HANDLE hThreads;

	g_para[index].index = index;
	//���̴߳��ݲ��������þֲ�����	
	hThreads = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)RunThread, (void *)&g_para[index], 0, &thread);
	if (!hThreads){
		MessageBox(L"������Ϸ�߳�ʧ�ܣ�", L"������Ϣ", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}
	/*
	if (m_autorun && pDp[index].bScriptExit){
		hThreads = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)RunScriptThread, (void *)&g_para[index], 0, &thread);
		if (!hThreads){
			MessageBox(L"�����ű��߳�ʧ�ܣ�", L"������Ϣ", MB_OK | MB_ICONEXCLAMATION);
			return FALSE;
		}
	}
	*/
	return TRUE;
}

//��һ���߳�
void RunThread(LPVOID p)
{
	THREADPARA *para = (THREADPARA *)p;
	pDp[para->index].Run(&g_userinfo[para->index]);
}

//�ص�����
void Callback_func(WPARAM wParam, NOTIFYPARA *pNotifyPara)
{
	CSAVDlg *p = (CSAVDlg *)wParam;
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

