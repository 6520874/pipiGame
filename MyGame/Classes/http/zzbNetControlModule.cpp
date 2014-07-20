//
//  zzbNetControlModule.cpp
//  GAME2
//
//  Created by zzb on 14-1-11.
//
//

#include "zzbNetControlModule.h"
#include "cocos-ext.h"
#include "network/HttpClient.h"
#include "zzbNewNetStruct.h"
#include "zzbLayerNetCommunication.h"
#include "Dialog.h"

USING_NS_CC;
USING_NS_CC_EXT;

using namespace cocos2d::network;
static CNetControlModule* g_NetControlModule = NULL;
CNetControlModule* CNetControlModule::sharedNetControlModule()
{
    if (!g_NetControlModule)
    {
        g_NetControlModule = new CNetControlModule();
        g_NetControlModule->init();
    }
    return g_NetControlModule;
}

bool CNetControlModule::addHttpPackage(HTTP_PACKAGE& strPackage)
{
    m_lstNetPackage.push_back(strPackage);//添加在队尾
    return true;
}

bool CNetControlModule::init()
{
    if (!CCNode::init())
        return false;
    
    onEnter();
    onEnterTransitionDidFinish();
    scheduleUpdate();
    return true;
}
void CNetControlModule::update(float dt)
{
    CCNode::update(dt);
    if (m_lstNetPackage.size()>0 && !m_bIfSending)
    {
        m_bIfSending = true;
        sendHttpPackage(m_lstNetPackage.front());
    }
}
/*
 发送接收函数
 */
void CNetControlModule::sendHttpPackage(HTTP_PACKAGE& package)
{
    //开始发送前先将标志位设成true表示已经有消息在发送了
//    CLayerNetCommunication* pLayer = new CLayerNetCommunication();
//    pLayer->init();
//    Director::getInstance()->getRunningScene()->addChild(pLayer,999999);
      if(m_bShowHttpDialog)
      {
          CDialogMgr::GetSingletonPtr()->createHttpDialog();
      }
    m_bShowHttpDialog = true;
    log("%s",package.m_strHttpUrlDate.c_str());
    
    HttpRequest* request = new HttpRequest();
    request->setUrl(package.m_strHttpUrlDate.c_str());
    request->setRequestType(network::HttpRequest::Type::POST);
    request->setResponseCallback(this, httpresponse_selector(CNetControlModule::recvHttpPackage));
    request->setUserData((void*)package.m_nEventType);
    char buffer[10] = {0};//将event type作为标示
    sprintf(buffer, "%d",package.m_nEventType);
    request->setTag(buffer);
    
    HttpClient::getInstance()->setTimeoutForConnect(15);//等待时间设置为10秒
    HttpClient::getInstance()->setTimeoutForRead(15);
    HttpClient::getInstance()->send(request);
    request->release();
}

