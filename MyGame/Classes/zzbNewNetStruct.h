//
//  zzbNewNetStruct.h
//  GAME2
//
//   Created by spf on 14-7-21
//
//

#ifndef __GAME2__zzbNewNetStruct__
#define __GAME2__zzbNewNetStruct__

#include <iostream>
#include "cocos2d.h"
//#include "DBMgr.h"


//((const char*){CWebsiteInfoPro::sharedWebsiteInfoProcess()->GetWebFromId(1).c_str()})//服务器地址

USING_NS_CC;

typedef struct netNewEventNameInf
{
	int m_eventType;
	char m_eventName[64];
	char m_eventHead[24];
    char m_eventCName[64];//hsx 请求名字
}NETNEWEVENTNAMEINF;
/*
 net define
 */
enum
{
    NET_RETURN_SUCC = 0,
    
    NET_RETURN_FAILER = 1
};
enum
{
    NET_EVENT_DRAWCARD,//hsx 抽卡 20140331
    NET_EVENT_LOGIN,//登入
    NET_EVENT_TEAMLIST,//保存编队信息
    NET_EVENT_UPDATE_CARD_INFO,
    NET_EVENT_APPLY_ADDFRIEND,//申请添加好友
    NET_EVENT_AGREE_ADDFRIEND,//同意添加好友
    NET_EVENT_REFUSE_ADDFRIEND,//拒绝添加好友
    NET_EVENT_DELETE_FRIEND, //删除好友
    NET_EVENT_SEND_MESSAGE,  //发送私信
    NET_EVENT_GET_FRIEND_LIST, //获取好友列表
    NET_EVENT_GET_FRIEND_APPLY_LIST,//获取好友申请列表
    NET_EVENT_GET_FRIEND_MSG,//获取未读好友消息
    NET_EVENT_UPDATE_FRIEND_MSG_STATE,//更新私信消息状态
    NET_EVENT_SEARCH_FRIEND_ID,//搜索好友
    NET_EVENT_GET_RECOMMEN_LIST,//获取推荐好友
    NET_EVENT_SEND_WORLD_MSG,  //发送世界消息
    NET_EVENT_REFRESH_WORLD_MSG,//刷新世界消息
    NET_EVENT_UPDATE_USER_NAME,//修改用户名
    NET_EVENT_UPDATE_USER_STAMINA,//修改体力
    NET_EVENT_BOUND_USERID_TO_OTHERID,//绑定其他账号
    NET_EVENT_GET_PROPSHOP_LIST,//获取商店道具列表
    NET_EVENT_BUYPROPS,  //购买道具
    NET_EVENT_BATTLE_BEFORE,//战前组战好友
    NET_EVENT_BATTLE_AFTER,//战后结果
    NET_EVENT_BATTLE_REVIVE,//战后复活
    NET_EVENT_BATTLE_WORLD_BOSS,//世界boss 伤害
    NET_EVENT_GET_RANK_WORLD_BOSS,//获取世界boss 排行榜
    NET_EVENT_SAVE_TAKE_OUT_CARD,//保存抽卡结果
    NET_EVENT_GET_ITEM_BY_TYPE,//获取道具列表
    NET_EVENT_SAVE_ITEM,//保存道具
    NET_EVENT_GET_ITEM_BAG_NUM,//获取道具所占用格子数
    NET_EVENT_REFRESH_FORMLATION,//刷新阵型
    NET_EVENT_EVOLUTION_CARD,//进化卡牌
    NET_EVENT_UPGRADE_CARD,//升级卡牌
    NET_EVENT_SKILL_UPGRADE,//技能升级
    NET_EVENT_GET_REGISTRATION,//得到签到信息
    NET_EVENT_SAVE_REGISTRATION,//保存签到信息
    NET_NEW_EVENT_NR
};

struct _netNewEventStructBase:public Object
{
	int m_eventType;
	virtual bool execute(){return false;}
};

struct _netNewSendEventBase : public _netNewEventStructBase{
	//生成需要发送的字段,头和尾巴都不需要生成
	virtual std::string generateContentStr()=0;
    //发送的完整消息
	std::string generateSendStr();
};

//接收消息的基类
struct _netNewRecvEventBase : public _netNewEventStructBase
{
	_netNewRecvEventBase():m_retCode(NET_RETURN_SUCC){}
	static _netNewRecvEventBase* create(const int& nEventType,const std::string&receiveCommand);
    
    
	static std::string truncateCommandHeaderStr(std::string commanstr);//去掉问号之前的东西
    
	virtual bool init()
    {
		m_retCode = NET_RETURN_SUCC;
		if(m_paramsStr.size() <= 0)
			return true;
        int value = parseNumberAfterEqualFromInstruction("Info","info");
        if(value == 1)
			return true;
        
        m_retCode = value;
		return isRight();
	}
    
	virtual bool isRight()
    {
		return m_retCode == NET_RETURN_SUCC;
	}
    
    
	std::string parseStrAfterEqualFromInstruction(const std::string& Maxkey,const std::string& key);
	int parseNumberAfterEqualFromInstruction(const std::string& Maxkey,const std::string& key);
	float parseFloatAfterEqualFromInstruction(const std::string& Maxkey,const std::string& key);
	std::string parseHasEqualInstructionKeyname(const std::string& key);
    
	void parseAllParams(const std::string&str);
   // std::map<std::string, std::string> m_paramsStr;
    std::map<std::string, std::map<std::string, std::string>> m_paramsStr;
	int m_retCode;
};


struct _netNewSendLogin: public _netNewSendEventBase
{
    virtual std::string generateContentStr()
    {
        //app版 uin要小于零sessionId 传的是验证码
        //其他平台需要另外添加
        char buffer[127] = {0};
        
#ifdef AppVersionIsIOS
      //sprintf(buffer, "uin=%d&sessionId=%s&type=app&platform=AppStore&version=1.0",CUserDate::getInstance()->getUserId(),CUserDate::getInstance()->getUserAuthcode().c_str());
        // 86 E5BB082779311623EC0154CC14A20BCC
        //userId=91   authcode=FCCDC380D169CA4501BC32944BC294FC
        sprintf(buffer, "uin=86&sessionId=%s&type=app&platform=AppStore&version=1.0","E5BB082779311623EC0154CC14A20BCC");
       // sprintf(buffer, "uin=91&sessionId=%s&type=app&platform=AppStore&version=1.0","FCCDC380D169CA4501BC32944BC294FC");
#endif
        return buffer;
    }
};


struct _netNewRecvLogin : public _netNewRecvEventBase
{
    virtual bool init()
    {
        if (!_netNewRecvEventBase::init()) {
            return false;
        }
      
        return true;
    }
};

struct _netNewSendEventDrawCard : public _netNewSendEventBase
{
    virtual std::string generateContentStr()
    {
        char buffer[127] = {0};
        //sprintf(buffer, "k=%s&params=type=1",CUserDate::getInstance()->getUserToken().c_str());
        return buffer;
    }
};


struct _netNewRecvEventDrawCard : public _netNewRecvEventBase
{
    virtual bool init()
    {
        if (!_netNewRecvEventBase::init()) {
            return false;
        }
             return true;
    }
    std::string cardInfo;
   // HeroFragmentSumInfo hfsInfo;
};

#endif /* defined(__GAME2__zzbNewNetStruct__) */
