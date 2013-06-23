//
//  BomberMapScene.h
//  CrazyBomber
//
//  Created by Yao Melo on 6/17/13.
//
//

#ifndef __CrazyBomber__BomberMapScene__
#define __CrazyBomber__BomberMapScene__

#include <iostream>
#include "cocos2d.h"
#include "Player.h"
#include "Environment.h"
#include "PlayerPositionDelegate.h"

class BomberMapScene : public cocos2d::CCLayer, public Simulation::PlayerPositionDelegate
{
private:
    cocos2d::CCTMXTiledMap *_tileMap;
    Simulation::Environment *_env;
    
public:
    static cocos2d::CCScene* scene();
    
    virtual bool init();
    
    virtual void didAccelerate(cocos2d::CCAcceleration* pAccelerationValue);
    
    virtual void updatePlayerPostion(cocos2d::CCPoint& postion);
    
    virtual void ccTouchesEnded(cocos2d::CCSet *pTouch, cocos2d::CCEvent *pEvent);
    
    ~BomberMapScene();
    
    CREATE_FUNC(BomberMapScene);
};

#endif /* defined(__CrazyBomber__BomberMapScene__) */