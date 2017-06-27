#include "stdafx.h"
#include "Common.h"

int ConnectServer(SOCKET &rsocket, char *ip, int port, char *serverKey)
{
	int nRet = -1;
	BOOL bConnected = FALSE;

	rsocket = socket(AF_INET, SOCK_STREAM, 0);
	//套接字创建失败！
	if (rsocket == INVALID_SOCKET)
		return -1;
	sockaddr_in servAddr;
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(port);
	servAddr.sin_addr.s_addr = inet_addr(ip);

	//设置接收超时时间为35秒
	int nTimeout = 35000;
	if (setsockopt(rsocket, SOL_SOCKET, SO_RCVTIMEO, (char*)&nTimeout, sizeof(nTimeout)) == SOCKET_ERROR)
		return -2;
	//把当前套接字设为非阻塞模式
	unsigned long nFlag = 1;
	nRet = ioctlsocket(rsocket, FIONBIO, (unsigned long*)&nFlag);
	if (nRet == SOCKET_ERROR)//把当前套接字设为非阻塞模式失败!
		return -3;
	//非阻塞模式下执行I/O操作时，Winsock函数会立即返回并交出控制权。这种模式使用起来比较复杂，
	//因为函数在没有运行完成就进行返回，会不断地返回WSAEWOULDBLOCK错误。
	if (connect(rsocket, (struct sockaddr *)&servAddr, sizeof(servAddr)) == SOCKET_ERROR) {
		struct timeval timeout = { 0 };
		timeout.tv_sec = 10;	//连接超时时间为10秒,此值过小会造成多线程同时连接服务端时因无法建立连接而通信失败
		timeout.tv_usec = 0;	//产生此情况的原因是线程的执行顺序是不可预知的

		fd_set fdWrite;
		FD_ZERO(&fdWrite);
		FD_SET(rsocket, &fdWrite);

		// 接收serverkey
		Sleep(2000);
		recv(rsocket, serverKey, 50, 0);//接受数据

		int nError = -1;
		int nLen = sizeof(int);
		nRet = select(rsocket, 0, &fdWrite, 0, &timeout);
		if (nRet > 0)
		{
			getsockopt(rsocket, SOL_SOCKET, SO_ERROR, (char*)&nError, &nLen);
			if (nError != 0)
				bConnected = FALSE;
			else
				bConnected = TRUE;
		}
		else
			bConnected = FALSE;
	}
	//再设置回阻塞模式
	nFlag = 0;
	ioctlsocket(rsocket, FIONBIO, (unsigned long*)&nFlag);



	//若连接失败则返回
	if (bConnected == FALSE)//与服务器建立连接失败！
		return -4;
	return 1;
}

vector<CString> GetLineInConfigurationINI()
{
	vector<CString> vec;

	HMODULE module = GetModuleHandle(0);

	TCHAR buf[MAX_PATH];
	GetModuleFileName(module, buf, sizeof buf);
	CString strPath = buf;
	strPath.Replace(L"SAV.exe", L"");
	strPath.Append(_T("config.ini"));

	TCHAR szKey[1024] = { 0 };
	CString value = _T("");

	TCHAR szBuffer[65536] = { 0 };
	CString strSectionName = _T("line");

	//获得INI文件指定段的全部键名和键值
	int nBufferSize = GetPrivateProfileSection(strSectionName, szBuffer, 65536, strPath);

	int nItem = 0;
	for (int n = 0, i = 0; n < nBufferSize; n++)
	{
		if (szBuffer[n] == 0)
		{
			szKey[i] = 0;
			CString strKey = szKey;
			vec.push_back(strKey);

			i = 0;

			nItem++;
		}
		else
		{
			szKey[i] = szBuffer[n];

			i++;
		}
	}

	return vec;
}


int ReadInteger(CString szSection, CString szKey, int iDefaultValue, CString m_szFileName)
{
	int iResult = GetPrivateProfileInt(szSection, szKey, iDefaultValue, m_szFileName);
	return iResult;
}
CString ReadString(CString szSection, CString szKey, CString szDefaultValue, CString m_szFileName)
{
	TCHAR* szResult = L"";
	memset(szResult, 0x00, 255);
	GetPrivateProfileString(szSection, szKey, szDefaultValue, szResult, 255, m_szFileName);
	return szResult;
}

/*
vector<CString> GetLineInConfigurationINI()
{
	vector<CString> vec;

	HMODULE module = GetModuleHandle(0);

	//CString m_strFileName;// = _T("C:\\WorkingFolder\\NPRO\\SA\\SAV\\SAV\\SAV\\config.ini");
	TCHAR buf[MAX_PATH];
	GetModuleFileName(module, buf, sizeof buf);


	TCHAR szKey[1024] = { 0 };
	CString strKey = _T("");
	CString strKeyName = _T("");
	CString strKeyValue = _T("");

	TCHAR szBuffer[65536] = { 0 };
	CString strSectionName = _T("line");

	//获得INI文件指定段的全部键名和键值
	int nBufferSize = GetPrivateProfileSection(strSectionName, szBuffer, 65536, m_strFileName);

	int nItem = 0;
	for (int n = 0, i = 0; n < nBufferSize; n++)
	{
		if (szBuffer[n] == 0)
		{
			szKey[i] = 0;
			strKey = szKey;

			strKeyName = strKey.Left(strKey.Find('='));
			strKeyValue = strKey.Mid(strKey.Find('=') + 1);

			pList->InsertItem(nItem, strKeyName);
			pList->SetItemText(nItem, 1, strKeyValue);
			
			i = 0;

			nItem++;
		}
		else
		{
			szKey[i] = szBuffer[n];

			i++;
		}
	}
}
*/