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
#include "Delegations.h"
#include "GLES-Render.h"

class BomberMapScene : public cocos2d::CCLayer, public Simulation::GameModelDelegate
{
private:
    cocos2d::CCTMXTiledMap *_tileMap;
    Simulation::Environment *_env;
#ifdef PHYSICS_DEBUG
    cocos2d::extension::GLESDebugDraw* _debugDraw;
#endif
    
public:
    static cocos2d::CCScene* scene();
    
    virtual bool init();
    
    virtual void didAccelerate(cocos2d::CCAcceleration* pAccelerationValue);
    
    virtual void updatePlayerPostion(cocos2d::CCPoint& postion);
    
    virtual void addNode(cocos2d::CCNode *node,int z_order);
    
    virtual void removeNode(cocos2d::CCNode *node);
    
    virtual void ccTouchesEnded(cocos2d::CCSet *pTouch, cocos2d::CCEvent *pEvent);
    
    virtual void draw();
    
    ~BomberMapScene();
    
    CREATE_FUNC(BomberMapScene);
};

#endif /* defined(__CrazyBomber__BomberMapScene__) */