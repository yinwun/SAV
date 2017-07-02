#include "stdafx.h"
#include "SALib.h"

#pragma region 变量

extern USERINFO *g_userinfo;
extern int g_userNum;
extern SALib *pDp;
//游戏时间
extern long gametime;
//消息回调函数
extern void Callback_Notify(NOTIFYPARA *pNotifyPara);

CCriticalSection csSingal;	//信号量

#pragma endregion

SALib::SALib()
{
	// 初始化变量
	IP = 0;
	IsOnLine = FALSE;
	script = NULL;

	//初始化为未运行状态
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

	//参数设置
	nScriptDelay = 50;										//脚本延时（0-250）
	bReLogin = FALSE;										//是否断线重登
	nAutoUnlock = FALSE;									//自动解锁
	IsSafeCodeUnlock = FALSE;								//是否已解锁
	bAutoCapture = FALSE;									//自动捉宠
	bAutoEscape = FALSE;									//自动逃跑
	bFightpetDeadEscape = FALSE;							//战宠死亡自动逃跑
	bAutoKNPC = FALSE;										//自动KNPC
	bFullEscape = FALSE;									//落马逃跑
	bMakeTeam = FALSE;										//组队
	bDuel = FALSE;											//决斗
	bCallingCard = FALSE;									//名片
	bTrade = FALSE;											//交易
	for (int i = 0; i < 10; i++) {
		ZeroMemory(cZDAttack[i], sizeof(cZDAttack[i]));		//指定攻击的宠物
		ZeroMemory(cLockAttack[i], sizeof(cLockAttack[i]));	//锁定攻击的宠物
		ZeroMemory(cZDEscape[i], sizeof(cZDEscape[i]));		//指定逃跑的宠物
	}
	nZDAttackNum = 0;
	nLockAttackNum = 0;
	nZDEscapeNum = 0;
	for (int i = 0; i < 4; i++) {
		nAutoUpPoint[i] = 0;
	}
	bAutoEatSYC = FALSE;									//自动吃鱼鳃草
	bAutoExpNut = FALSE;									//吃智慧果
	nEatSYCTime = 0;
	nExpNutTime = 0;
	bAutoPile = FALSE;										//自动堆叠
	bEatMeat = FALSE;										//吃补血肉
	bDiscardMeat = FALSE;									//丢没有补血功能的血肉
	bRecruitMpPlaceTime = FALSE;							//平时补气
	nLockRidePet = 0;										//锁定骑宠
	nLockFightPet = 0;										//锁定战宠
	for (int i = 0; i < 15; i++) {
		ZeroMemory(cDiscardLikeItem[i], sizeof(cDiscardLikeItem[i]));		//丢弃包含
		ZeroMemory(cDiscardExceptItem[i], sizeof(cDiscardExceptItem[i]));	//丢弃不包含
	}
	nDiscardLikeItemNum = 0;
	nDiscardExceptItemNum = 0;
	dFirstDelay = 0;				//首次延迟
	dAttackDelay = 0;				//攻击延迟
	dRMpByBlood = 0;				//嗜血补气
	ZeroMemory(cCharFirstAction, sizeof(cCharFirstAction));	//人物首次动作
	ZeroMemory(cCharAction, sizeof(cCharAction));			//人物一般动作
	ZeroMemory(cPetFirstAction, sizeof(cPetFirstAction));	//战宠首次动作
	ZeroMemory(cPetAction, sizeof(cPetAction));				//战宠一般动作
	nCapLevel = 0;											//捕捉等级
	for (int i = 0; i < 5; i++)
		ZeroMemory(cCapPetName[i], sizeof(cCapPetName[i]));	//捉宠名称
	nCapPetNum = 0;
	nCapPetBlood = 0;											//捉宠血量
	nCapCharUseSkill = 0;										//捉宠时人物的技能和捉宠血量
	nCapPetSkill = 1;											//捉宠时宠物使用的技能,缺省防御
	bCapEscapeWhenNoPet = TRUE;									//是否逃跑当没有要捕获的宠物时
	recruitblood.id = -1;										//人物精灵补血
	ZeroMemory(recruitblood.name, sizeof(recruitblood.name));
	petrecruitblood.skillid = -1;								//宠物技能补血
	bDeleteChar = FALSE;
}

SALib::~SALib()
{
}

