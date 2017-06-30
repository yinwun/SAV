#pragma once
#include <math.h>
#include "malloc.h"
#include <vector>
#include "iphlpapi.h"
#pragma   comment(lib, "Iphlpapi.lib ")


#pragma region Struct

//�����ip��ַ�Ͷ˿ں�
typedef struct {
	char servername[30];
	char ip[30];
	int port;
}SERVERINFO;

//��¼�ʺ���Ϣ
typedef struct {
	char charname[30];
	char password[30];
	char safecode[30];
	int index;			//�ڼ����ʺ�
	char scriptName[100];//�ű��ļ���
	char servername[100];
	int port;
}USERINFO;

//�ص���Ϣ�ṹ
typedef struct{
	UINT nNotityType;		//��Ϣ���ͣ��������ö�ٶ���
	LPVOID lpNotifyData;	//��Ϣ����
}NOTIFYPARA;

//�ص���Ϣ����
enum{
	NOTIFY_TIME,
	NOTIFY_MSG,
	NOTIFY_LOGIN,
	NOTIFY_LOGOUT,
	NOTIFY_CHARDETAIL,
	NOTIFY_MAP,
	NOTIFY_XY,
	NOTIFY_UPLEVELPOINT,
	NOTIFY_SCRIPT,
	NOTIFY_STARTSCRIPT,
	NOTIFY_STOPSCRIPT,
	NOTIFY_GAMESTATE,
	NOTIFY_ROUND,
	NOTIFY_FAME
};

//�������̴߳������Ͳ���
typedef struct{
	int index;
}THREADPARA;
#pragma endregion

typedef void(*CALLBACK_Func) (WPARAM wParam, NOTIFYPARA *msg);

int ConnectServer(SOCKET &rsocket, char *ip, int port, char *serverKey);

vector<CString> GetLineInConfigurationINI();

int ReadInteger(CString szSection, CString szKey, int iDefaultValue, CString m_szFileName);

CString ReadString(CString szSection, CString szKey, CString szDefaultValue, CString m_szFileName);

int WriteDataToFile(LPCSTR filename, char* data, long size, LPCSTR mode, int nStartPos/*=-1*/);

void DbgLog(LPCTSTR lpszFormat,...);

CString GetCurTimeString();