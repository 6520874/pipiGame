//
//  zzbNewNetStruct.cpp
//  GAME2
//
//  Created by zzb on 14-1-13.
//
//

#include "zzbNewNetStruct.h"



NETNEWEVENTNAMEINF g_newEventNameInf[NET_NEW_EVENT_NR] =
{
    {NET_EVENT_DRAWCARD,"c=Card&m=takeOutCards","HoodleServer/apiServlet","错误代码001"},//获得抽卡数据如掉落的英雄id和概率
    {NET_EVENT_LOGIN,"login=1","HoodleServer/login","错误代码002"},
    {NET_EVENT_TEAMLIST,"c=Card&m=updateTeamList","HoodleServer/apiServlet","错误代码003"},
    {NET_EVENT_UPDATE_CARD_INFO,"c=Card&m=updateCardInfo","HoodleServer/apiServlet","错误代码004"},
    {NET_EVENT_APPLY_ADDFRIEND,"c=Friend&m=applyAddFriend","HoodleServer/apiServlet","错误代码005"},
    {NET_EVENT_AGREE_ADDFRIEND,"c=Friend&m=agreeAddFriend","HoodleServer/apiServlet","错误代码006"},
    {NET_EVENT_GET_RECOMMEN_LIST,"c=Friend&m=getRecommendList","HoodleServer/apiServlet","错误代码007"},
    {NET_EVENT_UPDATE_USER_NAME,"c=GameUser&m=updateUserName","HoodleServer/apiServlet","错误代码008"},{NET_EVENT_UPDATE_USER_STAMINA,"c=GameUser&m=updateUserStamina","HoodleServer/apiServlet","错误代码009"},
    {NET_EVENT_BOUND_USERID_TO_OTHERID,"c=GameUser&m=boundUserIdToOtherId","HoodleServer/apiServlet","错误代码010"},
    {NET_EVENT_GET_PROPSHOP_LIST,"c=Shop&m=getBuyPropsList","HoodleServer/apiServlet","错误代码011"},
    {NET_EVENT_BATTLE_BEFORE,"c=Battle&m=battleBefore","HoodleServer/apiServlet","错误代码012"},
    {NET_EVENT_BATTLE_AFTER,"c=Battle&m=battleAfter","HoodleServer/apiServlet","错误代码013"},
    {NET_EVENT_BATTLE_WORLD_BOSS,"c=Battle&m=battleWorldBoss","HoodleServer/apiServlet","错误代码014"},
    {NET_EVENT_GET_RANK_WORLD_BOSS,"c=Battle&m=getRankWorldBoss","HoodleServer/apiServlet","错误代码015"},
    {NET_EVENT_SAVE_TAKE_OUT_CARD,"c=Card&m=saveTakeOutCard","HoodleServer/apiServlet","错误代码016"},
    {NET_EVENT_GET_ITEM_BY_TYPE,"c=Item&m=getItemByType","HoodleServer/apiServlet","错误代码017"},
    {NET_EVENT_SAVE_ITEM,"c=Item&m=saveItem","HoodleServer/apiServlet","错误代码018"},
    {NET_EVENT_GET_ITEM_BAG_NUM,"c=Item&m=getItemBagNum","HoodleServer/apiServlet","错误代码019"},
    {NET_EVENT_REFRESH_FORMLATION,"c=Card&m=refreshFormlation","HoodleServer/apiServlet","错误代码020"},
    {NET_EVENT_GET_FRIEND_LIST,"c=Friend&m=getFriendList","HoodleServer/apiServlet","错误代码021"},
    {NET_EVENT_GET_FRIEND_APPLY_LIST,"c=Friend&m=getFriendApplyList","HoodleServer/apiServlet","错误代码022"},
    {NET_EVENT_GET_FRIEND_MSG,"c=Friend&m=getFriendMsg","HoodleServer/apiServlet","错误代码023"},
 
    {NET_EVENT_SEARCH_FRIEND_ID,"c=Friend&m=searchFriendId","HoodleServer/apiServlet","错误代码024"},
    {NET_EVENT_REFUSE_ADDFRIEND,"c=Friend&m=refuseAddFriend","HoodleServer/apiServlet","错误代码025"},
    {NET_EVENT_DELETE_FRIEND,"c=Friend&m=deleteFriend","HoodleServer/apiServlet","错误代码026"},
    {NET_EVENT_SEND_MESSAGE,"c=Friend&m=sendMsgToFriend","HoodleServer/apiServlet","错误代码027"},
    {NET_EVENT_SEND_WORLD_MSG,"c=Friend&m=sendWorldMsg","HoodleServer/apiServlet","错误代码028"},
    {NET_EVENT_REFRESH_WORLD_MSG,"c=Friend&m=refreshWorldMsg","HoodleServer/apiServlet","错误代码029"},
    {NET_EVENT_EVOLUTION_CARD, "c=Card&m=cardEvolution", "HoodleServer/apiServlet", "卡牌进化错误30"},
    {NET_EVENT_UPGRADE_CARD, "c=Card&m=cardUpgrade", "HoodleServer/apiServlet", "卡牌升级错误31"},
    {NET_EVENT_SKILL_UPGRADE, "c=Skill&m=skillUpLevel", "HoodleServer/apiServlet", "技能升级错误32"},
     {NET_EVENT_BUYPROPS,"c=Shop&m=buyBuyProps","HoodleServer/apiServlet", "购买道具错误33"},
    {NET_EVENT_UPDATE_FRIEND_MSG_STATE,"c=Friend&m=updateMsgStatus","HoodleServer/apiServlet","错误代码034"},
    {NET_EVENT_BATTLE_REVIVE,"c=Battle&m=battleRevive","HoodleServer/apiServlet","错误代码035"},
    {NET_EVENT_GET_REGISTRATION,"c=DailyTask&m=getSignDailyInfo","HoodleServer/apiServlet","错误代码036"},
    {NET_EVENT_SAVE_REGISTRATION,"c=DailyTask&m=saveSignDaily","HoodleServer/apiServlet","错误代码036"}
};

