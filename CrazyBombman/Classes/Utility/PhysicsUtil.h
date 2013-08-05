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

namespace Utility
{
    b2Body* CreateBodyOutlined(b2World* world,cocos2d::CCRect const& rect,b2BodyType bodyType);
    b2Body* CreateBodyFilled(b2World* world,cocos2d::CCRect const& rect,b2BodyType bodyType);
    bool CropRect(cocos2d::CCRect& rect,float maxWidth = MOB_MAX_COLLIDE_SIZE,float maxHeight = MOB_MAX_COLLIDE_SIZE);
}
#endif /* defined(__CrazyBombman__PhysicsUtil__) */
