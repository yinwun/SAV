#pragma once
#include <math.h>
#include "malloc.h"
#include "iphlpapi.h"
#pragma   comment(lib, "Iphlpapi.lib ")

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
}USERINFO;

int ConnectServer(SOCKET &rsocket, char *ip, int port, char *serverKey);

