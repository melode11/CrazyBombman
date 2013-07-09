//
//  ArtworkLoader.h
//  CrazyBombman
//
//  Created by Yao Melo on 7/3/13.
//
//

#ifndef __CrazyBombman__ArtworkLoader__
#define __CrazyBombman__ArtworkLoader__

#include <iostream>
#include "cocos2d.h"
#include "Simulation.h"

namespace Utility
{
    class ArtworkLoader
    {
    private:
        static cocos2d::CCAnimation* moveLeftAnimation;
        static cocos2d::CCAnimation* moveRightAnimation;
        static cocos2d::CCAnimation* moveUpAnimation;
        static cocos2d::CCAnimation* moveDownAnimation;
        
    public:
        static cocos2d::CCAnimation* explosionAnimation();
        
        static cocos2d::CCAnimation* walkingAnimation(Simulation::Direction dir);
        
        static cocos2d::CCSprite* playerSprite()
        {
            cocos2d::CCTextureCache::sharedTextureCache() -> addImage("bombman.png");
            cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("bombman.plist");
            return cocos2d::CCSprite::createWithSpriteFrame(cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("ds-01.png"));
        }
        
        static cocos2d::CCSprite* bombSprite()
        {
            return cocos2d::CCSprite::create("bomb.png");
        };
    };
}
#endif /* defined(__CrazyBombman__ArtworkLoader__) */