void CNetControlModule::recvHttpPackage(Node* node, void* data)
{
    HttpResponse *response = (HttpResponse*)data;
//    HttpRequest* request = response->getHttpRequest();
//    CLayerNetCommunication* pLayer = (CLayerNetCommunication*)request->getUserData();
//    pLayer->removeFromParentAndCleanup(true);
    CDialogMgr::GetSingletonPtr()->removeHttpDialog();
    char hintBuffer[127] = {0};
    
    if (!response)
    {
        /*
         消息发送错误
         */
        onBtnErrorHint("消息发送失败！\r\n请重试！");
        return;
    }
    int s= (int)response->getHttpRequest()->getRequestType();
    log("request type %d",s);
    
    
    if (0 != strlen(response->getHttpRequest()->getTag()))
    {
        log("%s ------>oked", response->getHttpRequest()->getTag());
    }
    
    int statusCode = response->getResponseCode();
    log("response code: %d", statusCode);
    
    
    char statusString[64] = {};
    sprintf(statusString, "HTTP Status Code: %d, tag = %s", statusCode, response->getHttpRequest()->getTag());
    log("%s",statusString);//可以根据不同的tag进行解析
    
    if (!response->isSucceed())
    {
        log("response failed");
        log("error buffer: %s", response->getErrorBuffer());
        onBtnErrorHint("网络请求错误！\r\n请重试!");
        return;
    }
    
    std::vector<char> *buffer = response->getResponseData();
    printf("Http Test, dump data: ");
    std::string sBuffer = "";
    for (unsigned int i = 0; i < buffer->size(); i++)
    {
        sBuffer += (*buffer)[i];
    }
    log("%s",sBuffer.c_str());
    
    /*
     判断返回的消息是否为空
     */
    if (sBuffer.size()<=0 && sBuffer.find("info=") == std::string::npos) {
        onBtnErrorHint("服务器返回的数据为空！\r\n请重试！");
        return;
    }
    /*
     根据htag判断是哪条消息，调用那个struct解析
     */
    int nEventType = atoi(response->getHttpRequest()->getTag());
    log("\r\nEvent type=%d",nEventType);
    
    _netNewRecvEventBase* pNetEvent = _netNewRecvEventBase::create(nEventType, sBuffer);
    if (!pNetEvent) {
        onBtnErrorHint("错误的命令！\r\n请重试！");
        return;
    }
    else if (pNetEvent->m_retCode != 0)
    {/*
      还要判断返回的info是否等于0 表示服务器返回的信息成功与否
      */
        memset(hintBuffer, 0, sizeof(hintBuffer));
        sprintf(hintBuffer, "服务器返回错误！info=%d\r\n请重试！",pNetEvent->m_retCode);
        onBtnErrorHint(hintBuffer);
        
        CC_SAFE_DELETE(pNetEvent);
        return;
    }
    if (m_lstNetPackage.size()<=0)
    {
        CC_SAFE_DELETE(pNetEvent);
        m_nResendCount = 0;
        m_bIfSending = false;
        return;
    }
    
    if (m_lstNetPackage.front().m_pTarget!=NULL && m_lstNetPackage.front().m_pHandler!=NULL)
    {
        (m_lstNetPackage.front().m_pTarget->*m_lstNetPackage.front().m_pHandler)(pNetEvent);
    }
    
    CC_SAFE_DELETE(pNetEvent);
    m_lstNetPackage.pop_front();//发送成功后从第一条从新开始发送
    //发送玩把标志位设成false，允许下一条消息继续发送
    m_bIfSending = false;
    m_nResendCount = 0;
}
/*
 弹出框点击确认后再点
 */
void CNetControlModule::onBtnErrorHint(std::string hintBuffer)
{
    m_nResendCount ++;
    if (m_nResendCount<=1) {
        onEventCallBackYes(NULL);
        return;
    }
    if (m_nResendCount>=5)
    {
        CDialogMgr::GetSingletonPtr()->createDialog(hintBuffer.c_str(), this, menu_selector(CNetControlModule::onEventCallBackYes), this, menu_selector(CNetControlModule::onEventCallBackNo));
    }else if(m_nResendCount>=2)
    {
        CDialogMgr::GetSingletonPtr()->createDialog(hintBuffer.c_str(), this, menu_selector(CNetControlModule::onEventCallBackYes),NULL,NULL);
    }else
    {
        ;
    }

}

void CNetControlModule::onEventCallBackYes(cocos2d::Object* pSender)
{
    m_bIfSending = false;
}

void CNetControlModule::onEventCallBackNo(cocos2d::Object* pSender)
{
//    m_lstNetPackage.pop_front();
//    m_bIfSending = false;
    //如果可以的话点取消就跳到登陆界面
    m_lstNetPackage.clear();
    m_bIfSending = false;
    m_nResendCount = 0;
    //LAYER_MANAGER->createScene(LAYER_TYPE_HELLO_WORLD,true,true);
}

CNetControlModule::CNetControlModule()
: m_bIfSending(false)
, m_nResendCount(0)
{
}

CNetControlModule::~CNetControlModule()
{
}


