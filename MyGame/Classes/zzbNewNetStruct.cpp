//
//  zzbNewNetStruct.cpp
//  GAME2
//
//  Created by zzb on 14-1-13.
//
//

#include "zzbNewNetStruct.h"

#define URL_ADDRESS "http://112.12.59.147:9090/"


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



_netNewRecvEventBase* _netNewRecvEventBase::create(const int& nEventType,const std::string&receiveCommand)
{
	_netNewRecvEventBase* pRecvEvent;
    std::string leftcommandstr = truncateCommandHeaderStr(receiveCommand);
	switch(nEventType)
    {
        case 1:break;
        
            return NULL;
	}
	pRecvEvent->m_eventType = nEventType;
	pRecvEvent->parseAllParams(leftcommandstr);
	pRecvEvent->init();
	return pRecvEvent;
}


std::string _netNewSendEventBase::generateSendStr()
{
	std::string sendstr = URL_ADDRESS;
    sendstr += getNewEventHeadStr(m_eventType);
    sendstr += "?";
	sendstr += getNewEventNameByEventType(m_eventType);
	sendstr += "&";
	std::string contentstr = generateContentStr();
   // std::string strHttp = CDBMgr::getInstance()->HttpEncrypt(contentstr);
    //__String *str = __String::createWithFormat("%s&cph=%s",contentstr.c_str(),strHttp.c_str());
    //contentstr = str->getCString();
	//sendstr += contentstr;
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
};