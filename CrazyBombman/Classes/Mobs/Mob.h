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
#include "PhysicsObject.h"

using namespace cocos2d;

namespace Simulation
{
    
    class Mob:public PhysicsObject
    {
        CC_SYNTHESIZE_READONLY(Level, _lvl, Level);
        CC_SYNTHESIZE_READONLY(float, _hp, Hitpoint);
        CC_SYNTHESIZE_READONLY(std::string, _name, Name);
        CC_SYNTHESIZE_READONLY(CCNode*, _node, Node);
        CC_SYNTHESIZE_READONLY(unsigned int, _id, Id);
    private:
        float _velocity;
        Direction _dir;
        CCAnimation* moveAnimation[4];
        bool isFlipped[4];
        float _timeSinceLastFreeMove;
    public:
        Mob(unsigned int mobId,Level lvl,float hp,std::string const& name,float velocity);
        
        ~Mob();
        
        virtual bool init();
        
        virtual void update(float dt);
        
        void freeMove();
        
        bool isDead();
        
        static Mob* create(unsigned int mobId,Level lvl,float hp,std::string const& name,float velocity)
        {
            Mob* mob = new Mob(mobId,lvl,hp,name,velocity);
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
        
        virtual PhysicalType getPhysicalType() {return PhysMob;};
        
        virtual void collideWith(PhysicsObject* other);
        
        virtual bool acceptCollide(Simulation::PhysicsObject *other);
        
    protected:
        virtual b2Body* createBody(b2World *world);
    };
}
#endif /* defined(__CrazyBombman__Mob__) */