void CNetControlModule::AddHttpPackage(cocos2d::Object* pTarget,cocos2d::SEL_CallFuncO phandler,_netNewSendEventBase & event)
{
    HTTP_PACKAGE strPackage;
    strPackage.m_pTarget = pTarget;
    strPackage.m_pHandler = phandler;
    strPackage.m_nEventType = event.m_eventType;
    strPackage.m_strHttpUrlDate = event.generateSendStr();
    addHttpPackage(strPackage);
    
}
//TODO: 抽卡
//hsx 20140401
void CNetControlModule::getEventDrawCard(cocos2d::Object*pTarget,cocos2d::SEL_CallFuncO phandler)
{
    
    _netNewSendEventDrawCard event;
    event.m_eventType = NET_EVENT_DRAWCARD;
    AddHttpPackage(pTarget,phandler,event);
}
//TODO: 登入
void CNetControlModule::Login(cocos2d::Object* pTarget,cocos2d::SEL_CallFuncO phandler)
{
    _netNewSendLogin event;
    event.m_eventType = NET_EVENT_LOGIN;
    AddHttpPackage(pTarget,phandler,event);
}

//TODO: 更新卡牌编队
void CNetControlModule::UpdateTeamList(cocos2d::Object*pTarget,cocos2d::SEL_CallFuncO phandler,int type,std::string teamList,string cardList)
{
    _netNewSendUpdateTeamList event;
    event.m_eventType = NET_EVENT_TEAMLIST;
    event.type = type; 
    event.m_sTeamList = teamList;
    event.m_sCardList =  cardList;
    AddHttpPackage(pTarget,phandler,event);
}

//TODO: 更新个人卡牌
void CNetControlModule::UpdateCardList(cocos2d::Object*pTarget,cocos2d::SEL_CallFuncO phandler,std::string cardList)
{
    _netNewSendUpdateCardInfo event;
    event.m_eventType = NET_EVENT_UPDATE_CARD_INFO;
    event.m_sCardList = cardList;
    AddHttpPackage(pTarget,phandler,event);
}

//TODD: 申请好友
void CNetControlModule::applyAddFriend(cocos2d::Object*pTarget,cocos2d::SEL_CallFuncO phandler,int senderId,int receiveId,std::string msg)
 {
     _netNewSendApplyAddFriend event;
     event.m_eventType = NET_EVENT_APPLY_ADDFRIEND;
     event.senderId = senderId;
     event.receiveId = receiveId;
     event.msg = msg;
     AddHttpPackage(pTarget,phandler,event);
 }

//同意添加好友
void CNetControlModule::agreeAddFriend(cocos2d::Object*pTarget,cocos2d::SEL_CallFuncO phandler,int senderId ,int receiveId,
                                       int fmsgId,std::string msg)
{
    _netNewSendAgreeAddFriend event;
    event.m_eventType = NET_EVENT_AGREE_ADDFRIEND;
    event.senderId = senderId;
    event.receiveId = receiveId;
    event.msg = msg;
    event.fmsgId = fmsgId;
    AddHttpPackage(pTarget,phandler,event);
}

//拒绝添加好友
void CNetControlModule::refuseAddFriend(cocos2d::Object*pTarget,cocos2d::SEL_CallFuncO phandler,int senderId,int receiveId,
                                        int fmsgId,std::string msg)
{
    _netNewSendRefuseAddFriend event;
    event.m_eventType = NET_EVENT_REFUSE_ADDFRIEND;
    event.senderId = senderId;
    event.receiveId = receiveId;
    event.fmsgId = fmsgId;
    event.msg = msg;
    AddHttpPackage(pTarget,phandler,event);
}

//删除好友
void CNetControlModule::deleteFriend(cocos2d::Object*pTarget,cocos2d::SEL_CallFuncO phandler,int friendId)
{
    _netNewSendDeleteFriend event;
    event.m_eventType = NET_EVENT_DELETE_FRIEND;
    event.friendId = friendId;
    AddHttpPackage(pTarget,phandler,event);
}

//发送私信
void CNetControlModule::sendMsgToFriend(cocos2d::Object*pTarget,cocos2d::SEL_CallFuncO phandler,
                     int friendId ,std::string msg)
{
    _netNewSendMessgaeToFriend event;
    event.m_eventType = NET_EVENT_SEND_MESSAGE;
    event.friendId = friendId;
    event.msg = msg;
    AddHttpPackage(pTarget,phandler,event);
}

