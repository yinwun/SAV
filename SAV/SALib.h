#pragma once
#include "Common.h"
#include "Autil.h"
#include "SASO.h"
#include <deque>
#include <stack>

#pragma region Constant

#define STATIC_NPC_NUM				200	//静态npc人数
#define CHAR_SKILL_NUM				30	//人物技能数
#define EMAIL_NUM					80	//邮件名片数
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
//人物
typedef struct{
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

//精灵
typedef struct{
	int id;			//精灵所在装备的位置编号（头0，身1，武器2，左饰3，右饰4）
	int kubun;		//装备中的精灵是否可用，装上装备为1，取下装备后为0
	int mp;
	int field;
	int target;
	char name[100];
	char comment[200];
}MAGIC;

//宠物技能
typedef struct{
	int skillid;
	int field;
	int target;
	char name[50];
	char comment[100];
}PETSKILL;

//宠物
typedef struct{
	int no;//编号
	int islive;//不在身上为0(丢出)，在身上为1
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
	int state;		//宠物状态，0=休息，1=战斗|等待，4=邮件	
}PETDETAIL;

//背包物件
typedef struct{//物品位置|物品名称|parashow|颜色|物品描述|物品图像编号|能使用的场合|目标|级别|标志|损坏程度|叠加数量|类型|itemlevel
	char name[50];			//名字不为空有物品，否则没有物品
	char paramshow[50];
	int color;
	char comment[100];
	int imgno;
	int ableusefield;
	int target;
	int level;
	int flg;		//不允许(0),邮寄(1)，从某物合成(2)，堆叠(4)等
	char damagecrushe[50];
	int pilenums;
	char element[50];
	int itemlevel;
	char unknown[50];
}ITEMINFO;

//人物技能
typedef struct{
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

//人物详细
typedef struct{
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
	int ridepet;		//骑乘宠物编号,无骑宠为-1
	int learnride;
	int faceimg;
	int unknown;
	char name[50];
	char owntitle[50];
	/////////////////////
	int uplevelpoint;
	int fame;			//声望
}CHARDETAIL;

//邮件
typedef struct{
	int use;
	char charname[50];
	int level;
	int dp;
	int online;			//下线为0，上线为4
	int graphicsno;
	int transmigration;
	int unknown;
}MAILCONTACTLIST;

//游戏状态
typedef struct{
	int charid;		//人物编号
	int time;		//登入时间
	int fightpet;	//战宠编号,//无战宠为-1,有战宠为其编号
	int menuflg;	//菜单旗标
	int x;			//人物当前位置
	int y;
	int direction;	//人物方向
	int state;		//游戏状态，-1登出，0平时，1战斗
	int round;		//战斗回合数
}CHAROTHERINFO;

//地图信息
typedef struct{
	int floor;
	int x1;
	int y1;
	int x2;
	int y2;
	int unknown1;
	int unknown2;
	int unknown3;
	char floorname[50];
	////////////////地图切换事件编号
	int seqno;
}MAPINFO;

//人物精灵补血
typedef struct{
	int id;			//精灵的索引
	char name[50];	//精灵的名称
	int val;		//补血设定界限
}RECRUITBLOOD;

//宠物补血
typedef struct{
	int skillid;	//技能id
	int val;		//补血设定界限
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

	USERINFO user;						//帐号信息
	CHARLIST charlist[2];						//人物列表
	MAGIC magic[6];								//人物身上的精灵信息
	PETDETAIL petdetail[5];						//宠物详细信息
	ITEMINFO iteminfo[15];						//物品信息
	CHARSKILL charskill[CHAR_SKILL_NUM];		//人物技能信息
	MAILCONTACTLIST mailcontactlist[EMAIL_NUM];	//邮件联系人列表
	CHAROTHERINFO charotherinfo;		//人物的其它信息	
	CHARDETAIL chardetail;				//人物详细信息
	MAPINFO mapinfo;					//当前地图的信息

	BOOL IsOnLine;						//是否在线
	BOOL IsLogin;						//人物是否正在登录中
	BOOL bExit;							//让游戏线程终止
	BOOL bScriptExit;					//让脚本线程终止
	int IP;								//指令计数器
	CString *script;					//保存脚本
	BOOL bIsReLogin;					//是否刚进行了登录（重登），用于控制脚本的跳转
	BOOL bScriptErrorReStart;		//脚本出错重新运行
	BOOL IsDispTalk;					//是否显示说话内容
	BOOL IsDispInfoOnTime;				//是否显示实时更新信息
	BOOL IsBaiTanOk;					//点击摆滩按钮后，服务端是否返回确认信息
	BOOL bIsBaiTaning;					//是否正处于摆滩中，摆好滩后置为true，取消摆滩后置为false 
	int maxload;						//最大负重
	int MapSeqNo;						//地图切换事件编号

	int  nScriptDelay;				//脚本延时（0-250）
	BOOL bReLogin;					//是否断线重登
	BOOL nAutoUnlock;				//自动解锁
	BOOL IsSafeCodeUnlock;			//是否已解锁
	BOOL bAutoCapture;				//自动捉宠
	BOOL bAutoEscape;				//自动逃跑
	BOOL bAutoKNPC;					//自动KNPC
	BOOL bFullEscape;				//落马逃跑
	BOOL bFightpetDeadEscape;		//战宠死亡自动逃跑
	BOOL bMakeTeam;					//组队
	BOOL bDuel;						//决斗
	BOOL bCallingCard;				//名片
	BOOL bTrade;					//交易
	int nAutoUpPoint[4];			//自动加点，1000以下为体力，1000以上为腕力，2000以上为耐力，3000以上为速度
	BOOL bDeleteChar;				//重登时是否删除帐号

	//战斗
	char cZDAttack[10][50];			//指定攻击的宠物
	int nZDAttackNum;				//指定攻击的宠物的宠物数量
	char cLockAttack[10][50];		//锁定攻击的宠物
	int nLockAttackNum;
	char cZDEscape[10][50];			//指定逃跑的宠物
	int nZDEscapeNum;

	//平时
	BOOL bAutoEatSYC;				//自动吃鱼鳃草
	int	nEatSYCTime;				//上次吃鱼鳃草的时间
	BOOL bAutoExpNut;				//吃智慧果
	int nExpNutTime;				//上次吃智慧果的时间
	BOOL bAutoPile;					//自动堆叠
	BOOL bEatMeat;					//吃补血肉
	BOOL bDiscardMeat;				//丢没有补血功能的血肉
	BOOL bRecruitMpPlaceTime;		//平时补气
	int nLockRidePet;				//锁定骑宠
	int nLockFightPet;				//锁定战宠
	char cDiscardLikeItem[15][50];	//丢弃包含
	char cDiscardExceptItem[15][50];//丢弃不包含
	int nDiscardLikeItemNum;
	int nDiscardExceptItemNum;
	double dFirstDelay;				//首次延迟
	double dAttackDelay;			//攻击延迟
	double dRMpByBlood;				//嗜血补气
	char cCharFirstAction[50];		//人物首次动作
	char cCharAction[50];			//人物一般动作
	char cPetFirstAction[50];		//战宠首次动作
	char cPetAction[50];			//战宠一般动作
	int nCapLevel;					//捕捉等级
	char cCapPetName[5][50];		//捉宠名称
	int nCapPetNum;					//和捉宠名称配合使用，捉宠数量
	int nCapPetBlood;				//捉宠血量
	int nCapCharUseSkill;			//捉宠时人物的技能和捉宠血量
	int nCapPetSkill;				//捉宠时宠物使用的技能
	BOOL bCapEscapeWhenNoPet;		//是否逃跑当没有要捕获的宠物时
	RECRUITBLOOD recruitblood;		//保存人物精灵补血设置(包括战时和平时)
	PETRECRUITBLOOD petrecruitblood;		//宠物技能补血
	
	//系统
	DWORD nStartTime;					//发送连接信息计时器
	DWORD nRecvTime;					//接收连接信息计时器

	
};

