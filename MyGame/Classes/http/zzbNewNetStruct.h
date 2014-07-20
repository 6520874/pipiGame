//
//  zzbNewNetStruct.h
//  GAME2
//
//  Created by zzb on 14-1-13.
//
//

#ifndef __GAME2__zzbNewNetStruct__
#define __GAME2__zzbNewNetStruct__

#include <iostream>
#include "cocos2d.h"
#include "DBMgr.h"
#include "UserDate.h"
#include "CardManager.h"


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
	//std::string parseHasEqualInstructionKeyname(const std::string& key);
    
	void parseAllParams(const std::string&str);
    //std::map<std::string, std::string> m_paramsStr;
    std::map<std::string, std::map<std::string, std::string>> m_paramsStr;
	int m_retCode;
};

struct _netNewSendEventDrawCard : public _netNewSendEventBase
{
    virtual std::string generateContentStr()
    {
        char buffer[127] = {0};
        sprintf(buffer, "k=%s&params=type=1",CUserDate::getInstance()->getUserToken().c_str());
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
        cardInfo = parseStrAfterEqualFromInstruction("Info", "cardInfo");
        hfsInfo.m_iLargeSummonStone = parseNumberAfterEqualFromInstruction("Info", "bigPro");
        hfsInfo.m_iDropLargeSummonStone = parseNumberAfterEqualFromInstruction("Info", "bigNum");
        hfsInfo.m_iType = parseNumberAfterEqualFromInstruction("Info", "type");
        hfsInfo.m_iMidSummonStone = parseNumberAfterEqualFromInstruction("Info", "middlePro");
        hfsInfo.m_iDropMidSummonStone = parseNumberAfterEqualFromInstruction("Info", "middleNum");
        hfsInfo.m_iSmallSummonStone = parseNumberAfterEqualFromInstruction("Info", "smallPro");
        hfsInfo.m_iDropSmallSummonStone = parseNumberAfterEqualFromInstruction("Info", "smallNum");
        CDBMgr::getInstance()->ReadHeroFragment(cardInfo, hfsInfo);
        return true;
    }
    std::string cardInfo;
    HeroFragmentSumInfo hfsInfo;
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
        int UserId = parseNumberAfterEqualFromInstruction("user", "userId");
        std::string Name = parseStrAfterEqualFromInstruction("user","userName");
        int Level = parseNumberAfterEqualFromInstruction("user","userLevel");
        int Exp = parseNumberAfterEqualFromInstruction("user","userExp");
        int Str = parseNumberAfterEqualFromInstruction("user","stamina");
        int Coin = parseNumberAfterEqualFromInstruction("user","gold");
        int MagicStone = parseNumberAfterEqualFromInstruction("user","diamond");
        int VipExp = parseNumberAfterEqualFromInstruction("user","vipExp");
        int VipLevel = parseNumberAfterEqualFromInstruction("user","vipLevel");
        PassSumInfo PassSum;
        userRewardinfo Reward;
        std::string DropHeroFragment = "";
        int LoginDay =0;
        std::string token = parseStrAfterEqualFromInstruction("Info", "k");
        std::string authcode = parseStrAfterEqualFromInstruction("user", "authcode");
        int mapid = parseNumberAfterEqualFromInstruction("user","mapId");
        int mapMinid = parseNumberAfterEqualFromInstruction("user","mapMinId");
        std::string cardInfo = parseStrAfterEqualFromInstruction("cardInfo","cardInfo");
        std::string formation = parseStrAfterEqualFromInstruction("formation","formation");
        std::string staminaTime = parseStrAfterEqualFromInstruction("user","staminaTime");
        int maxLevelExp = parseNumberAfterEqualFromInstruction("user","maxLevelExp");
        std::string cardPrice = parseStrAfterEqualFromInstruction("cardPrice","cardPrice");
        std::string serverTime = parseStrAfterEqualFromInstruction("systemTime","systemTime");
        int  isSign = parseNumberAfterEqualFromInstruction("isSign","isSign");
        
