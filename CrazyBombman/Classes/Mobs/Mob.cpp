//
//  Mob.cpp
//  CrazyBombman
//
//  Created by Yao Melo on 7/14/13.
//
//

#include "Mob.h"

namespace Simulation {
    
    Mob::Mob(unsigned int mobId,Level lvl,float hp,std::string const& name,float velocity):_id(mobId),_lvl(lvl),_hp(hp),_name(name),_dir(eNone),_timeSinceLastFreeMove(0),_velocity(velocity)
    {
        
        _node = Utility::ArtworkLoader::mobSprite(mobId);
        _node->retain();
        
        moveAnimation[0] = Utility::ArtworkLoader::mobAnimation(mobId, eDown, isFlipped);
        moveAnimation[1] = Utility::ArtworkLoader::mobAnimation(mobId, eLeft, isFlipped+1);
        moveAnimation[2] = Utility::ArtworkLoader::mobAnimation(mobId, eRight, isFlipped+2);
        moveAnimation[3] = Utility::ArtworkLoader::mobAnimation(mobId, eUp, isFlipped+3);
        for (int i = 0; i<4; ++i) {
            moveAnimation[i]->retain();
        }
        freeMove();
    }
    
    Mob::~Mob()
    {
        CC_SAFE_RELEASE(_node);
        for (int i = 0; i<4; ++i) {
            CCAnimation* anim = moveAnimation[i];
            CC_SAFE_RELEASE(anim);
        }
    }
    
    bool Mob::init()
    {
        return true;
    }
    
    void Mob::update(float dt)
    {
        _timeSinceLastFreeMove+=dt;
        if(_timeSinceLastFreeMove>MOB_KEEP_DIR_INTERVAL)
        {
            freeMove();
            _timeSinceLastFreeMove = 0;
        }
        float dx,dy;
        switch (_dir) {
            case eLeft:
                dx = - (dt* _velocity);
                break;
            case eUp:
                dy = (dt* _velocity);
                break;
            case eRight:
                dx = (dt* _velocity);
                break;
            case eDown:
                dy = - (dt* _velocity);
                break;
                
            default:
                break;
        }
        cocos2d::CCPoint p = _node -> getPosition();
        p.x += dx;
        p.y += dy;
        _node->setPosition(p);
    }
    
    void Mob::freeMove()
    {
        int randIndex = (int)((rand()/(RAND_MAX+1.0))*4);
        Direction dirs[] = {eDown,eLeft,eRight,eUp};
        if(_dir != dirs[randIndex])
        {
            if(isFlipped[randIndex])
            {
                _node->setScaleX(-1.0f);
            }
            else
            {
                _node->setScaleX(1.0f);
            }
            _node->stopAllActions();
            _node->runAction(CCRepeatForever::create(CCAnimate::create(moveAnimation[randIndex])));
            _dir = dirs[randIndex];
        }

    }
}