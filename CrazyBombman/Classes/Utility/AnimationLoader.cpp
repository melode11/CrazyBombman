//
//  AnimationLoader.cpp
//  CrazyBombman
//
//  Created by Yao Melo on 7/3/13.
//
//

#include "AnimationLoader.h"
namespace Utility
{
    using namespace cocos2d;
    CCAnimation* AnimationLoader::explosionAnimation()
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
}