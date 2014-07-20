//
//  zzbNetControlModule.h
//  GAME2
//
//  Created by spf on 14-7-21
//
#ifndef __GAME2__zzbNetControlModule__
#define __GAME2__zzbNetControlModule__

#include <iostream>
#include "cocos2d.h"
#include <string>
using namespace std;
#include "zzbNewNetStruct.h"
//又是一个单例类，但是这个类貌似不保存数据的说
struct HTTP_PACKAGE
{
    int m_nEventType;//消息类型
    
    std::string m_strHttpUrlDate;
    /*
     每一个包都带回调函数
     */
    cocos2d::Object* m_pTarget;
    cocos2d::SEL_CallFuncO m_pHandler;
    //构造析构函数
    HTTP_PACKAGE():
    m_pTarget(NULL)
    ,m_pHandler(NULL)
    {}
    ~HTTP_PACKAGE(){}
};
class CNetControlModule:public cocos2d::Node
{
private:
    CNetControlModule();
    ~CNetControlModule();
    bool addHttpPackage(HTTP_PACKAGE& strPackage);
    void update(float dt);
    void sendHttpPackage(HTTP_PACKAGE& package);
private:
    bool init();
    void recvHttpPackage(cocos2d::Node* node,void* data);
    void onBtnErrorHint(std::string hintBuffer);
    void onEventCallBackYes(cocos2d::Object* pSender);
    void onEventCallBackNo(cocos2d::Object* pSender);
    bool m_bShowHttpDialog; //是否显示网络对话框
public:
    static CNetControlModule* sharedNetControlModule();
protected:
    std::list<HTTP_PACKAGE> m_lstNetPackage;//保存http发送的消息包
    
    bool m_bIfSending;//是否正在发送中
    int m_nResendCount;
public:
    void getEventDrawCard(cocos2d::Object*pTarget,cocos2d::SEL_CallFuncO phandler);//得到抽卡信息 hsx

    void AddHttpPackage(cocos2d::Object* pTarget,cocos2d::SEL_CallFuncO phandler,_netNewSendEventBase & event);
    

    bool GetShowHttpDialog();
    
    void SetHttpDialog(bool bShowHttpDialog);
    
};

#endif /* defined(__GAME2__zzbNetControlModule__) */
