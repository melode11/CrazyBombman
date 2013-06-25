//
//  Explosion.cpp
//  CrazyBombman
//
//  Created by Yao Melo on 6/23/13.
//
//

#include "Explosion.h"
#include "Simulation.h"

namespace Simulation
{
    Explosion::Explosion():_animateNodes(),_range(EXPLOSION_RANGE)
    {
        
    }
    
    Explosion::~Explosion()
    {

    }
    
    void Explosion::update(float dt)
    {
        
        for (std::vector<AnimatedNode>::iterator it=_animateNodes.begin(); it!=_animateNodes.end(); it++) {
            cocos2d::CCNode* node =  it->getNode();
            cocos2d::CCAction *anim = it->getAction();
            if(!it->isAnimated && anim && node)
            {
                node->runAction(anim);
            }
            else if(anim && anim->isDone())
            {
                node->getParent()->removeChild(node);
                _animateNodes.erase(it);
            }
        }
        
    }
    
    bool Explosion::init()
    {
        return true;
    }
    

    void Explosion::createNodesAt(cocos2d::CCPoint const& center)
    {
        using namespace cocos2d;

        CCSprite *explode = NULL;
        CCArray *frames = CCArray::create();
        for(int i = 0;i<4;i++)
        {
            for(int j = 0;j<4;j++)
            {
                CCSpriteFrame* frame = CCSpriteFrame::create("explode.png",  CCRectMake(j*32, i*32, 32, 32));
                frames->addObject(frame);
                if(!explode)
                {
                    explode = CCSprite::createWithSpriteFrame(frame);
                    explode->setPosition(center);
                }
            }
        }
        CCAnimation *animation = CCAnimation::create();
        animation->createWithSpriteFrames(frames,0.1);
        CCAnimate* action = CCAnimate::create(animation);
        AnimatedNode node;
        node.setAction(action);
        node.setNode(explode);
        _animateNodes.push_back(node);
    }
}