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
#include "StatusBarLayer.h"

class BomberMapScene : public cocos2d::CCLayer, public Simulation::GameModelDelegate
{
private:
    cocos2d::CCTMXTiledMap *_tileMap;
    Simulation::Environment *_env;
    StatusBar* _statusBarWeakRef;
#ifdef PHYSICS_DEBUG
    cocos2d::extension::GLESDebugDraw* _debugDraw;
#endif
protected:
    void pushGameoverScreen();
public:
    static cocos2d::CCScene* scene();
    
    virtual bool init();
    
    virtual void didAccelerate(cocos2d::CCAcceleration* pAccelerationValue);
    
    void updateGameStatus(Simulation::GameStatus const& status);
    
    virtual void addNode(cocos2d::CCNode *node,int z_order);
    
    virtual void removeNode(cocos2d::CCNode *node);
    
    virtual void onGameResult(Simulation::GameResult result);
    
    virtual void ccTouchesEnded(cocos2d::CCSet *pTouch, cocos2d::CCEvent *pEvent);
    
    virtual void draw();
    
    BomberMapScene();
    
    ~BomberMapScene();
    
    CREATE_FUNC(BomberMapScene);
};

#endif /* defined(__CrazyBomber__BomberMapScene__) */