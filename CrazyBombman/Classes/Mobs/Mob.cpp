//
//  Mob.cpp
//  CrazyBombman
//
//  Created by Yao Melo on 7/14/13.
//
//

#include "Mob.h"

namespace Simulation {
    
    Mob::Mob(unsigned int mobId,Level lvl,float hp,std::string const& name):_id(mobId),_lvl(lvl),_hp(hp),_name(name),_dir(eNone),_timeSinceLastFreeMove(0)
    {
        
        _node = Utility::ArtworkLoader::mobSprite(mobId);
        _node->retain();
        
        moveAnimation[0] = Utility::ArtworkLoader::mobAnimation(mobId, eDown, transform);
        moveAnimation[1] = Utility::ArtworkLoader::mobAnimation(mobId, eLeft, transform+1);
        moveAnimation[2] = Utility::ArtworkLoader::mobAnimation(mobId, eRight, transform+2);
        moveAnimation[3] = Utility::ArtworkLoader::mobAnimation(mobId, eUp, transform+3);
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
    }
    
    void Mob::freeMove()
    {
        int randIndex = (int)((rand()/(RAND_MAX+1.0))*4);
        printf("rand:%d",randIndex);
        Direction dirs[] = {eDown,eLeft,eRight,eUp};
        if(_dir != dirs[randIndex])
        {
            _node->setAdditionalTransform(transform[1]);
            _node->stopAllActions();
            _node->runAction(CCRepeatForever::create(CCAnimate::create(moveAnimation[randIndex])));
            _dir = dirs[randIndex];
        }

    }
}