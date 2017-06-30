
// SAVDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "DialogAccount.h"
#include "DialogCharInfo.h"
#include "Common.h"
#include "SASO.h"


// CSAVDlg �Ի���
class CSAVDlg : public CDialogEx
{
// ����
public:
	CSAVDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SAV_DIALOG };

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
	CListBox m_message;
	CListCtrl m_charinfo;
	CDialogCharInfo m_para_charInfo;
	CDialogAccount m_para_account;

	afx_msg void OnTcnSelchangeTabmain(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSinglelogin();
	afx_msg void OnBnClickedbtnsinglelogin();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	void BindInfoList();
	void CallbackMsg(NOTIFYPARA *pNotifyPara);
	BOOL CharLogin(int index);

	UINT TimerOn;
	CStatic m_time;
	BOOL m_autorun;
};


void Callback_func(WPARAM wParam, NOTIFYPARA *pNotifyPara);
void Set_Callback(CALLBACK_Func func, WPARAM wParam);
void Callback_Notify(NOTIFYPARA *pNotifyPara);
void RunThread(LPVOID p);