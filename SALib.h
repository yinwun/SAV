#pragma once
#include "Common.h"
#include "Autil.h"
#include "SASO.h"
#include <deque>
#include <stack>

#pragma region Constant

#define STATIC_NPC_NUM				200	//��̬npc����
#define CHAR_SKILL_NUM				30	//���＼����
#define EMAIL_NUM					80	//�ʼ���Ƭ��
#define MENUFLAG					64	//448
#define MAXTALKLENGTH				20


#define SUCCESSFUL					1
#define SENDMSG_ERROR				-2
#define RECVMSG_ERROR				-3
#define CHECKSUM_ERROR				-4
#define SPLITMSG_ERROR				-5
#define GETFUNC_ERROR				-6
#define CDKEY_AND_PWD_ERROR			-7
#define INVALID_INFO				-8
#define GET_ACCOUNT_INFO_ERROR		-9
#define NOT_LOGGED_IN				-10
#define NOACCOUNT					0
#define DELETE_CHAR_ERROR			-1
#define CREATE_NEWCHAR_ERROR		-1
#define LOGIN_ERROR					-1

#pragma endregion


#pragma region Struct
//����
typedef struct {
	int dataplace;
	int faceimage;
	int	level;
	int maxhp;
	int atk;
	int def;
	int quick;
	int charm;
	int dp;
	int earth;
	int water;
	int fire;
	int wind;
	int logincount;
	char name[50];
	char place[50];
}CHARLIST;

//����
typedef struct {
	int id;			//��������װ����λ�ñ�ţ�ͷ0����1������2������3������4��
	int kubun;		//װ���еľ����Ƿ���ã�װ��װ��Ϊ1��ȡ��װ����Ϊ0
	int mp;
	int field;
	int target;
	char name[100];
	char comment[200];
}MAGIC;

//���＼��
typedef struct {
	int skillid;
	int field;
	int target;
	char name[50];
	char comment[100];
}PETSKILL;

//����
typedef struct {
	int no;//���
	int islive;//��������Ϊ0(����)��������Ϊ1
	int image;
	int hp;
	int maxhp;
	int mp;
	int maxmp;
	int exp;
	int nextexp;
	int level;
	int attack;
	int defence;
	int quick;
	int ai;
	int fEarth;
	int fWater;
	int fFire;
	int fWind;
	int slot;
	int changenameflag;
	int transmigration;
	int unknown;
	char oldname[50];
	char newname[50];
	PETSKILL petskill[7];
	///////////////
	int state;		//����״̬��0=��Ϣ��1=ս��|�ȴ���4=�ʼ�	
}PETDETAIL;

//�������
typedef struct {//��Ʒλ��|��Ʒ����|parashow|��ɫ|��Ʒ����|��Ʒͼ����|��ʹ�õĳ���|Ŀ��|����|��־|�𻵳̶�|��������|����|itemlevel
	char name[50];			//���ֲ�Ϊ������Ʒ������û����Ʒ
	char paramshow[50];
	int color;
	char comment[100];
	int imgno;
	int ableusefield;
	int target;
	int level;
	int flg;		//������(0),�ʼ�(1)����ĳ��ϳ�(2)���ѵ�(4)��
	char damagecrushe[50];
	int pilenums;
	char element[50];
	int itemlevel;
	char unknown[50];
}ITEMINFO;

//���＼��
typedef struct {
	int useflag;
	int identity;
	int target;
	int kind;
	int icon;
	int costmp;
	int level;
	char name[50];
	char comment[100];
}CHARSKILL;

//������ϸ
typedef struct {
	int kubun;
	int hp;
	int maxhp;
	int mp;
	int maxmp;
	int vital;
	int str;
	int tough;
	int dex;
	int exp;
	int nextexp;
	int level;
	int attack;
	int defence;
	int fQuick;
	int fCharm;
	int fLuck;
	int fEarth;
	int fWater;
	int fFire;
	int fWind;
	int gold;
	int indexofeqtitle;
	int dp;
	int transmigration;
	int ridepet;		//��˳�����,�����Ϊ-1
	int learnride;
	int faceimg;
	int unknown;
	char name[50];
	char owntitle[50];
	/////////////////////
	int uplevelpoint;
	int fame;			//����
}CHARDETAIL;

//�ʼ�
typedef struct {
	int use;
	char charname[50];
	int level;
	int dp;
	int online;			//����Ϊ0������Ϊ4
	int graphicsno;
	int transmigration;
	int unknown;
}MAILCONTACTLIST;

//��Ϸ״̬
typedef struct {
	int charid;		//������
	int time;		//����ʱ��
	int fightpet;	//ս����,//��ս��Ϊ-1,��ս��Ϊ����
	int menuflg;	//�˵����
	int x;			//���ﵱǰλ��
	int y;
	int direction;	//���﷽��
	int state;		//��Ϸ״̬��-1�ǳ���0ƽʱ��1ս��
	int round;		//ս���غ���
}CHAROTHERINFO;

//��ͼ��Ϣ
typedef struct {
	int floor;
	int x1;
	int y1;
	int x2;
	int y2;
	int unknown1;
	int unknown2;
	int unknown3;
	char floorname[50];
	////////////////��ͼ�л��¼����
	int seqno;
}MAPINFO;

//���ﾫ�鲹Ѫ
typedef struct {
	int id;			//���������
	char name[50];	//���������
	int val;		//��Ѫ�趨����
}RECRUITBLOOD;

//���ﲹѪ
typedef struct {
	int skillid;	//����id
	int val;		//��Ѫ�趨����
}PETRECRUITBLOOD;

#pragma endregion

class SALib
{
public:
	SALib();
	~SALib();

