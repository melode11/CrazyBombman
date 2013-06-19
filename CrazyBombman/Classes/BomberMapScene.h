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
#endif /* defined(__CrazyBomber__BomberMapScene__) */
class BomberMapScene : public cocos2d::CCLayer
{
private:
    cocos2d::CCTMXTiledMap *_tileMap;
    Simulation::Player *_player;
    
public:
    virtual bool init();
    
    virtual void didAccelerate(cocos2d::CCAcceleration* pAccelerationValue);
    
    static cocos2d::CCScene* scene();
    
    ~BomberMapScene();
    
    CREATE_FUNC(BomberMapScene);
};