void SALib::Init()
{
	int i, j;
	//初始化人物列表
	for (i = 0; i < 2; i++) {
		charlist[i].dataplace = 0;
		charlist[i].faceimage = 0;
		ZeroMemory(charlist[i].name, sizeof(charlist[i].name));
		ZeroMemory(charlist[i].place, sizeof(charlist[i].place));
	}

	//初始化装备上的精灵列表
	for (i = 0; i < 6; i++) {
		magic[i].id = 0;
		magic[i].kubun = 0;
		ZeroMemory(magic[i].name, sizeof(magic[i].name));
		ZeroMemory(magic[i].comment, sizeof(magic[i].comment));
	}

	//初始化宠物详细信息
	for (i = 0; i < 5; i++) {
		petdetail[i].no = -1;
		for (j = 0; j < 7; j++) {
			ZeroMemory(petdetail[i].oldname, sizeof(petdetail[i].oldname));
			ZeroMemory(petdetail[i].newname, sizeof(petdetail[i].newname));
			petdetail[i].petskill[j].skillid = -1;
			petdetail[i].state = 0;
		}
	}

	//初始化物品信息
	for (i = 0; i < 15; i++) {
		ZeroMemory(iteminfo[i].name, sizeof(iteminfo[i].name));
		ZeroMemory(iteminfo[i].comment, sizeof(iteminfo[i].comment));
	}

	//初始化人物技能信息
	for (i = 0; i < CHAR_SKILL_NUM; i++) {
		charskill[i].useflag = -1;
		ZeroMemory(charskill[i].name, sizeof(charskill[i].name));
	}

	//初始化邮件联系人列表
	for (i = 0; i < EMAIL_NUM; i++) {
		ZeroMemory(mailcontactlist[i].charname, sizeof(mailcontactlist[i].charname));
	}

	//初始gameflag
	charotherinfo.fightpet = -1;
	charotherinfo.menuflg = MENUFLAG;
	charotherinfo.state = -1;//登出状态
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
	char *serverKey = (char*)malloc(150 * sizeof(char));

	lineConnect(socket, &*serverKey, puser);
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

	
	/*strncpy_s(ip, puser->servername, strlen(puser->servername));
	strncpy_s(serverName, puser->servername, strlen(puser->servername));*/

	

	lpHostEnt = gethostbyname(ip);
	if (!lpHostEnt) return false;
	lpaddr = lpHostEnt->h_addr_list[0];
	memmove(&inAddr, lpaddr, 4);
	sprintf_s(ip, "%d.%d.%d.%d", inAddr.S_un.S_addr & 0xff, (inAddr.S_un.S_addr >> 8) & 0xff, (inAddr.S_un.S_addr >> 16) & 0xff, (inAddr.S_un.S_addr >> 24) & 0xff);
	//strcpy_s(g_serverinfo.ip, "9065");

	//g_serverinfo.port = puser->port;
	strcpy_s(user.charname, "yinwun15");
	strcpy_s(user.password, "dI34286834Y");
	strcpy_s(user.safecode, "123");
	strcpy_s(user.scriptName, "");
	isConnect = ConnectServer(socket, "116.10.184.141", 9065, &*serverKey);


	//连接服务端
	if (!isConnect) {

		AfxMessageBox("A");


	}
	else

	{

		//生成runningKey
		CString strtmp(serverKey);
		//AfxMessageBox(strtmp);
		CString str = strtmp.Right(strtmp.GetLength() - 1);
		SASO *so = new SASO(str);
		char *SOKey = so->RunningKey();

		AfxMessageBox(SOKey);
		return isConnect;
	}
	

	return isConnect;
}

//客户端向服务端每隔30秒发送一次在线信息，以便让服务端知道客户端仍在线上，客户端发送的信息为hoge,战斗时每回合后发送"????"
int SALib::SendOnlineInfo(char *info)
{
	char buffer[1024];
	int checksum = 0;

	nStartTime = GetTickCount();
	checksum = 0;
	ZeroMemory(buffer, sizeof(buffer));
	checksum += autil.util_mkstring(buffer, info);
	autil.util_mkint(buffer, checksum);
	if (!autil.util_SendMesg(&socket, 87, buffer)) {
		IsOnLine = FALSE;
		return SENDMSG_ERROR;
	}
	return SUCCESSFUL;
}

int SALib::CharLogin(int dataplace)
{
	char buffer[8192];
	int checksum = 0;

	//新号登入
	checksum = 0;
	ZeroMemory(buffer, sizeof(buffer));
	checksum += autil.util_mkstring(buffer, charlist[dataplace].name);
	autil.util_mkint(buffer, checksum);
	if (!autil.util_SendMesg(&socket, 77, buffer)) {
		IsOnLine = FALSE;
		return SENDMSG_ERROR;
	}
	//if(type==1){//安全码登入，等待返回错误信息
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