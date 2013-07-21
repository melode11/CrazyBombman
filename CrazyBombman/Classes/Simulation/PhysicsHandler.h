//
//  PhysicsHandler.h
//  CrazyBombman
//
//  Created by Yao Melo on 7/21/13.
//
//

#ifndef __CrazyBombman__PhysicsHandler__
#define __CrazyBombman__PhysicsHandler__

#include <iostream>
#include "cocos2d.h"
#include "Box2D.h"
#include "Player.h"
#include "Explosion.h"
#include "Mob.h"
#include "PhysicsObject.h"

namespace Simulation
{
    class PhysicsHandler : public cocos2d::CCObject
    {
    public:
        void buildPhysicsMap(cocos2d::CCTMXTiledMap* tilemap);
        void addPlayerBody(Player* player);
        void addExplosionBody(Explosion* explosion);
        void addMobBody(Mob* mob);
        void removeBody(PhysicsObject* obj);
        
    private:
        b2World *_world;
    };
}
#endif /* defined(__CrazyBombman__PhysicsHandler__) */
