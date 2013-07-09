//
//  AnimationLoader.h
//  CrazyBombman
//
//  Created by Yao Melo on 7/3/13.
//
//

#ifndef __CrazyBombman__AnimationLoader__
#define __CrazyBombman__AnimationLoader__

#include <iostream>
#include "cocos2d.h"
#include "Simulation.h"
namespace Utility
{
    class AnimationLoader
    {
    private:
        static cocos2d::CCAnimation* moveLeftAnimation;
        static cocos2d::CCAnimation* moveRightAnimation;
        static cocos2d::CCAnimation* moveUpAnimation;
        static cocos2d::CCAnimation* moveDownAnimation;
        
    public:
        static cocos2d::CCAnimation* explosionAnimation();
        
        static cocos2d::CCAnimation* walkingAnimation(Simulation::Direction dir);
    };
}
#endif /* defined(__CrazyBombman__AnimationLoader__) */