//获取我的好友列表
void CNetControlModule::getFriendList(cocos2d::Object*pTarget,cocos2d::SEL_CallFuncO phandler)
{
    _netNewSendGetFriendList  event;
    event.m_eventType = NET_EVENT_GET_FRIEND_LIST;
    AddHttpPackage(pTarget, phandler,event);
}

//获取申请好友列表
void CNetControlModule::getFriendApplyList(cocos2d::Object*pTarget,cocos2d::SEL_CallFuncO phandler)
{
    _netNewSendGetFriendApplyList event;
    event.m_eventType = NET_EVENT_GET_FRIEND_APPLY_LIST;
    AddHttpPackage(pTarget,phandler,event);
}

//获取私信列表
void CNetControlModule::getFriendMsg(cocos2d::Object*pTarget,cocos2d::SEL_CallFuncO phandler)
{
    _netNewSendGetFriendMessage event;
    event.m_eventType = NET_EVENT_GET_FRIEND_MSG;
    AddHttpPackage(pTarget,phandler,event);
}

//获取推荐好友列表
void CNetControlModule::getRecommenList(cocos2d::Object *pTarget, cocos2d::SEL_CallFuncO phandler)
{
    _netNewSendGetRecommendList event;
    event.m_eventType = NET_EVENT_GET_RECOMMEN_LIST;
    AddHttpPackage(pTarget,phandler,event);
}

//搜索好友
void CNetControlModule::searchFriendId(cocos2d::Object*pTarget,cocos2d::SEL_CallFuncO phandler,int searchId)
{
    _netNewSendSearchFriendId event;
    event.m_eventType = NET_EVENT_SEARCH_FRIEND_ID;
    event.searchId = searchId;
    AddHttpPackage(pTarget,phandler,event);
}

//更新私信消息状态
void CNetControlModule::updateMsgStatus(cocos2d::Object*pTarget,cocos2d::SEL_CallFuncO phandler,int fmsgId)
{

    _netNewSendUpdateMessageState event;
    event.m_eventType =  NET_EVENT_UPDATE_FRIEND_MSG_STATE;
    event.m_iFmsg = fmsgId;
    AddHttpPackage(pTarget,phandler,event);
}

//世界聊天
void CNetControlModule::refreshWorldMsg(cocos2d::Object*pTarget,cocos2d::SEL_CallFuncO phandler,int iId)
{
    _netNewSendRefreshWorldMsg event;
    event.m_eventType = NET_EVENT_REFRESH_WORLD_MSG;
    event.Id  = iId;
    AddHttpPackage(pTarget,phandler,event);
}

//发送世界聊天消息
void CNetControlModule::sendWorldMsg(cocos2d::Object*pTarget,cocos2d::SEL_CallFuncO phandler,int id,std::string strMsg)
{
    _netNewSendWorldTalk event;
    event.m_eventType = NET_EVENT_SEND_WORLD_MSG;
    event.Id  = id;
    event.sMsg = strMsg;
    AddHttpPackage(pTarget,phandler,event);
}

//TODO: 修改用户名字
void CNetControlModule::UpdateUserName(cocos2d::Object *pTarget, cocos2d::SEL_CallFuncO phandler,std::string name)
{
    _netNewEventUpdateUserName event;
    event.m_eventType = NET_EVENT_UPDATE_USER_NAME;
    event.userName = name;
    AddHttpPackage(pTarget,phandler,event);
}

//TODO: 修改体力
void CNetControlModule::UpdateUserStamina(cocos2d::Object *pTarget, cocos2d::SEL_CallFuncO phandler,int stamina)
{
    _netNewEventUpdateUserStamina event;
    event.m_eventType = NET_EVENT_UPDATE_USER_STAMINA;
    event.stamina = stamina;
    AddHttpPackage(pTarget,phandler,event);
}

