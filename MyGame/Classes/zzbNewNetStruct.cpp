//
//  zzbNewNetStruct.cpp
//  GAME2
//
//   Created by spf on 14-7-21
//
//

#include "zzbNewNetStruct.h"

#define URL_ADDRESS "http://112.12.59.147:9090/"


NETNEWEVENTNAMEINF g_newEventNameInf[NET_NEW_EVENT_NR] =
{
    {NET_EVENT_DRAWCARD,"c=Card&m=takeOutCards","HoodleServer/ass"}
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
 std::string _netNewRecvEventBase::parseHasEqualInstructionKeyname(const std::string& key)
 {
 /*int pos = str.find('=');
 CCAssert(pos != -1,"");
 if(pos == -1)
 
 return str.substr(0,pos);*/
     return 0;
 }