/******************************************************************
 //funcName:getEventTypeByEventName
 
 //date:2013/3/19 17:13
 
 //desc:根据传入的命令名字得到type
 
 //param:
 
 //ret value:
 
 //author:butcher
 ******************************************************************/
//int getEventTypeByEventName(const char* pEventName)
//{
//	std::string retname = pEventName;
//	//如果有COMMAN直接去掉,晕
//	int pos = retname.find("COMMAN");
//	if(pos != -1){
//		retname = retname.substr(strlen("COMMAN"),-1);
//	}
//	int len = retname.length();
//	const char* pRealName = retname.c_str();
//	for(int i = 0; i < NET_NEW_EVENT_NR; i++){
//		if(memcmp(pRealName,g_newEventNameInf[i].m_eventName,len) == 0){
//			return i;
//		}
//	}
//	return 0;//INVALIDE_VALUE;
//}
/******************************************************************
 //funcName:getEventNameByEventType
 
 //date:2013/3/19 17:14
 
 //desc:根据命令类型,得到命令名字
 
 //param:
 
 //ret value:
 
 //author:butcher
 ******************************************************************/
const char* getNewEventNameByEventType(int eventType)
{
	for(int i = 0; i < NET_NEW_EVENT_NR; i++){
		if(g_newEventNameInf[i].m_eventType == eventType){
			return g_newEventNameInf[i].m_eventName;
		}
	}
	return NULL;
}
const char* getNewEventHeadStr(int eventType)
{
	for(int i = 0; i < NET_NEW_EVENT_NR; i++){
		if(g_newEventNameInf[i].m_eventType == eventType){
			return g_newEventNameInf[i].m_eventHead;
		}
	}
	return "";
}



