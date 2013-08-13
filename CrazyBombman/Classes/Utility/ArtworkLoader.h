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
        
        /**
         * outputIsFlipped indicates if there's an additional flipped transform need to apply to CCSprite 
         * to make the animation correct. since the CCNode's additional transform not working as expected,
         * we set the bool flag instead of constructing the transform.
         */
        static cocos2d::CCAnimation* mobAnimation(unsigned int mobId,Simulation::Direction dir,bool* outputIsFlipped);
        
        static cocos2d::CCSprite* playerSprite()
        {
            cocos2d::CCTextureCache::sharedTextureCache() -> addImage("bombman.png");
            cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("bombman.plist");
            return cocos2d::CCSprite::createWithSpriteFrame(cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("ds-01.png"));
        }
        
        static cocos2d::CCTexture2D* mobsTexture()
        {
            return cocos2d::CCTextureCache::sharedTextureCache() -> addImage("monsters.png");
        }
        
        static cocos2d::CCSprite* mobSprite(unsigned int mobId)
        {
            cocos2d::CCTextureCache::sharedTextureCache() -> addImage("monsters.png");
            cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("monsters.plist");
            char fn[16];
            snprintf(fn, 16, "Mon_%02d.png",mobId*6+1);
            return cocos2d::CCSprite::createWithSpriteFrame(cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(fn));
        }
        
        static cocos2d::CCSprite* bombSprite()
        {
            return cocos2d::CCSprite::create("bomb.png");
        };
        
        static cocos2d::CCSprite* statusBarSprite()
        {
            return cocos2d::CCSprite::create("bottom-bar.png");
        }
    };
}
#endif /* defined(__CrazyBombman__ArtworkLoader__) */