        CUserDate::getInstance()->setUserInfo(UserId, Name, Level, Exp, Str, Coin,  MagicStone,  VipExp, VipLevel, PassSum,  Reward, LoginDay,  DropHeroFragment,  token,  authcode,  mapid,  mapMinid,formation,staminaTime,maxLevelExp,serverTime,isSign);
        
        CCardManager::GetSingletonPtr()->ReadMyCardPrice(cardPrice);
        CCardManager::GetSingletonPtr()->ReadMyCard(cardInfo);
        return true;
    }
};

struct _netNewSendUpdateTeamList : public _netNewSendEventBase
{
    virtual std::string generateContentStr()
    {
        //teamType 队伍类型
        char buffer[2048] = {0};
        sprintf(buffer, "k=%s&params=teamList=%s*teamType=%d*cardInfo=%s",CUserDate::getInstance()->getUserToken().c_str(),m_sTeamList.c_str(),type,m_sCardList.c_str());
        return buffer;
    }
    int type;
    std::string m_sTeamList;
    std::string m_sCardList;
};
struct _netNewRecvUpdateTeamList : public _netNewRecvEventBase
{
    virtual bool init()
    {
        if (!_netNewRecvEventBase::init()) {
            return false;
        }
        return true;
    }

};
struct _netNewSendUpdateCardInfo : public _netNewSendEventBase
{
    virtual std::string generateContentStr()
    {
        //teamType 队伍类型
        char buffer[127] = {0};
        sprintf(buffer, "k=%s&params=cardInfo=%s",CUserDate::getInstance()->getUserToken().c_str(),m_sCardList.c_str());
        return buffer;
    }
    std::string m_sCardList;
};

struct _netNewRecvUpdateCardInfo : public _netNewRecvEventBase
{
    virtual bool init()
    {
        if (!_netNewRecvEventBase::init()) {
            return false;
        }
        return true;
    }

};

//friend started
//申请添加好友
struct _netNewSendApplyAddFriend : public _netNewSendEventBase
{
    virtual std::string generateContentStr()
    {
        char buffer[127] = {0};
        sprintf(buffer, "k=%s&params=senderId=%d*receiveId=%d*msg=%s",CUserDate::getInstance()->getUserToken().c_str(),senderId,receiveId,msg.c_str());
        return buffer;
    }
    int  senderId;
    int  receiveId;
    std::string msg;
};

struct _netNewRecvApplyAddFriend : public _netNewRecvEventBase
{
    virtual bool init()
    {
        if (!_netNewRecvEventBase::init())
        {
            return false;
        }
        
        return true;
    }
};

//同意添加好友
struct _netNewSendAgreeAddFriend: public _netNewSendEventBase
{
    virtual std::string generateContentStr()
    {
        char buffer[127] = {0};
        sprintf(buffer, "k=%s&params=senderId=%d*receiveId=%d*fmsgId=%d*msg=%s",CUserDate::getInstance()->getUserToken().c_str(),senderId,receiveId,fmsgId,msg.c_str());
        return buffer;
    }
    int  senderId;
    int  receiveId;
    int  fmsgId;
    std::string msg;
    
};

struct _netNewRecvAgreeAddFriend : public _netNewRecvEventBase
{
    virtual bool init()
    {
        if (!_netNewRecvEventBase::init()) {
            return false;
        }
        
        return true;
    }
};

//拒绝添加好友
struct _netNewSendRefuseAddFriend: public _netNewSendEventBase
{
    virtual std::string generateContentStr()
    {
        char buffer[127] = {0};
        sprintf(buffer, "k=%s&params=senderId=%d*receiveId=%d*fmsgId=%d*msg=%s",CUserDate::getInstance()->getUserToken().c_str(),senderId,receiveId,fmsgId,msg.c_str());
        return buffer;
    }
    int  senderId;
    int  receiveId;
    int  fmsgId;
    std::string msg;
};

struct _netNewRecvRefuseAddFriend : public _netNewRecvEventBase
{
    virtual bool init()
    {
        if (!_netNewRecvEventBase::init()) {
            return false;
        }
        return true;
    }
};

