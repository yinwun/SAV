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