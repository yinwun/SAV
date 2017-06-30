#pragma once
#include <math.h>
#include "malloc.h"
#include <vector>
#include "iphlpapi.h"
#pragma   comment(lib, "Iphlpapi.lib ")


#pragma region Struct

//服务端ip地址和端口号
typedef struct {
	char servername[30];
	char ip[30];
	int port;
}SERVERINFO;

//登录帐号信息
typedef struct {
	char charname[30];
	char password[30];
	char safecode[30];
	int index;			//第几个帐号
	char scriptName[100];//脚本文件名
	char servername[100];
	int port;
}USERINFO;

//回调消息结构
typedef struct{
	UINT nNotityType;		//信息类型，见上面的枚举定义
	LPVOID lpNotifyData;	//信息内容
}NOTIFYPARA;

//回调消息类型
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

//用于向线程传递整型参数
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