//发送私信
struct _netNewSendMessgaeToFriend: public _netNewSendEventBase
{
    virtual std::string generateContentStr()
    {
        char buffer[127] = {0};
        sprintf(buffer, "k=%s&params=friendId=%d*msg=%s",CUserDate::getInstance()->getUserToken().c_str(),friendId,msg.c_str());
        return buffer;
    }
    int friendId;
    std::string msg;
};

struct _netNewRecvMessageToFriend: public _netNewRecvEventBase
{
    virtual bool init()
    {
        if (!_netNewRecvEventBase::init()) {
            return false;
        }
        return true;
    }
};

//删除好友
struct _netNewSendDeleteFriend: public _netNewSendEventBase
{
    virtual std::string generateContentStr()
    {
        char buffer[127] = {0};
        sprintf(buffer, "k=%s&params=friendId=%d",CUserDate::getInstance()->getUserToken().c_str(),friendId);
        return buffer;
    }
    int friendId;
};

struct _netNewRecvDeleteFriend: public _netNewRecvEventBase
{
    virtual bool init()
    {
        if (!_netNewRecvEventBase::init()) {
            return false;
        }
        return true;
    }
};

//获取好友列表
struct _netNewSendGetFriendList: public _netNewSendEventBase
{
    virtual std::string generateContentStr()
    {
        char buffer[127] = {0};
        sprintf(buffer, "k=%s&params=userId=%d",CUserDate::getInstance()->getUserToken().c_str(),CUserDate::getInstance()->getUserId());
        return buffer;
    }
};

struct _netNewRecvGetFriendList: public _netNewRecvEventBase
{
    virtual bool init()
    {
        if (!_netNewRecvEventBase::init())
        {
            return false;
        }
        return true;
    }
};

//获取推荐好友
struct _netNewSendGetRecommendList : public _netNewSendEventBase
{
    virtual std::string generateContentStr()
    {
        char buffer[127] = {0};
        sprintf(buffer, "k=%s&params=userId=%d",CUserDate::getInstance()->getUserToken().c_str(),CUserDate::getInstance()->getUserId());
        return buffer;
    }
};

struct _netNewRecvGetRecommendList : public _netNewRecvEventBase
{
    virtual bool init()
    {
        if (!_netNewRecvEventBase::init()) {
            return false;
        }
        return true;
    }
    
};

//获取好友申请列表
struct _netNewSendGetFriendApplyList:public _netNewSendEventBase
{
    virtual std::string generateContentStr()
    {
        char buffer[127] = {0};
        sprintf(buffer, "k=%s&params=userId=%d",CUserDate::getInstance()->getUserToken().c_str(),CUserDate::getInstance()->getUserId());
        return buffer;
    }
};

struct _netNewRecvGetFriendApplyList:public _netNewRecvEventBase
{
    virtual bool init()
    {
        if (!_netNewRecvEventBase::init()) {
            return false;
        }
        return true;
    }
};

//获取未读好友消息
struct _netNewSendGetFriendMessage :public _netNewSendEventBase
{
    virtual std::string generateContentStr()
    {
        char buffer[127] = {0};
        sprintf(buffer, "k=%s&params=userId=%d",CUserDate::getInstance()->getUserToken().c_str(),CUserDate::getInstance()->getUserId());
        return buffer;
    }
    int userId;
};

struct _netNewRecvGetFriendMessage :public _netNewRecvEventBase
{
    virtual bool init()
    {
        if (!_netNewRecvEventBase::init()) {
            return false;
        }
        return true;
    }
};

//搜索好友
struct _netNewSendSearchFriendId :public _netNewSendEventBase
{
    virtual std::string generateContentStr()
    {
        char buffer[127] = {0};
        sprintf(buffer, "k=%s&params=userId=%d*searchId=%d",CUserDate::getInstance()->getUserToken().c_str(),CUserDate::getInstance()->getUserId(),searchId);
        return buffer;
    }
    int searchId;
};

struct _netNewRecvSearchFriendId :public _netNewRecvEventBase
{
    virtual bool init()
    {
        if (!_netNewRecvEventBase::init())
        {
            return false;
        }
        return true;
    }
};

