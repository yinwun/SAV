
// SAVDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SAV.h"
#include "SAVDlg.h"
#include "afxdialogex.h"
#include "SASO.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CDialogAccount cdlgact;

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

	

	cdlgact.GetAccountList();

	//��ȡ��������ַ
	vector<CString> vecLine = GetLineInConfigurationINI();
	if (vecLine.empty())
	{
		MessageBox(L"û��������ַ��", L"��ʾ��Ϣ", MB_OK | MB_ICONINFORMATION);
		return;
	}
	

	
	/*
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
