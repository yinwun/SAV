
// SAVDlg.cpp : 实现文件
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

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CSAVDlg 对话框



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


// CSAVDlg 消息处理程序

BOOL CSAVDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	
	m_tabMain.InsertItem(0, _T("账号管理"));
	m_tabMain.InsertItem(1, _T("人宠资料"));
	
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


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSAVDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
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

	//获取服务器地址
	vector<CString> vecLine = GetLineInConfigurationINI();
	if (vecLine.empty())
	{
		MessageBox(L"没服务器地址！", L"提示信息", MB_OK | MB_ICONINFORMATION);
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
	strncpy_s(serverName, "石器电信1", strlen("石器电信1"));

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


	//连接服务端
	if (!isConnect) {

		MessageBox(L"A");


	}
	else

	{

		//生成runningKey
		CString strtmp(serverKey);
		//AfxMessageBox(strtmp);
		CString str = strtmp.Right(strtmp.GetLength() - 1);
		SASO *so = new SASO(str);
		char *SOKey = so->RunningKey();
	}
	*/
}
