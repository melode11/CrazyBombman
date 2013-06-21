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
    class PlayerPositionDelegate
    {
    public:
        virtual void updatePlayerPostion(cocos2d::CCPoint& postion) = 0;
    };
}

#endif /* defined(__CrazyBombman__PlayerPositionDelegate__) */