//TODO: 绑定账号
void CNetControlModule::BoundUserIdTOOtherId(cocos2d::Object *pTarget, cocos2d::SEL_CallFuncO phandler,int type,std::string mark,std::string pass)
{
    _netNewEventBoundUserIdTOOtherId event;
    event.m_eventType = NET_EVENT_BOUND_USERID_TO_OTHERID;
    event.type = type;
    event.mark = mark;
    event.pass = pass;
    AddHttpPackage(pTarget,phandler,event);
}                                  
//TODO: 获取道具商城接口
void CNetControlModule::getBuyPropsList(cocos2d::Object *pTarget, cocos2d::SEL_CallFuncO phandler)
{
    _netNewEventShopList event;
    event.m_eventType = NET_EVENT_GET_PROPSHOP_LIST;
    AddHttpPackage(pTarget,phandler,event);
}

//购买道具
void CNetControlModule::buyBuyProps(cocos2d::Object *pTarget, cocos2d::SEL_CallFuncO phandler,int id)
{
    _netNewEventBuyBuyProps event;
    event.m_eventType  = NET_EVENT_BUYPROPS;
    event.iId = id;
    AddHttpPackage(pTarget,phandler,event);
}

//TODO: 获得助战好友列表
void CNetControlModule::getBattleBefore(cocos2d::Object *pTarget, cocos2d::SEL_CallFuncO phandler)
{
    _netNewEventBattleBefore event;
    event.m_eventType = NET_EVENT_BATTLE_BEFORE;
    AddHttpPackage(pTarget,phandler,event);
}
//TODO: 战斗结束结算
void CNetControlModule::BattleAfter(cocos2d::Object *pTarget, cocos2d::SEL_CallFuncO phandler,int type,int result,int mapId,int mapMinId,int helpId,int isFriend,std::string dropGoods)
{
    _netNewEventBattleAfter event;
    event.m_eventType = NET_EVENT_BATTLE_AFTER;
    event.type = type;
    event.result = result;
    event.mapId = mapId;
    event.mapMinId = mapMinId;
    event.helpId = helpId;
    event.isFriend = isFriend;
    event.dropGoods = dropGoods;
    AddHttpPackage(pTarget,phandler,event);
}

//战斗复活
void  CNetControlModule::BattleRevive(cocos2d::Object *pTarget, cocos2d::SEL_CallFuncO phandler)
{
    _netNewEventBattleRevive event;
    event.m_eventType  = NET_EVENT_BATTLE_REVIVE;
    AddHttpPackage(pTarget,phandler,event);
}
//TODO: 世界boss扣血

void CNetControlModule::BattleWorldBoss(cocos2d::Object *pTarget, cocos2d::SEL_CallFuncO phandler,int hp)
{
    _netNewEventBattleWorldBoss event;
    event.m_eventType = NET_EVENT_BATTLE_WORLD_BOSS;
    event.hurt = hp;
    AddHttpPackage(pTarget,phandler,event);
}
//TODO: 获取世界boss 排行榜
void CNetControlModule::getRankWorldBoss(cocos2d::Object *pTarget, cocos2d::SEL_CallFuncO phandler)
{
    _netNewEventGetRankWorldBoss event;
    event.m_eventType = NET_EVENT_GET_RANK_WORLD_BOSS;
    AddHttpPackage(pTarget,phandler,event);
}

//TODO: 保存抽卡结果
void CNetControlModule::SaveTakeOutCard(cocos2d::Object *pTarget, cocos2d::SEL_CallFuncO phandler,int type,int addNum,std::string takeCard)
{
    _netNewEventSaveTakeOutCard event;
    event.m_eventType = NET_EVENT_SAVE_TAKE_OUT_CARD;
    event.type = type;
    event.addNum = addNum;
    event.takeCard = takeCard;
    if (takeCard.length()<=0) {
        event.takeCard = "null";
    }
    AddHttpPackage(pTarget,phandler,event);
}
//TODO: 获取道具列表
void CNetControlModule::getItemByType(cocos2d::Object *pTarget, cocos2d::SEL_CallFuncO phandler,int type)
{
    _netNewEventGetItemByType event;
    event.m_eventType = NET_EVENT_GET_ITEM_BY_TYPE;
    event.type = type;
    AddHttpPackage(pTarget,phandler,event);
}
//TODO: 保存道具
void CNetControlModule::SaveItem(cocos2d::Object *pTarget, cocos2d::SEL_CallFuncO phandler,int type,int itemId,int num,int addOrCut)
{
    _netNewEventSaveItem event;
    event.m_eventType = NET_EVENT_SAVE_ITEM;
    event.type = type;
    event.itemId = itemId;
    event.num = num;
    event.addOrCut = addOrCut;
    
    AddHttpPackage(pTarget,phandler,event);
}