_netNewRecvEventBase* _netNewRecvEventBase::create(
                                                   const int& nEventType,
                                                   const std::string&receiveCommand)
{
	_netNewRecvEventBase* pRecvEvent;
    std::string leftcommandstr = truncateCommandHeaderStr(receiveCommand);
	switch(nEventType){
        case NET_EVENT_DRAWCARD:
            pRecvEvent = new _netNewRecvEventDrawCard();
            break;
        case NET_EVENT_LOGIN:
            pRecvEvent = new _netNewRecvLogin();
            break;
        case NET_EVENT_TEAMLIST:
            pRecvEvent = new _netNewRecvUpdateTeamList();
            break;
        case NET_EVENT_UPDATE_CARD_INFO:
            pRecvEvent = new _netNewRecvUpdateCardInfo();
            break;
        case NET_EVENT_UPDATE_USER_NAME:
            pRecvEvent = new _netNewRecvUpdateUserName();
            break;
        case NET_EVENT_UPDATE_USER_STAMINA:
            pRecvEvent = new _netNewRecvUpdateUserStamina();
            break;
        case NET_EVENT_BOUND_USERID_TO_OTHERID:
            pRecvEvent = new _netNewRecvBoundUserIdTOOtherId();
            break;
        case NET_EVENT_GET_PROPSHOP_LIST:
            pRecvEvent = new _netNewRecvShopList();
            break;
        case NET_EVENT_BATTLE_BEFORE:
            pRecvEvent = new _netNewRecvBattleBefore();
            break;
        case NET_EVENT_BATTLE_AFTER:
            pRecvEvent = new _netNewRecvBattleAfter();
            break;
        case   NET_EVENT_BATTLE_REVIVE:
            pRecvEvent = new _netNewRecvBattleReviver();
            break;
        case NET_EVENT_BATTLE_WORLD_BOSS:
            pRecvEvent = new _netNewRecvBattleWorldBoss();
            break;
        case NET_EVENT_GET_RANK_WORLD_BOSS:
            pRecvEvent = new _netNewRecvGetRankWorldBoss();
            break;
        case NET_EVENT_SAVE_TAKE_OUT_CARD:
            pRecvEvent = new _netNewRecvSaveTakeOutCard();
            break;
        case NET_EVENT_GET_ITEM_BY_TYPE:
            pRecvEvent = new _netNewRecvGetItemByType();
            break;
        //friend
        case  NET_EVENT_APPLY_ADDFRIEND:
            pRecvEvent = new _netNewRecvApplyAddFriend();
            break;
        case NET_EVENT_AGREE_ADDFRIEND:
            pRecvEvent = new  _netNewRecvAgreeAddFriend();
            break;
        case  NET_EVENT_REFUSE_ADDFRIEND:
            pRecvEvent = new _netNewRecvRefuseAddFriend();
            break;
        case  NET_EVENT_REFRESH_WORLD_MSG:
            pRecvEvent = new _netNewRecvRefreshWorldMsg();
            break;
        case  NET_EVENT_SEND_WORLD_MSG:
            pRecvEvent = new  _netNewRecvWorldTalk;
            break;
        case  NET_EVENT_DELETE_FRIEND:
            pRecvEvent = new _netNewRecvDeleteFriend();
            break;
        case NET_EVENT_GET_FRIEND_LIST:
            pRecvEvent = new _netNewRecvGetFriendList();
            break;
            
        case NET_EVENT_GET_RECOMMEN_LIST:
            pRecvEvent = new _netNewRecvGetRecommendList();
            break;
        case NET_EVENT_GET_FRIEND_APPLY_LIST:
            pRecvEvent = new _netNewRecvGetFriendApplyList();
            break;
        case NET_EVENT_SEARCH_FRIEND_ID:
            pRecvEvent = new _netNewRecvSearchFriendId();
            break;
        case NET_EVENT_SEND_MESSAGE:
            pRecvEvent = new _netNewRecvMessageToFriend();
            break;
        case NET_EVENT_GET_FRIEND_MSG:
            pRecvEvent = new _netNewRecvGetFriendMessage();
            break;
        case NET_EVENT_UPDATE_FRIEND_MSG_STATE:
            pRecvEvent = new _netNewRecvUpdateMessageState();
            break;
        case NET_EVENT_SAVE_ITEM:
            pRecvEvent = new _netNewRecvSaveItem();
            break;
        case NET_EVENT_GET_ITEM_BAG_NUM:
            pRecvEvent = new _netNewRecvGetItemBagNum();
            break;
        case NET_EVENT_REFRESH_FORMLATION:
            pRecvEvent = new _netNewRecvRefreshFormlation();
            break;
        case NET_EVENT_EVOLUTION_CARD:
            pRecvEvent = new _netNewRecvEvolutionCard();
            break;
            
        case NET_EVENT_UPGRADE_CARD:
            pRecvEvent = new _netNewRecvUpgradeCard();
            break;
        case NET_EVENT_SKILL_UPGRADE:
            pRecvEvent = new _netNewRecvSkillUpgrade();
            break;
        case NET_EVENT_BUYPROPS:
            pRecvEvent = new _netNewEventRecvBuyBuyProps();
            break;
        case NET_EVENT_GET_REGISTRATION:
            pRecvEvent = new _netNewRecvGetRegistration();
            break;
        case NET_EVENT_SAVE_REGISTRATION:
            pRecvEvent = new _netNewRecvSaveRegistration();
            break;
        default:
            return NULL;
	}
	pRecvEvent->m_eventType = nEventType;
	pRecvEvent->parseAllParams(leftcommandstr);
	pRecvEvent->init();
	return pRecvEvent;
}
/******************************************************************
 //funcName:create
 
 //date:2013/3/15 11:26
 
 //desc:创建一个通用的错误事件
 
 //param:
 ret:错误的返回值
 errorcode:错误码
 
 //ret value:
 
 //author:butcher
 ******************************************************************/
