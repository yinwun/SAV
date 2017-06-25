
// SAVDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "DialogAccount.h"
#include "DialogCharInfo.h"
#include "Common.h"

// CSAVDlg �Ի���
class CSAVDlg : public CDialogEx
{
// ����
public:
	CSAVDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SAV_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
