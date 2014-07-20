//
//  zzbLayerNetCommunication.cpp
//  GAME2
//
//  Created by zzb on 13-10-16.
//
//

#include "zzbLayerNetCommunication.h"
#include "Utilty.h"

std::string netAction1[4] = {
    "httpImage/net_action1_1.png",
    "httpImage/net_action1_2.png",
    "httpImage/net_action1_3.png",
    "httpImage/net_action1_4.png",
};

CLayerNetCommunication::CLayerNetCommunication()
{
    m_pSprite = NULL;
}
CLayerNetCommunication::~CLayerNetCommunication()
{

}
void CLayerNetCommunication::initDialogUI()
{
    m_pSprite = CSpriteBase::create("httpImage/net_action1_4.png");
    m_pSprite->setPosition(Point::ZERO);
    m_pSprite->setAnchorPoint(Point::ZERO);
    addChild(m_pSprite);
    Animate * animate = Utilty::createAnimateByPngs(4, "httpImage/net_action1_", 0.2f, 0);
    m_pSprite->runAction(RepeatForever::create(animate));
}



