#include "stdafx.h"
#include "SALib.h"

#pragma region ����

extern USERINFO *g_userinfo;
extern int g_userNum;
extern SERVERINFO g_serverinfo;
extern SALib *pDp;
//��Ϸʱ��
extern long gametime;
//��Ϣ�ص�����
extern void Callback_Notify(NOTIFYPARA *pNotifyPara);

CCriticalSection csSingal;	//�ź���

#pragma endregion

SALib::SALib()
{
	// ��ʼ������
	IP = 0;
	IsOnLine = FALSE;
	script = NULL;

	//��ʼ��Ϊδ����״̬
	bExit = TRUE;
	bScriptExit = TRUE;
	bScriptErrorReStart = FALSE;
	bIsReLogin = FALSE;
	IsLogin = FALSE;
	IsDispTalk = FALSE;
	IsDispInfoOnTime = TRUE;
	IsBaiTanOk = FALSE;
	bIsBaiTaning = FALSE;
	maxload = 0;
	MapSeqNo = 1;

	//��������
	nScriptDelay = 50;										//�ű���ʱ��0-250��
	bReLogin = FALSE;										//�Ƿ�����ص�
	nAutoUnlock = FALSE;									//�Զ�����
	IsSafeCodeUnlock = FALSE;								//�Ƿ��ѽ���
	bAutoCapture = FALSE;									//�Զ�׽��
	bAutoEscape = FALSE;									//�Զ�����
	bFightpetDeadEscape = FALSE;							//ս�������Զ�����
	bAutoKNPC = FALSE;										//�Զ�KNPC
	bFullEscape = FALSE;									//��������
	bMakeTeam = FALSE;										//���
	bDuel = FALSE;											//����
	bCallingCard = FALSE;									//��Ƭ
	bTrade = FALSE;											//����
	for (int i = 0; i < 10; i++){
		ZeroMemory(cZDAttack[i], sizeof(cZDAttack[i]));		//ָ�������ĳ���
		ZeroMemory(cLockAttack[i], sizeof(cLockAttack[i]));	//���������ĳ���
		ZeroMemory(cZDEscape[i], sizeof(cZDEscape[i]));		//ָ�����ܵĳ���
	}
	nZDAttackNum = 0;
	nLockAttackNum = 0;
	nZDEscapeNum = 0;
	for (int i = 0; i < 4; i++){
		nAutoUpPoint[i] = 0;
	}
	bAutoEatSYC = FALSE;									//�Զ���������
	bAutoExpNut = FALSE;									//���ǻ۹�
	nEatSYCTime = 0;
	nExpNutTime = 0;
	bAutoPile = FALSE;										//�Զ��ѵ�
	bEatMeat = FALSE;										//�Բ�Ѫ��
	bDiscardMeat = FALSE;									//��û�в�Ѫ���ܵ�Ѫ��
	bRecruitMpPlaceTime = FALSE;							//ƽʱ����
	nLockRidePet = 0;										//�������
	nLockFightPet = 0;										//����ս��
	for (int i = 0; i < 15; i++){
		ZeroMemory(cDiscardLikeItem[i], sizeof(cDiscardLikeItem[i]));		//��������
		ZeroMemory(cDiscardExceptItem[i], sizeof(cDiscardExceptItem[i]));	//����������
	}
	nDiscardLikeItemNum = 0;
	nDiscardExceptItemNum = 0;
	dFirstDelay = 0;				//�״��ӳ�
	dAttackDelay = 0;				//�����ӳ�
	dRMpByBlood = 0;				//��Ѫ����
	ZeroMemory(cCharFirstAction, sizeof(cCharFirstAction));	//�����״ζ���
	ZeroMemory(cCharAction, sizeof(cCharAction));			//����һ�㶯��
	ZeroMemory(cPetFirstAction, sizeof(cPetFirstAction));	//ս���״ζ���
	ZeroMemory(cPetAction, sizeof(cPetAction));				//ս��һ�㶯��
	nCapLevel = 0;											//��׽�ȼ�
	for (int i = 0; i < 5; i++)
		ZeroMemory(cCapPetName[i], sizeof(cCapPetName[i]));	//׽������
	nCapPetNum = 0;
	nCapPetBlood = 0;											//׽��Ѫ��
	nCapCharUseSkill = 0;										//׽��ʱ����ļ��ܺ�׽��Ѫ��
	nCapPetSkill = 1;											//׽��ʱ����ʹ�õļ���,ȱʡ����
	bCapEscapeWhenNoPet = TRUE;									//�Ƿ����ܵ�û��Ҫ����ĳ���ʱ
	recruitblood.id = -1;										//���ﾫ�鲹Ѫ
	ZeroMemory(recruitblood.name, sizeof(recruitblood.name));
	petrecruitblood.skillid = -1;								//���＼�ܲ�Ѫ
	bDeleteChar = FALSE;
}

