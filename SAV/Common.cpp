#include "stdafx.h"
#include "Common.h"

int ConnectServer(SOCKET &rsocket, char *ip, int port, char *serverKey)
{
	int nRet = -1;
	BOOL bConnected = FALSE;

	rsocket = socket(AF_INET, SOCK_STREAM, 0);
	//�׽��ִ���ʧ�ܣ�
	if (rsocket == INVALID_SOCKET)
		return -1;
	sockaddr_in servAddr;
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(port);
	servAddr.sin_addr.s_addr = inet_addr(ip);

	//���ý��ճ�ʱʱ��Ϊ35��
	int nTimeout = 35000;
	if (setsockopt(rsocket, SOL_SOCKET, SO_RCVTIMEO, (char*)&nTimeout, sizeof(nTimeout)) == SOCKET_ERROR)
		return -2;
	//�ѵ�ǰ�׽�����Ϊ������ģʽ
	unsigned long nFlag = 1;
	nRet = ioctlsocket(rsocket, FIONBIO, (unsigned long*)&nFlag);
	if (nRet == SOCKET_ERROR)//�ѵ�ǰ�׽�����Ϊ������ģʽʧ��!
		return -3;
	//������ģʽ��ִ��I/O����ʱ��Winsock�������������ز���������Ȩ������ģʽʹ�������Ƚϸ��ӣ�
	//��Ϊ������û��������ɾͽ��з��أ��᲻�ϵط���WSAEWOULDBLOCK����
	if (connect(rsocket, (struct sockaddr *)&servAddr, sizeof(servAddr)) == SOCKET_ERROR) {
		struct timeval timeout = { 0 };
		timeout.tv_sec = 10;	//���ӳ�ʱʱ��Ϊ10��,��ֵ��С����ɶ��߳�ͬʱ���ӷ����ʱ���޷��������Ӷ�ͨ��ʧ��
		timeout.tv_usec = 0;	//�����������ԭ�����̵߳�ִ��˳���ǲ���Ԥ֪��

		fd_set fdWrite;
		FD_ZERO(&fdWrite);
		FD_SET(rsocket, &fdWrite);

		// ����serverkey
		Sleep(2000);
		recv(rsocket, serverKey, 50, 0);//��������

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
	//�����û�����ģʽ
	nFlag = 0;
	ioctlsocket(rsocket, FIONBIO, (unsigned long*)&nFlag);



	//������ʧ���򷵻�
	if (bConnected == FALSE)//���������������ʧ�ܣ�
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

	//���INI�ļ�ָ���ε�ȫ�������ͼ�ֵ
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

/********************************************************************************
* Function Type	:	public
* Description	:	��ȡ��ǰʱ����ַ���,�磺2003-10-01 12:00:00
*********************************************************************************/
CString GetCurTimeString()
{
	time_t tNow = time(NULL);
	CTime cTime(tNow);
	return cTime.Format(_T("%Y-%m-%d %H:%M:%S"));
}

/********************************************************************************
* Function Type	:	Global
* Parameter		:	lpszFormat	-	Ҫ��¼����־����
* Return Value	:	�޷���ֵ
* Description	:	��¼��־
*********************************************************************************/
CCriticalSection f_CSFor_DbgLog;
void DbgLog(LPCSTR lpszFormat,...)
{
	// ��ʽ��
	f_CSFor_DbgLog.Lock();
	char szLogBuf[1024 * 4] = { 0 };
	char *p = szLogBuf;
	*p = '[';
	p++;
	CString csDate = GetCurTimeString();
	int nLen = csDate.GetLength();
	//strcpy_s(p, nLen + 1, (LPCSTR)csDate);
	memcpy(p, csDate, csDate.GetLength());
	p += nLen;
	*p = ']';
	p++;
	*p = ' ';
	p++;

	va_list  va;
	//va_start(va, lpszFormat);
	nLen = sizeof(szLogBuf) / 2 - (int)(p - szLogBuf);
	vsprintf_s(p, nLen, lpszFormat, va);
	va_end(va);
	char buf[1024*4]={0};
	//WideCharToMultiByte(CP_ACP,0,szLogBuf,-1,buf,sizeof(buf),NULL,NULL);
	WriteDataToFile("log.txt", szLogBuf, strlen(szLogBuf), "ab+", 0);
	f_CSFor_DbgLog.Unlock();
}

/********************************************************************************
* Function Type	:	Global
* Parameter		:	filename		-	�ļ���
*					data			-	Ҫ���������
*					mode			-	�ļ��򿪵�ģʽ
*					size			-	���ݴ�С
*					nStartPos		-	�ļ���ʼλ��
* Return Value	:	>=0				-	д���ļ��Ĵ�С
*					-1				-	д����ʧ��
* Description	:	�������ݵ��ļ�
*********************************************************************************/
int WriteDataToFile(LPCSTR filename, char* data, long size, LPCSTR mode, int nStartPos/*=-1*/)
{
	//ASSERT ( filename && strlen(filename) > 0 );
	FILE *fp;
	long retval;
	errno_t err;
	err = fopen_s(&fp, filename, mode);
	if (err == 0)
	{
		if (nStartPos >= 0)
		{
			if (fseek(fp, nStartPos, SEEK_SET) != 0)
				return -1;
		}
		retval = (long)fwrite(data, sizeof(UCHAR), size, fp);
		fclose(fp);
		if (retval != size)
		{
			return -1;
		}
		else 	return retval;
	}
	else
	{
		return -1;
	}
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

	//���INI�ļ�ָ���ε�ȫ�������ͼ�ֵ
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