//更新私信消息状态
struct _netNewSendUpdateMessageState:public _netNewSendEventBase
{

    virtual std::string generateContentStr()
    {
        char buffer[127] = {0};
        sprintf(buffer, "k=%s&params=userId=%d*fmsgId=%d",CUserDate::getInstance()->getUserToken().c_str(),CUserDate::getInstance()->getUserId(),m_iFmsg);
        return buffer;
    }
    int m_iFmsg;
};

struct _netNewRecvUpdateMessageState:public _netNewRecvEventBase
{
    virtual bool init()
    {
        if (!_netNewRecvEventBase::init())
        {
            return false;
        }
        return true;
    }

};


//发送世界聊天
struct _netNewSendWorldTalk: public _netNewSendEventBase
{
    virtual std::string generateContentStr()
    {
        char buffer[127] = {0};
        sprintf(buffer, "k=%s&params=userId=%d*id=%d*msg=%s",CUserDate::getInstance()->getUserToken().c_str(),CUserDate::getInstance()->getUserId(),Id,sMsg.c_str());
        return buffer;
    }
    int Id;
    std::string sMsg;
};

struct _netNewRecvWorldTalk: public _netNewRecvEventBase
{
    virtual bool init()
    {
        if(!_netNewRecvEventBase::init())
        {
            return false;
        }
        return true;
    }
};

//刷新世界聊天
struct _netNewSendRefreshWorldMsg: public _netNewSendEventBase
{
    virtual std::string generateContentStr()
    {
        char buffer[127] = {0};
        sprintf(buffer, "k=%s&params=userId=%d*id=%d",CUserDate::getInstance()->getUserToken().c_str(),CUserDate::getInstance()->getUserId(),Id);
        return buffer;
    }
    int Id;
};

struct _netNewRecvRefreshWorldMsg: public _netNewRecvEventBase
{
    virtual bool init()
    {
        if(!_netNewRecvEventBase::init())
        {
            return false;
        }
        return true;
    }
};
//friend ended


//TODO: 修改用户名字
struct _netNewEventUpdateUserName : public _netNewSendEventBase
{
    virtual std::string generateContentStr()
    {
        char buffer[127] = {0};
        sprintf(buffer, "k=%s&params=userId=%d*userName=%s",CUserDate::getInstance()->getUserToken().c_str(),CUserDate::getInstance()->getUserId(),userName.c_str());
        return buffer;
    }    std::string userName;
};
struct _netNewRecvUpdateUserName : public _netNewRecvEventBase
{
    virtual bool init()
    {
        if (!_netNewRecvEventBase::init()) {
            return false;
        }
        return true;
    }
};
//TODO: 修改体力
struct _netNewEventUpdateUserStamina : public _netNewSendEventBase
{
    virtual std::string generateContentStr()
    {
        char buffer[127] = {0};
        sprintf(buffer, "k=%s&params=stamina=%d",CUserDate::getInstance()->getUserToken().c_str(),stamina);
        return buffer;
    }
    int stamina;
};
struct _netNewRecvUpdateUserStamina : public _netNewRecvEventBase
{
    virtual bool init()
    {
        if (!_netNewRecvEventBase::init()) {
            return false;
        }
        return true;
    }
};
//TODO: 绑定其他账号
struct _netNewEventBoundUserIdTOOtherId : public _netNewSendEventBase
{
    virtual std::string generateContentStr()
    {
        char buffer[127] = {0};
        sprintf(buffer, "k=%s&params=type=%d&mark=%s*pass=%s",CUserDate::getInstance()->getUserToken().c_str(),type,mark.c_str(),pass.c_str());
        return buffer;
    }
    int type;
    std::string mark;
    std::string pass;
};
struct _netNewRecvBoundUserIdTOOtherId : public _netNewRecvEventBase
{
    virtual bool init()
    {
        if (!_netNewRecvEventBase::init()) {
            return false;
        }
        return true;
    }
};