SALib::~SALib()
{
}

void SALib::Init()
{
	int i, j;
	//��ʼ�������б�
	for (i = 0; i < 2; i++){
		charlist[i].dataplace = 0;
		charlist[i].faceimage = 0;
		ZeroMemory(charlist[i].name, sizeof(charlist[i].name));
		ZeroMemory(charlist[i].place, sizeof(charlist[i].place));
	}

	//��ʼ��װ���ϵľ����б�
	for (i = 0; i < 6; i++){
		magic[i].id = 0;
		magic[i].kubun = 0;
		ZeroMemory(magic[i].name, sizeof(magic[i].name));
		ZeroMemory(magic[i].comment, sizeof(magic[i].comment));
	}
	
	//��ʼ��������ϸ��Ϣ
	for (i = 0; i < 5; i++){
		petdetail[i].no = -1;
		for (j = 0; j < 7; j++){
			ZeroMemory(petdetail[i].oldname, sizeof(petdetail[i].oldname));
			ZeroMemory(petdetail[i].newname, sizeof(petdetail[i].newname));
			petdetail[i].petskill[j].skillid = -1;
			petdetail[i].state = 0;
		}
	}
	
	//��ʼ����Ʒ��Ϣ
	for (i = 0; i < 15; i++){
		ZeroMemory(iteminfo[i].name, sizeof(iteminfo[i].name));
		ZeroMemory(iteminfo[i].comment, sizeof(iteminfo[i].comment));
	}
	
	//��ʼ�����＼����Ϣ
	for (i = 0; i < CHAR_SKILL_NUM; i++){
		charskill[i].useflag = -1;
		ZeroMemory(charskill[i].name, sizeof(charskill[i].name));
	}
	
	//��ʼ���ʼ���ϵ���б�
	for (i = 0; i < EMAIL_NUM; i++){
		ZeroMemory(mailcontactlist[i].charname, sizeof(mailcontactlist[i].charname));
	}
		
	//��ʼgameflag
	charotherinfo.fightpet = -1;
	charotherinfo.menuflg = MENUFLAG;
	charotherinfo.state = -1;//�ǳ�״̬
	ZeroMemory(chardetail.name, sizeof(chardetail.name));
	chardetail.kubun = -1;
	chardetail.uplevelpoint = 0;
	chardetail.fame = 0;
	ZeroMemory(mapinfo.floorname, sizeof(mapinfo.floorname));
}

void SALib::Run(USERINFO *puser)
{
	ASSERT(this);
	char buffer[65500], temp[65500];
	int recvbytes;
	CString szVal, szT, szStr;

	IsLogin = TRUE;
	bExit = FALSE;
	Init();

	CString szMsg;
	NOTIFYPARA para;
	para.nNotityType = NOTIFY_MSG;
	
}