//_netSendError* _netSendError::create(int ret,int errorcode)
//{
//	_netSendError* pErrorEvent = new _netSendError;
//	pErrorEvent->m_eventType = NET_EVENT_SEND_ERROR;
//	pErrorEvent->m_retCode = ret;
//	pErrorEvent->m_errorCode = errorcode;
//	return pErrorEvent;
//}
//不用通知scene了,直接显示
//bool _netSendError::execute()
//{
//    CCLog("网络连接失败!\n按确定键重新连接!");
//	return false;
//}
//_netRecvError* _netRecvError::create(int ret)
//{
//	_netRecvError* pErrorEvent = new _netRecvError;
//	pErrorEvent->m_eventType = NET_EVENT_RECV_ERROR;
//	pErrorEvent->m_retCode = ret;
//	return pErrorEvent;
//}
//bool _netRecvError::execute()
//{
//    CCLog("网络出现异常,请稍后再试");
//	return false;
//}
/******************************************************************
 //funcName:generateSendStr
 
 //date:2013/3/15 15:23
 
 //desc:实际进行消息发送的
 
 //param:
 
 //ret value:
 
 //author:butcher
 ******************************************************************/
std::string _netNewSendEventBase::generateSendStr()
{
	std::string sendstr = URL_ADDRESS;
    sendstr += getNewEventHeadStr(m_eventType);
    sendstr += "?";
	sendstr += getNewEventNameByEventType(m_eventType);
	sendstr += "&";
	std::string contentstr = generateContentStr();
    std::string strHttp = CDBMgr::getInstance()->HttpEncrypt(contentstr);
    __String *str = __String::createWithFormat("%s&cph=%s",contentstr.c_str(),strHttp.c_str());
    contentstr = str->getCString();
	sendstr += contentstr;
	return sendstr;
}
/******************************************************************
 //funcName:truncateCommandHeaderStr
 
 //date:2013/3/14 15:42
 
 //desc:接收到的信息的头的抓取
 
 //param:
 commanstr[in/out]:命令串;返回的是去掉头以及?之后的字符串
 "createUser?userid:.."
 返回"userid..."
 
 //ret value:
 事件名称,createUser
 
 //author:butcher
 ******************************************************************/
std::string _netNewRecvEventBase::truncateCommandHeaderStr(
                                                           std::string commandstr)
{
	int pos = commandstr.find('?');
    if (pos != std::string::npos) {
        std::string headname = commandstr.substr(0,pos);
        commandstr = commandstr.substr(pos+1,-1);
        return commandstr;
    }
	return commandstr;
}
/******************************************************************
 //funcName:parseAllParams
 
 //date:2013/3/14 16:11
 
 //desc:对传入的字符串进行解析
 以&作为分隔符,!作为结束
 比如:"userid=1000&name=中国!"
 vector中会存入
 userid=1000
 name=中国
 //param:
 
 //ret value:
 
 //author:butcher
 ******************************************************************/
