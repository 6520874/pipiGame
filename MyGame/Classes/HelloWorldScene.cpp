#include "HelloWorldScene.h"
#include "zzbLayerNetCommunication.h"
#include "zzbNetControlModule.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance

void   HelloWorld::_GetDrawCard(Object *pSender)
{
    

}

bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
   
    
    CNetControlModule::sharedNetControlModule()->getEventDrawCard(this,callfuncO_selector(HelloWorld::_GetDrawCard));
    
    return true;
}


void HelloWorld::menuCloseCallback(Object* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
