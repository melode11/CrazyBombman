//
//  PhysicsUtil.h
//  CrazyBombman
//
//  Created by Yao Melo on 7/16/13.
//
//

#ifndef __CrazyBombman__PhysicsUtil__
#define __CrazyBombman__PhysicsUtil__

#include <iostream>
#include "Box2D.h"
#include "cocos2d.h"

#define MOB_MAX_COLLIDE_SIZE 28
#define PLAYER_MAX_COLLIDE_SIZE 24
#define EXPLOSION_MAX_COLLIDE_SIZE 28
#define CCPoint2Vec(__x__) (b2Vec2(__x__.x,__x__.y))

namespace Utility
{
    b2Body* CreateBodyOutlined(b2World* world,cocos2d::CCRect const& rect,b2BodyType bodyType);
    b2Body* CreateBodyFilled(b2World* world,cocos2d::CCRect const& rect,b2BodyType bodyType);
    bool CropRect(cocos2d::CCRect& rect,float maxWidth = MOB_MAX_COLLIDE_SIZE,float maxHeight = MOB_MAX_COLLIDE_SIZE);
    
    void AddFixturesOutlined(b2Body* body,cocos2d::CCRect const& rect,cocos2d::CCPoint const& bodycenter);
    void AddFixturesFilled(b2Body* body,cocos2d::CCRect const& rect,cocos2d::CCPoint const& bodycenter);
}
#endif /* defined(__CrazyBombman__PhysicsUtil__) */
