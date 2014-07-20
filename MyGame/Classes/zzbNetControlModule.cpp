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
         // CDialogMgr::GetSingletonPtr()->createHttpDialog();
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
    //CDialogMgr::GetSingletonPtr()->removeHttpDialog();
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
        //CDialogMgr::GetSingletonPtr()->createDialog(hintBuffer.c_str(), this, menu_selector(CNetControlModule::onEventCallBackYes), this, menu_selector(CNetControlModule::onEventCallBackNo));
    }else if(m_nResendCount>=2)
    {
      //  CDialogMgr::GetSingletonPtr()->createDialog(hintBuffer.c_str(), this, menu_selector(CNetControlModule::onEventCallBackYes),NULL,NULL);
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


void CNetControlModule::getEventDrawCard(cocos2d::Object*pTarget,cocos2d::SEL_CallFuncO phandler)
{
    
    _netNewSendEventDrawCard event;
    string sz = event.generateContentStr();
    event.m_eventType = NET_EVENT_DRAWCARD;
    AddHttpPackage(pTarget,phandler,event);
}