void _netNewRecvEventBase::parseAllParams(const std::string&str)
{
	m_paramsStr.clear();
    //modify by wwj
    std::string Maxkey, Maxvalue;
    int pos = 0;
    
	std::string tempstr = str;
	int seperatorpos = tempstr.find('=');
    if (seperatorpos==-1)
    {
        return;
    }
    do {
        seperatorpos = tempstr.find('=');
        Maxkey = tempstr.substr(0,seperatorpos);
        pos = tempstr.find('&');
        Maxvalue = tempstr.substr(seperatorpos + 1,pos-seperatorpos-1);
        pos = Maxvalue.find('#');
        std::map<std::string, std::string> tMapStr;
        tMapStr.clear();
        while (Maxvalue.compare(""))
        {
            std::string key = "";
            std::string value = "";
            int posTwo = 0;
            posTwo = Maxvalue.find('=');
            key = Maxvalue.substr(0,posTwo);
            pos = Maxvalue.find('#');
            value = Maxvalue.substr(posTwo+1,pos-posTwo-1);
            tMapStr.insert(std::make_pair(key,value));
            Maxvalue = Maxvalue.substr(pos+1,-1);
            if (pos==-1) {
                break;
            }
//            pos = Maxvalue.find('#');
        }
        m_paramsStr.insert(std::make_pair(Maxkey, tMapStr));
        pos = tempstr.find('&');
        tempstr = tempstr.substr(pos+1,-1);
    } while (pos!=-1);
    
    
    
//    log("%s",value.c_str());
//	if(seperatorpos == -1)
//    {
//        //如果没有&,就是一条整的命令
//        //m_paramsStr.push_back(tempstr)
//        pos = tempstr.find("=");
//        key = tempstr.substr(0, pos);
//
//		m_paramsStr.insert(std::make_pair(key, value));
//	}
//    else
//    {
//		//第一个是不是&,是就直接跳过
//		if(seperatorpos == 0)
//        {
//			tempstr = tempstr.substr(1,-1);
//		}
//		while(tempstr.length() > 0)
//        {
//			int seperatorpos = tempstr.find('#');
//			if(seperatorpos == -1)
//            {
//                //如果没有&,就是一条整的命令
//				//m_paramsStr.push_back(tempstr);
//                pos = tempstr.find("=");
//                key = tempstr.substr(0, pos);
//                value = tempstr.substr(pos + 1);
//                m_paramsStr.insert(std::make_pair(key, value));
//				break;
//			}
//			std::string oneInstructionstr = tempstr.substr(0,seperatorpos);
//			if(oneInstructionstr.length() > 0)
//            {
//				//m_paramsStr.push_back(oneInstructionstr);
//                pos = oneInstructionstr.find("=");
//                key = oneInstructionstr.substr(0, pos);
//                value = oneInstructionstr.substr(pos + 1);
//                m_paramsStr.insert(std::make_pair(key, value));
//			}
//			if(seperatorpos >= (int)(tempstr.length()) - 1)
//            {
//				break;
//			}
//			tempstr = tempstr.substr(seperatorpos + 1,-1);
//		}
//	}
	
}
/******************************************************************
 //funcName:parseNumberAfterEqualFromInstruction
 
 //date:2013/3/14 16:17
 
 //desc:根据一条指令解析出后面对应的数字,因为比较通用,所以提取出来
 比如 userid=1203
 type=4567
 
 //param:
 
 //ret value:=后面的数字
 
 //author:butcher
 ******************************************************************/
int _netNewRecvEventBase::parseNumberAfterEqualFromInstruction(const std::string& Maxkey,const std::string& key)
{
    std::map<std::string, std::string>::iterator str = m_paramsStr.find(Maxkey)->second.find(key);
    if (str == m_paramsStr.find(Maxkey)->second.end())
    {
        return 0;
    }
//	if(str.length() > 0)
//		return atoi(str.c_str());
	return atoi(str->second.c_str());
}
float _netNewRecvEventBase::parseFloatAfterEqualFromInstruction(const std::string& Maxkey,const std::string& key)
{
    std::string& str = m_paramsStr.find(Maxkey)->second.find(key)->second;
	if(str.length() > 0)
		return (float)(atof(str.c_str()));
	return 0;
}

/******************************************************************
 //funcName:parseNumberAfterEqualFromInstruction
 
 //date:2013/3/14 16:17
 
 //desc:根据一条指令解析出后面对应的数字,因为比较通用,所以提取出来
 比如 username=中国
 
 //param:
 
 //ret value:中国
 
 //author:butcher
 ******************************************************************/
std::string _netNewRecvEventBase::parseStrAfterEqualFromInstruction(const std::string& Maxkey,const std::string& key)
{
    std::string str = m_paramsStr.find(Maxkey)->second.find(key)->second;
	return str;
}
/******************************************************************
 //funcName:parseHasEqualInstructionKeyname
 
 //date:2013/10/21
 
 //desc:获取一个含有=指令的key
 比如 userid=1234
 返回"userid"
 
 //param:
 
 //ret value:
 
 //author:zzb
 ******************************************************************/
/*std::string _netNewRecvEventBase::parseHasEqualInstructionKeyname(const std::string& key)
{
	int pos = str.find('=');
	CCAssert(pos != -1,"");
	if(pos == -1)
		return 0;
	return str.substr(0,pos);
}*/
