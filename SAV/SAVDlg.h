
// SAVDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "DialogAccount.h"
#include "DialogCharInfo.h"
#include "Common.h"

// CSAVDlg 对话框
class CSAVDlg : public CDialogEx
{
// 构造
public:
	CSAVDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SAV_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_tabMain;
	CDialogAccount m_para_account;
	CDialogCharInfo m_para_charInfo;
	CListCtrl m_listAct;
	afx_msg void OnTcnSelchangeTabmain(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedbtnsinglelogin();

	
	SERVERINFO g_serverinfo;
	USERINFO user;						
};
