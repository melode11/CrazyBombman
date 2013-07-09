//
//  ArtworkLoader.cpp
//  CrazyBombman
//
//  Created by Yao Melo on 7/3/13.
//
//

#include "ArtworkLoader.h"
namespace Utility
{
    cocos2d::CCAnimation* ArtworkLoader::moveUpAnimation = NULL;
    
    cocos2d::CCAnimation* ArtworkLoader::moveDownAnimation = NULL;
    
    cocos2d::CCAnimation* ArtworkLoader::moveLeftAnimation = NULL;
    
    cocos2d::CCAnimation* ArtworkLoader::moveRightAnimation = NULL;
    
    using namespace cocos2d;
    
    CCArray* framesArrayWithNames(const std::string * file,...)
    {
        CCArray* arr = CCArray::create();
        do {
            CC_BREAK_IF(file);
            va_list args;
            const std::string* fileName = file;
            va_start(args, file);
            for(;fileName!=NULL;fileName = va_arg(args, const std::string*))
            {
                CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName((*fileName).data());
                if(frame)
                {
                    arr->addObject(frame);
                }
            }

        } while (0);
        return arr;
    }
    
    CCAnimation* ArtworkLoader::explosionAnimation()
    {
        CCArray *frames = CCArray::create();
        for(int i = 0;i<4;i++)
        {
            for(int j = 0;j<4;j++)
            {
                CCSpriteFrame* frame = CCSpriteFrame::create("explode.png",  CCRectMake(j*32, i*32, 32, 32));
                frames->addObject(frame);
                
            }
        }
        return CCAnimation::createWithSpriteFrames(frames,0.1);
    }
    
    CCAnimation* ArtworkLoader::walkingAnimation(Simulation::Direction dir)
    {
        CCTextureCache::sharedTextureCache() -> addImage("bombman.png");
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("bombman.plist");
        unsigned int startIndex;
        CCAnimation** animation;
       
        switch (dir) {
            case Simulation::eLeft:
                if(moveLeftAnimation)
                {
                    return moveLeftAnimation;
                }
                animation = &moveLeftAnimation;
                startIndex = 16;
                break;
            case Simulation::eRight:
                if (moveRightAnimation) {
                    return moveRightAnimation;
                }
                animation = &moveRightAnimation;
                startIndex = 6;
                break;
            case Simulation::eUp:
                if(moveUpAnimation)
                {
                    return moveUpAnimation;
                }
                animation = &moveUpAnimation;
                startIndex = 11;
                break;
            case Simulation::eDown:
                startIndex = 1;
                if(moveDownAnimation)
                {
                    return moveDownAnimation;
                }
                animation = &moveDownAnimation;
                break;
            default:
                return NULL;
        }
        char fileName[10];
        CCArray* arr = CCArray::create();
        for (int i = 0; i<5; ++i,++startIndex) {
            snprintf(fileName, 10, "ds-%02d.png",startIndex);
             CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(fileName);
            arr->addObject(frame);
        }
        *animation = CCAnimation::createWithSpriteFrames(arr,0.1);
        (*animation)->retain();
        return *animation;
    }
}