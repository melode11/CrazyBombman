//
//  PlayerPositionDelegate.h
//  CrazyBombman
//
//  Created by Yao Melo on 6/21/13.
//
//

#ifndef __CrazyBombman__PlayerPositionDelegate__
#define __CrazyBombman__PlayerPositionDelegate__

#include <iostream>
#include "cocos2d.h"
#include "Simulation.h"

namespace Simulation
{
    struct GameStatus
    {
        float playerHP;
        unsigned int mobCount;
        cocos2d::CCPoint playerPosition;
    };
    
    class GameModelDelegate
    {
    public:
        virtual void onGameResult(GameResult result) = 0;
        virtual void addNode(cocos2d::CCNode *node,int z_order) = 0;
        virtual void removeNode(cocos2d::CCNode *node) = 0;
        virtual void updateGameStatus(GameStatus const& status) = 0;
    };
    
    class CollisionDetectDelegate
    {
    public:
        virtual bool checkMoveCollision(cocos2d::CCPoint& dest,cocos2d::CCPoint const& start,cocos2d::CCSize const& subjectSize) = 0;
    };
}

#endif /* defined(__CrazyBombman__PlayerPositionDelegate__) */