//TODO: 获取商店物品列表
struct _netNewEventShopList : public _netNewSendEventBase
{
    virtual std::string generateContentStr()
    {
        char buffer[127] = {0};
        sprintf(buffer, "k=%s&params=userId=%d",CUserDate::getInstance()->getUserToken().c_str(),CUserDate::getInstance()->getUserId());
        return buffer;
    }
};

struct _netNewRecvShopList : public _netNewRecvEventBase
{
    virtual bool init()
    {
        if (!_netNewRecvEventBase::init()) {
            return false;
        }
        return true;
    }
};

//购买商店物品
struct _netNewEventBuyBuyProps:public _netNewSendEventBase
{
    int iId;
    virtual std::string generateContentStr()
    {
        char buffer[127] = {0};
        
        sprintf(buffer, "k=%s&params=userId=%d*id=%d",CUserDate::getInstance()->getUserToken().c_str(),CUserDate::getInstance()->getUserId(),iId);
        return buffer;
    }
};

struct _netNewEventRecvBuyBuyProps:public _netNewRecvEventBase
{
    virtual bool init()
    {
        if (!_netNewRecvEventBase::init()) {
            return false;
        }
        return true;
    }
};

//TODO: 获得助战好友列表
struct _netNewEventBattleBefore : public _netNewSendEventBase
{
    virtual std::string generateContentStr()
    {
        char buffer[127] = {0};
        sprintf(buffer, "k=%s&params=userId=%d",CUserDate::getInstance()->getUserToken().c_str(),CUserDate::getInstance()->getUserId());
        return buffer;
    }
};
struct _netNewRecvBattleBefore : public _netNewRecvEventBase
{
    virtual bool init()
    {
        if (!_netNewRecvEventBase::init()) {
            return false;
        }
        return true;
    }
};
//TODO: 战后结果
struct _netNewEventBattleAfter : public _netNewSendEventBase
{
    virtual std::string generateContentStr()
    {
        char buffer[127] = {0};
        sprintf(buffer, "k=%s&params=userId=%d*type=%d*result=%d*mapId=%d*mapMinId=%d*helpId=%d*isFriend=%d*dropGoods=%s",CUserDate::getInstance()->getUserToken().c_str(),CUserDate::getInstance()->getUserId(),type,result,mapId,mapMinId,helpId,isFriend,dropGoods.c_str());
        return buffer;
    }
    int type;
    int result;
    int mapId;
    int mapMinId;
    int helpId;
    int isFriend;
    std::string dropGoods;
    
};

struct _netNewRecvBattleAfter : public _netNewRecvEventBase
{
    virtual bool init()
    {
        if (!_netNewRecvEventBase::init()) {
            return false;
        }
        return true;
    }
};

//战后复活
struct _netNewEventBattleRevive: public _netNewSendEventBase
{
    virtual std::string generateContentStr()
    {
        char buffer[127] = {0};
        sprintf(buffer, "k=%s&params=userId=%d",CUserDate::getInstance()->getUserToken().c_str(),CUserDate::getInstance()->getUserId());
        return buffer;
    }
};

struct _netNewRecvBattleReviver : public _netNewRecvEventBase
{
    virtual bool init()
    {
        if (!_netNewRecvEventBase::init()) {
            return false;
        }
        return true;
    }
};

