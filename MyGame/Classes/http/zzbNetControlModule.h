//
//  zzbNetControlModule.h
//  GAME2
//
//  Created by zzb on 14-1-11.
//
//  私人使用的网络模块哟，大家别瞎搞的说···

#ifndef __GAME2__zzbNetControlModule__
#define __GAME2__zzbNetControlModule__

#include <iostream>
#include "cocos2d.h"
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
    void getEventDrawCard(cocos2d::Object*pTarget,cocos2d::SEL_CallFuncO phandler);//得到抽卡信息 hsx 0401
    /*
     *  登入
     *  hsx 0410
     */
    void Login(cocos2d::Object*pTarget,cocos2d::SEL_CallFuncO phandler);
    /*
     *  更新卡牌编队
     *  hsx 0412
     *  type 队伍类型 teamList 队伍信息
     */
    void UpdateTeamList(cocos2d::Object*pTarget,cocos2d::SEL_CallFuncO phandler,int type,std::string teamList,std::string cardList);
    /*
     *  更新个人卡牌
     *  hsx 0416
     *  cardList 卡牌信息
     */
    void UpdateCardList(cocos2d::Object*pTarget,cocos2d::SEL_CallFuncO phandler,std::string cardList);
    
    //申请好友
    void applyAddFriend(cocos2d::Object*pTarget,cocos2d::SEL_CallFuncO phandler,int senderId , int receiveId,std::string msg);
    
    //同意添加
    void agreeAddFriend(cocos2d::Object*pTarget,cocos2d::SEL_CallFuncO phandler,int senderId , int receiveId,int fmsgId,std::string msg);
    
    //拒绝添加
    void refuseAddFriend(cocos2d::Object*pTarget,cocos2d::SEL_CallFuncO phandler,int senderId , int receiveId,int fmsgId,std::string msg);
    
    //删除好友
    void deleteFriend(cocos2d::Object*pTarget,cocos2d::SEL_CallFuncO phandler,int friendId);
    
    //发送私信
    void sendMsgToFriend(cocos2d::Object*pTarget,cocos2d::SEL_CallFuncO phandler,
                         int friendId,std::string msg);
    
    //获取好友列表
    void getFriendList(cocos2d::Object*pTarget,cocos2d::SEL_CallFuncO phandler);
    
    //获取好友申请列表
    void getFriendApplyList(cocos2d::Object*pTarget,cocos2d::SEL_CallFuncO phandler);
    
    //获取未读消息列表
    void getFriendMsg(cocos2d::Object*pTarget,cocos2d::SEL_CallFuncO phandler);
    
    void updateMsgStatus(cocos2d::Object*pTarget,cocos2d::SEL_CallFuncO phandler,int fmsgId);
    
    //获取推荐好友
    void getRecommenList(cocos2d::Object*pTarget,cocos2d::SEL_CallFuncO phandler);
    
    //搜索好友
    void searchFriendId(cocos2d::Object*pTarget,cocos2d::SEL_CallFuncO phandler,int searchId);
    
    void refreshWorldMsg(cocos2d::Object*pTarget,cocos2d::SEL_CallFuncO phandler,int iUserId);
   
    void sendWorldMsg(cocos2d::Object*pTarget,cocos2d::SEL_CallFuncO phandler,int iUserid,std::string strMsg);
    /*
     *  修改用户名字
     *  hsx 0421
     *  name 用户名字
     */
    void UpdateUserName(cocos2d::Object *pTarget, cocos2d::SEL_CallFuncO phandler,std::string name);
    /*
     *  修改体力
     *  hsx 0421
     *  stamina 体力
     */
    void UpdateUserStamina(cocos2d::Object *pTarget, cocos2d::SEL_CallFuncO phandler,int stamina);
    /*
     *  绑定账号
     *  hsx 0421
     *  type 类型:邮箱，qq,iphone , mark 值 ,pass 密码
     */
    void BoundUserIdTOOtherId(cocos2d::Object *pTarget, cocos2d::SEL_CallFuncO phandler,int type,std::string mark,std::string pass);
    /*
     *  获取商店道具列表
     *  spf 2014-05-20 
     */
    void getBuyPropsList(cocos2d::Object *pTarget, cocos2d::SEL_CallFuncO phandler);
    /*
     *  获得助战好友列表
     *  hsx 0421
     */
    void buyBuyProps(cocos2d::Object *pTarget, cocos2d::SEL_CallFuncO phandler,int id);
    
    void getBattleBefore(cocos2d::Object *pTarget, cocos2d::SEL_CallFuncO phandler);
    /*
     *  战斗结束结算
     *  hsx 0421
     *  type,result,mapid,mapMinid,helpid,isFriend,dropGoods
     *  类型,战斗是否成功,关卡id,小关卡id,好友id(没有好友写0),是否是好友(1是,0不是),掉落（itemId,type,num   1,1,1@2,1,1）
     */
    void BattleAfter(cocos2d::Object *pTarget, cocos2d::SEL_CallFuncO phandler,int type,int result,int mapId,int mapMinId,int helpId,int isFriend,std::string dropGoods);
    
    //战斗复活
    void  BattleRevive(cocos2d::Object *pTarget, cocos2d::SEL_CallFuncO phandler);
    
    /*
     *  世界boss扣血
     *  hsx 0421
     *  hp 要扣多少血
     */
    void BattleWorldBoss(cocos2d::Object *pTarget, cocos2d::SEL_CallFuncO phandler,int hp);
    /*
     *  获取世界boss 排行榜
     *  hsx 0421
     */
    void getRankWorldBoss(cocos2d::Object *pTarget, cocos2d::SEL_CallFuncO phandler);
    /*
     *  保存抽卡结果
     *  hsx 0421
     *  type 抽卡类型，addnum 魔法石的次数，takeCard (1,1,1;2,2,2//物品类型,道具id,数量)
     *  物品类型：全部 0、英雄1、 碎片 2、材料3 、消耗品4
     */
    void SaveTakeOutCard(cocos2d::Object *pTarget, cocos2d::SEL_CallFuncO phandler,int type,int addNum,std::string takeCard);
    /*
     *  获取道具列表
     *  hsx 0421
     *  type 物品类型
     *  物品类型：全部:0
     */
    void getItemByType(cocos2d::Object *pTarget, cocos2d::SEL_CallFuncO phandler,int type);
    /*
     *  保存道具
     *  hsx 0421
     *  type 物品类型，itemId 物品id，num 物品数量，addOrcut=1 1为增加具体请参考服务器
     */
    void SaveItem(cocos2d::Object *pTarget, cocos2d::SEL_CallFuncO phandler,int type,int itemId,int num,int addOrCut=1);
    /*
     *  获取道具占用格子数
     *  hsx 0421
     *  
     */
    void getItemBagNum(cocos2d::Object *pTarget, cocos2d::SEL_CallFuncO phandler);
    /*
     *  刷新阵型
     *  type 阵型类型（0 战斗,1 抽卡）,formlationId 原阵型id
     */
    void refreshFormlation(cocos2d::Object *pTarget, cocos2d::SEL_CallFuncO phandler,int type,int formlationId);
    
    /*
     @brief 进化卡牌
     @param pTarget
     @param pHandler
     @param cardId 卡牌id(在数据库里的id)
     @param star 目标星级
     */
    void evolutionCard(cocos2d::Object *pTarget, cocos2d::SEL_CallFuncO pHandler, int cardId, int star,string cardInfo);
    
    /*
     @brief 升级卡牌
     @param pTarget
     @param pHandler
     @param cardId 卡牌id(数据库里的id)
     @param star 要升级的卡牌的当前星级
     @param costCardCnt 消耗的卡牌数
     */
    void upgradeCard(cocos2d::Object *pTarget, cocos2d::SEL_CallFuncO pHandler, int cardId, int star,string item,string cardInfo);
    
    /*
     * @brief 升级技能
     * @param pTarget
     * @param pHandler
     * @param targetSkillLevel 技能要升级到的目标等级
     * @param neededCardLevel 需要的卡牌等级
     */
    void upgradeSkill(cocos2d::Object *pTarget, cocos2d::SEL_CallFuncO pHandler, int targetSkillLevel, int neededCardLevel,string cardInfo);
    
    
    void AddHttpPackage(cocos2d::Object* pTarget,cocos2d::SEL_CallFuncO phandler,_netNewSendEventBase & event);
    bool GetShowHttpDialog();
    
    void SetHttpDialog(bool bShowHttpDialog);
    
    void getRegistrationInfo(cocos2d::Object *pTarget, cocos2d::SEL_CallFuncO phandler);//得到用户的签到信息
    void saveRegistrationInfo(cocos2d::Object *pTarget, cocos2d::SEL_CallFuncO phandler);//用户签到
    
    
};

#endif /* defined(__GAME2__zzbNetControlModule__) */
