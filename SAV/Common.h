#pragma once
#include <math.h>
#include "malloc.h"
#include <vector>
#include "iphlpapi.h"
#pragma   comment(lib, "Iphlpapi.lib ")



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
}USERINFO;



int ConnectServer(SOCKET &rsocket, char *ip, int port, char *serverKey);

vector<CString> GetLineInConfigurationINI();