//TODO: 世界boss 伤害
struct _netNewEventBattleWorldBoss : public _netNewSendEventBase
{
    virtual std::string generateContentStr()
    {
        char buffer[127] = {0};
        sprintf(buffer, "k=%s&params=userId=%d*hurt=%d",CUserDate::getInstance()->getUserToken().c_str(),CUserDate::getInstance()->getUserId(),hurt);
        return buffer;
    }
    int hurt;
};
struct _netNewRecvBattleWorldBoss : public _netNewRecvEventBase
{
    virtual bool init()
    {
        if (!_netNewRecvEventBase::init()) {
            return false;
        }
        return true;
    }
};
//TOOD: 世界boss 排行榜
struct _netNewEventGetRankWorldBoss : public _netNewSendEventBase
{
    virtual std::string generateContentStr()
    {
        char buffer[127] = {0};
        sprintf(buffer, "k=%s&params=userId=%d",CUserDate::getInstance()->getUserToken().c_str(),CUserDate::getInstance()->getUserId());
        return buffer;
    }
};
struct _netNewRecvGetRankWorldBoss : public _netNewRecvEventBase
{
    virtual bool init()
    {
        if (!_netNewRecvEventBase::init()) {
            return false;
        }
        return true;
    }
};
//TODO: 保存抽卡结果
struct _netNewEventSaveTakeOutCard : public _netNewSendEventBase
{
    virtual std::string generateContentStr()
    {
        char buffer[127] = {0};
        sprintf(buffer, "k=%s&params=type=%d*addNum=%d*takeCard=%s",CUserDate::getInstance()->getUserToken().c_str(),type,addNum,takeCard.c_str());
        return buffer;
    }
    int type;
    int addNum;
    std::string takeCard;
};
struct _netNewRecvSaveTakeOutCard : public _netNewRecvEventBase
{
    virtual bool init()
    {
        if (!_netNewRecvEventBase::init()) {
            return false;
        }
        int diamond = parseNumberAfterEqualFromInstruction("Info", "userDiamond");
        CUserDate::getInstance()->setUserMagic(diamond);
        return true;
    }
};
//TODO: 获取道具列表
struct _netNewEventGetItemByType : public _netNewSendEventBase
{
    virtual std::string generateContentStr()
    {
        char buffer[127] = {0};
        sprintf(buffer, "k=%s&params=userId=%d*type=%d", CUserDate::getInstance()->getUserToken().c_str(), CUserDate::getInstance()->getUserId(), type);
        return buffer;
    }
    
    int type;
};
struct _netNewRecvGetItemByType : public _netNewRecvEventBase
{
    virtual bool init()
    {
        if (!_netNewRecvEventBase::init()) {
            return false;
        }
        
        return true;
    }
    
    //std::vector<UserProps> vecProps;
};

//TODO: 保存道具
struct _netNewEventSaveItem : public _netNewSendEventBase
{
    virtual std::string generateContentStr()
    {
        char buffer[127] = {0};
        sprintf(buffer, "k=%s&params=type=%d*userId=%d*itemId=%d*num=%d*addOrCut=%d",CUserDate::getInstance()->getUserToken().c_str(),type,CUserDate::getInstance()->getUserId(),itemId,num,addOrCut);
        return buffer;
    }
    int type;
    int itemId;
    int num;
    int addOrCut;//1增加 0消费
};
struct _netNewRecvSaveItem : public _netNewRecvEventBase
{
    virtual bool init()
    {
        if (!_netNewRecvEventBase::init()) {
            return false;
        }
        return true;
    }
};
//TODO: 获取道具占用格子数
struct _netNewEventGetItemBagNum : public _netNewSendEventBase
{
    virtual std::string generateContentStr()
    {
        char buffer[127] = {0};
        sprintf(buffer, "k=%s&params=userId=%d",CUserDate::getInstance()->getUserToken().c_str(),CUserDate::getInstance()->getUserId());
        return buffer;
    }
};
struct _netNewRecvGetItemBagNum : public _netNewRecvEventBase
{
    virtual bool init()
    {
        if (!_netNewRecvEventBase::init()) {
            return false;
        }
        return true;
    }
};
//TODO: 刷新阵型
struct _netNewEventRefreshFormlation : public _netNewSendEventBase
{
    virtual std::string generateContentStr()
    {
        char buffer[127] = {0};
        sprintf(buffer, "k=%s&params=userId=%d*type=%d*formlationId=%d",CUserDate::getInstance()->getUserToken().c_str(),CUserDate::getInstance()->getUserId(),type,formlationId);
        return buffer;
    }
    int type;
    int formlationId;
};
struct _netNewRecvRefreshFormlation : public _netNewRecvEventBase
{
    virtual bool init()
    {
        if (!_netNewRecvEventBase::init()) {
            return false;
        }
        std::string formation = parseStrAfterEqualFromInstruction("Info","info");
        CUserDate::getInstance()->ReadFormation(formation);
        int coin = parseNumberAfterEqualFromInstruction("Info","userGold");
        CUserDate::getInstance()->setUserCoin(coin);
        return true;
    }
};

