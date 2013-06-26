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
    Explosion::Explosion():_animateNodes(),_range(EXPLOSION_RANGE),_isFinished(false)
    {
        
    }
    
    Explosion::~Explosion()
    {

    }
    
    void Explosion::update(float dt)
    {
        bool isFinished = true;
        for (std::vector<AnimatedNode>::iterator it=_animateNodes.begin(); it!=_animateNodes.end();) {
            cocos2d::CCNode* node =  it->getNode();
            cocos2d::CCAction *anim = it->getAction();
            if(!it->isAnimated && anim && node)
            {
                node->setVisible(true);
                node->runAction(anim);
                it->isAnimated = true;
                isFinished = false;
            }
            else if(anim && anim->isDone())
            {
                node->getParent()->removeChild(node);
                it = _animateNodes.erase(it);
                continue;
            }
            else
            {
                isFinished = false;
            }
            it++;
        }
        _isFinished = isFinished;
        
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
                    explode->setVisible(false);
                }
            }
        }
        CCAnimation *animation = CCAnimation::createWithSpriteFrames(frames,0.1);

        CCAnimate* action = CCAnimate::create(animation);
        AnimatedNode node;
        node.setAction(action);
        node.setNode(explode);
        _animateNodes.push_back(node);
    }
    
    unsigned int Explosion::getNodesCount()
    {
        return _animateNodes.size();
    }
    
    cocos2d::CCNode* Explosion::getNodeAt(unsigned int index)
    {
        return _animateNodes[index].getNode();
    }
    
    bool Explosion::isFinished()
    {
        return _isFinished;
    }
}