	CAutil autil;
	SOCKET socket;

	void SALib::Run(USERINFO *puser);
	void Init();
	BOOL SALib::lineConnect(SOCKET &rsocket, char *serverKey, USERINFO *puser);
	int SendOnlineInfo(char *info);
	int CharLogin(int dataplace);

	USERINFO user;						//�ʺ���Ϣ
	CHARLIST charlist[2];						//�����б�
	MAGIC magic[6];								//�������ϵľ�����Ϣ
	PETDETAIL petdetail[5];						//������ϸ��Ϣ
	ITEMINFO iteminfo[15];						//��Ʒ��Ϣ
	CHARSKILL charskill[CHAR_SKILL_NUM];		//���＼����Ϣ
	MAILCONTACTLIST mailcontactlist[EMAIL_NUM];	//�ʼ���ϵ���б�
	CHAROTHERINFO charotherinfo;		//�����������Ϣ	
	CHARDETAIL chardetail;				//������ϸ��Ϣ
	MAPINFO mapinfo;					//��ǰ��ͼ����Ϣ

	BOOL IsOnLine;						//�Ƿ�����
	BOOL IsLogin;						//�����Ƿ����ڵ�¼��
	BOOL bExit;							//����Ϸ�߳���ֹ
	BOOL bScriptExit;					//�ýű��߳���ֹ
	int IP;								//ָ�������
	CString *script;					//����ű�
	BOOL bIsReLogin;					//�Ƿ�ս����˵�¼���صǣ������ڿ��ƽű�����ת
	BOOL bScriptErrorReStart;		//�ű�������������
	BOOL IsDispTalk;					//�Ƿ���ʾ˵������
	BOOL IsDispInfoOnTime;				//�Ƿ���ʾʵʱ������Ϣ
	BOOL IsBaiTanOk;					//�����̲��ť�󣬷�����Ƿ񷵻�ȷ����Ϣ
	BOOL bIsBaiTaning;					//�Ƿ������ڰ�̲�У��ں�̲����Ϊtrue��ȡ����̲����Ϊfalse 
	int maxload;						//�����
	int MapSeqNo;						//��ͼ�л��¼����

	int  nScriptDelay;				//�ű���ʱ��0-250��
	BOOL bReLogin;					//�Ƿ�����ص�
	BOOL nAutoUnlock;				//�Զ�����
	BOOL IsSafeCodeUnlock;			//�Ƿ��ѽ���
	BOOL bAutoCapture;				//�Զ�׽��
	BOOL bAutoEscape;				//�Զ�����
	BOOL bAutoKNPC;					//�Զ�KNPC
	BOOL bFullEscape;				//��������
	BOOL bFightpetDeadEscape;		//ս�������Զ�����
	BOOL bMakeTeam;					//���
	BOOL bDuel;						//����
	BOOL bCallingCard;				//��Ƭ
	BOOL bTrade;					//����
	int nAutoUpPoint[4];			//�Զ��ӵ㣬1000����Ϊ������1000����Ϊ������2000����Ϊ������3000����Ϊ�ٶ�
	BOOL bDeleteChar;				//�ص�ʱ�Ƿ�ɾ���ʺ�

									//ս��
	char cZDAttack[10][50];			//ָ�������ĳ���
	int nZDAttackNum;				//ָ�������ĳ���ĳ�������
	char cLockAttack[10][50];		//���������ĳ���
	int nLockAttackNum;
	char cZDEscape[10][50];			//ָ�����ܵĳ���
	int nZDEscapeNum;

	//ƽʱ
	BOOL bAutoEatSYC;				//�Զ���������
	int	nEatSYCTime;				//�ϴγ������ݵ�ʱ��
	BOOL bAutoExpNut;				//���ǻ۹�
	int nExpNutTime;				//�ϴγ��ǻ۹���ʱ��
	BOOL bAutoPile;					//�Զ��ѵ�
	BOOL bEatMeat;					//�Բ�Ѫ��
	BOOL bDiscardMeat;				//��û�в�Ѫ���ܵ�Ѫ��
	BOOL bRecruitMpPlaceTime;		//ƽʱ����
	int nLockRidePet;				//�������
	int nLockFightPet;				//����ս��
	char cDiscardLikeItem[15][50];	//��������
	char cDiscardExceptItem[15][50];//����������
	int nDiscardLikeItemNum;
	int nDiscardExceptItemNum;
	double dFirstDelay;				//�״��ӳ�
	double dAttackDelay;			//�����ӳ�
	double dRMpByBlood;				//��Ѫ����
	char cCharFirstAction[50];		//�����״ζ���
	char cCharAction[50];			//����һ�㶯��
	char cPetFirstAction[50];		//ս���״ζ���
	char cPetAction[50];			//ս��һ�㶯��
	int nCapLevel;					//��׽�ȼ�
	char cCapPetName[5][50];		//׽������
	int nCapPetNum;					//��׽���������ʹ�ã�׽������
	int nCapPetBlood;				//׽��Ѫ��
	int nCapCharUseSkill;			//׽��ʱ����ļ��ܺ�׽��Ѫ��
	int nCapPetSkill;				//׽��ʱ����ʹ�õļ���
	BOOL bCapEscapeWhenNoPet;		//�Ƿ����ܵ�û��Ҫ����ĳ���ʱ
	RECRUITBLOOD recruitblood;		//�������ﾫ�鲹Ѫ����(����սʱ��ƽʱ)
	PETRECRUITBLOOD petrecruitblood;		//���＼�ܲ�Ѫ

											//ϵͳ
	DWORD nStartTime;					//����������Ϣ��ʱ��
	DWORD nRecvTime;					//����������Ϣ��ʱ��


};