// 卡牌进化
struct _netNewEventEvolutionCard : public _netNewSendEventBase {
    virtual std::string generateContentStr()
    {
        char buffer[127] = {0};
        sprintf(buffer, "k=%s&params=userId=%d*cardId=%d*star=%d*cardInfo=%s",CUserDate::getInstance()->getUserToken().c_str(),CUserDate::getInstance()->getUserId(), cardId, star,cardInfo.c_str());
        return buffer;
    }
    
    int cardId;
    int star;
    string cardInfo;
};

struct _netNewRecvEvolutionCard : public _netNewRecvEventBase {
    virtual bool init()
    {
        if (!_netNewRecvEventBase::init()) {
            return false;
        }
        return true;
    }
};

// 卡牌升级
struct _netNewEventUpgradeCard : public _netNewSendEventBase
{
    virtual std::string generateContentStr()
    {
        char buffer[127] = {0};
        sprintf(buffer, "k=%s&params=userId=%d*cardId=%d*star=%d*upgradeInfo=%s*cardInfo=%s", CUserDate::getInstance()->getUserToken().c_str(), CUserDate::getInstance()->getUserId(), cardId, star,item.c_str(),pCardInfo.c_str());
        return buffer;
    }
    
    int cardId;//要升级的卡牌id
    int star;//要升级的卡牌的当前星级
    string item;//碎片道具信息
    string pCardInfo;//卡牌信息
};

struct _netNewRecvUpgradeCard : public _netNewRecvEventBase
{
  virtual bool init()
    {
        if (!_netNewRecvEventBase::init()) {
            return false;
        }
        return true;
    }
};

//技能升级
struct _netNewEventSkillUpgrade : public _netNewSendEventBase
{
    virtual std::string generateContentStr()
    {
        char buffer[127] = {0};
        sprintf(buffer, "k=%s&params=userId=%d*skillLevel=%d*needLevel=%d*cardInfo=%s", CUserDate::getInstance()->getUserToken().c_str(), CUserDate::getInstance()->getUserId(), targetSkillLevel, neededCardLevel,m_cardInfo.c_str());//userId, skillLevel(技能目标等级)，needLevel（卡牌等级）
        return buffer;
    }
    
    int targetSkillLevel;//目标技能等级
    int neededCardLevel;//需要卡牌的等级
    std::string m_cardInfo;
};

struct _netNewRecvSkillUpgrade : public _netNewRecvEventBase
{
    virtual bool init()
    {
        if (!_netNewRecvEventBase::init()) {
            return false;
        }
        
        return true;
    }
};

//得到用户签到信息
struct _netNewEventGetRegistration : public _netNewSendEventBase
{
    virtual std::string generateContentStr()
    {
        char buffer[127] = {0};
        sprintf(buffer, "k=%s&params=userId=%d", CUserDate::getInstance()->getUserToken().c_str(), CUserDate::getInstance()->getUserId());
        return buffer;
    }
};

struct _netNewRecvGetRegistration : public _netNewRecvEventBase
{
    virtual bool init()
    {
        if (!_netNewRecvEventBase::init()) {
            return false;
        }
        
        return true;
    }
};

//用户签到
struct _netNewEventSaveRegistration : public _netNewSendEventBase
{
    virtual std::string generateContentStr()
    {
        char buffer[127] = {0};
        sprintf(buffer, "k=%s&params=userId=%d", CUserDate::getInstance()->getUserToken().c_str(), CUserDate::getInstance()->getUserId());
        return buffer;
    }
};

struct _netNewRecvSaveRegistration : public _netNewRecvEventBase
{
    virtual bool init()
    {
        if (!_netNewRecvEventBase::init()) {
            return false;
        }
        
        return true;
    }
};


#endif /* defined(__GAME2__zzbNewNetStruct__) */
