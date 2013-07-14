//
//  Mob.h
//  CrazyBombman
//
//  Created by Yao Melo on 7/14/13.
//
//

#ifndef __CrazyBombman__Mob__
#define __CrazyBombman__Mob__

#include <iostream>
#include "cocos2d.h"
#include "MobPrototype.h"
#include "ArtworkLoader.h"

using namespace cocos2d;

namespace Simulation
{
    
    class Mob:public CCObject
    {
        CC_SYNTHESIZE_READONLY(Level, _lvl, Level);
        CC_SYNTHESIZE_READONLY(float, _hp, Hitpoint);
        CC_SYNTHESIZE_READONLY(std::string, _name, Name);
        CC_SYNTHESIZE_READONLY(CCNode*, _node, Node);
        CC_SYNTHESIZE_READONLY(unsigned int, _id, Id);
    private:
        Direction _dir;
        CCAnimation* moveAnimation[4];
        CCAffineTransform transform[4];
        float _timeSinceLastFreeMove;
    public:
        Mob(unsigned int mobId,Level lvl,float hp,std::string const& name);
        
        ~Mob();
        
        virtual bool init();
        
        virtual void update(float dt);
        
        void freeMove();
        
        static Mob* create(unsigned int mobId,Level lvl,float hp,std::string const& name)
        {
            Mob* mob = new Mob(mobId,lvl,hp,name);
            if(mob->init())
            {
                mob->autorelease();
                return mob;
            }
            else{
                mob->release();
                return NULL;
            }
        }
    };
}
#endif /* defined(__CrazyBombman__Mob__) */