//TODO: 获取道具占用格子数
void CNetControlModule::getItemBagNum(cocos2d::Object *pTarget, cocos2d::SEL_CallFuncO phandler)
{
    _netNewEventGetItemBagNum event;
    event.m_eventType = NET_EVENT_GET_ITEM_BAG_NUM;
    
    AddHttpPackage(pTarget,phandler,event);
}

//TODO: 刷新阵型
void CNetControlModule::refreshFormlation(cocos2d::Object *pTarget, cocos2d::SEL_CallFuncO phandler,int type,int formlationId)
{
    _netNewEventRefreshFormlation event;
    event.m_eventType = NET_EVENT_REFRESH_FORMLATION;
    event.type = type;
    event.formlationId = formlationId;
    
    AddHttpPackage(pTarget,phandler,event);
}
//进化卡牌
void CNetControlModule::evolutionCard(cocos2d::Object *pTarget, cocos2d::SEL_CallFuncO pHandler, int cardId, int star,string cardInfo)
{
    _netNewEventEvolutionCard evt;
    evt.m_eventType = NET_EVENT_EVOLUTION_CARD;
    evt.cardId = cardId;
    evt.star = star;
    evt.cardInfo = cardInfo;
    
    AddHttpPackage(pTarget,pHandler,evt);
}

//升级卡牌
void CNetControlModule::upgradeCard(cocos2d::Object *pTarget, cocos2d::SEL_CallFuncO pHandler, int cardId, int star,string item,string cardInfo)
{
    _netNewEventUpgradeCard evt;
    evt.m_eventType = NET_EVENT_UPGRADE_CARD;
    evt.cardId = cardId;
    evt.star = star;
    evt.item = item;
    evt.pCardInfo = cardInfo;
    
    AddHttpPackage(pTarget,pHandler,evt);
}

//升级技能
void CNetControlModule::upgradeSkill(cocos2d::Object *pTarget, cocos2d::SEL_CallFuncO pHandler, int targetSkillLevel, int neededCardLevel,string cardInfo)
{
    _netNewEventSkillUpgrade evt;
    evt.m_eventType = NET_EVENT_SKILL_UPGRADE;
    evt.targetSkillLevel = targetSkillLevel;
    evt.neededCardLevel = neededCardLevel;
    evt.m_cardInfo = cardInfo;
    
    AddHttpPackage(pTarget,pHandler,evt);
}

bool CNetControlModule::GetShowHttpDialog()
{
    return  m_bShowHttpDialog;
}

void CNetControlModule::SetHttpDialog(bool bShowHttpDialog)
{
    m_bShowHttpDialog = bShowHttpDialog;
}

//TODO: 获取用户签到信息
void CNetControlModule::getRegistrationInfo(cocos2d::Object *pTarget, cocos2d::SEL_CallFuncO phandler)
{
    _netNewEventGetRegistration event;
    event.m_eventType = NET_EVENT_GET_REGISTRATION;
    
    AddHttpPackage(pTarget,phandler,event);
}
//保存签到信息
void CNetControlModule::saveRegistrationInfo(cocos2d::Object *pTarget, cocos2d::SEL_CallFuncO phandler)
{
    _netNewEventSaveRegistration event;
    event.m_eventType = NET_EVENT_SAVE_REGISTRATION;
    
    AddHttpPackage(pTarget,phandler,event);
}