BOOL SALib::lineConnect(SOCKET &rsocket, char *serverKey, USERINFO *puser)
{
	BOOL isConnect = FALSE;
	HOSTENT *lpHostEnt;
	struct in_addr inAddr;
	LPSTR lpaddr;
	char ip[30];
	char serverName[30];
	memset(ip, 0, sizeof(ip));


	strncpy_s(ip, puser->servername, strlen(puser->servername));
	strncpy_s(serverName, puser->servername, strlen(puser->servername));

	lpHostEnt = gethostbyname(ip);
	if (!lpHostEnt)return;
	lpaddr = lpHostEnt->h_addr_list[0];
	memmove(&inAddr, lpaddr, 4);
	sprintf_s(ip, "%d.%d.%d.%d", inAddr.S_un.S_addr & 0xff, (inAddr.S_un.S_addr >> 8) & 0xff, (inAddr.S_un.S_addr >> 16) & 0xff, (inAddr.S_un.S_addr >> 24) & 0xff);
	strcpy_s(g_serverinfo.ip, ip);

	g_serverinfo.port = puser->port;

	char *serverKey = (char*)malloc(150 * sizeof(char));

	strcpy_s(user.charname, "yinwun15");
	strcpy_s(user.password, "dI34286834Y");
	strcpy_s(user.safecode, "123");
	strcpy_s(user.scriptName, "");
	SOCKET socket;
	BOOL isConnect = false;
	//ConnectServer(socket, g_serverinfo.ip, g_serverinfo.port, &*serverKey);


	//���ӷ����
	if (!isConnect) {

		MessageBox(L"A");


	}
	else

	{

		//����runningKey
		CString strtmp(serverKey);
		//AfxMessageBox(strtmp);
		CString str = strtmp.Right(strtmp.GetLength() - 1);
		SASO *so = new SASO(str);
		char *SOKey = so->RunningKey();


		return isConnect;
	}
}



//�ͻ���������ÿ��30�뷢��һ��������Ϣ���Ա��÷����֪���ͻ����������ϣ��ͻ��˷��͵���ϢΪhoge,ս��ʱÿ�غϺ���"????"
int SALib::SendOnlineInfo(char *info)
{
	char buffer[1024];
	int checksum = 0;

	nStartTime = GetTickCount();
	checksum = 0;
	ZeroMemory(buffer, sizeof(buffer));
	checksum += autil.util_mkstring(buffer, info);
	autil.util_mkint(buffer, checksum);
	if (!autil.util_SendMesg(&socket, 87, buffer)){
		IsOnLine = FALSE;
		return SENDMSG_ERROR;
	}
	return SUCCESSFUL;
}


int SALib::CharLogin(int dataplace)
{
	char buffer[8192];
	int checksum = 0;

	//�ºŵ���
	checksum = 0;
	ZeroMemory(buffer, sizeof(buffer));
	checksum += autil.util_mkstring(buffer, charlist[dataplace].name);
	autil.util_mkint(buffer, checksum);
	if (!autil.util_SendMesg(&socket, 77, buffer)){
		IsOnLine = FALSE;
		return SENDMSG_ERROR;
	}
	//if(type==1){//��ȫ����룬�ȴ����ش�����Ϣ
	//	ZeroMemory(buffer,sizeof(buffer));
	//	recvbytes=recv(socket,buffer,sizeof(buffer),0);
	//	if(recvbytes<=0)
	//		return RECVMSG_ERROR;
	//	autil.util_Init();
	//	autil.util_DecodeMessage(raw,buffer);
	//	if(!autil.util_SplitMessage(raw,SEPARATOR))
	//		return SPLITMSG_ERROR;
	//	if(!autil.util_GetFunctionFromSlice(&func, &fieldcount))
	//		return GETFUNC_ERROR;
	//	checksum=0;
	//	if(func==88 && fieldcount==3){
	//		checksum += autil.util_destring(2,result);
	//		checksum += autil.util_destring(3,message);
	//		autil.util_deint(4, &checksumrecv);
	//		if(checksum!=checksumrecv)	
	//			return CHECKSUM_ERROR;
	//		if(strcmp(result,"failed")!=0 && strcmp(message,"Password is wrong")!=0)
	//			return CREATE_NEWCHAR_ERROR;	
	//	}
	//	else
	//		return INVALID_INFO;

	//}
	return SUCCESSFUL;
}