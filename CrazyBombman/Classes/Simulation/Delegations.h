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
namespace Simulation
{
    
    class GameModelDelegate
    {
    public:
        virtual void updatePlayerPostion(cocos2d::CCPoint& postion) = 0;
        virtual void addNode(cocos2d::CCNode *node,int z_order) = 0;
        virtual void removeNode(cocos2d::CCNode *node) = 0;
    };
}

#endif /* defined(__CrazyBombman__PlayerPositionDelegate__) */
