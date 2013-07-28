//
//  PhysicsUtil.cpp
//  CrazyBombman
//
//  Created by Yao Melo on 7/16/13.
//
//

#include "PhysicsUtil.h"
namespace Utility
{
    using namespace cocos2d;
    
    b2Body* CreateBodyForRect(b2World* world,CCRect const& rect)
    {
        return CreateBodyForRect(world, rect, b2_dynamicBody);
    }
    
    b2Body* CreateBodyForRect(b2World* world,cocos2d::CCRect const& rect,b2BodyType bodyType)
    {
        b2PolygonShape shape;
        CCSize size = rect.size;
        CCPoint p = rect.origin + ccp(0.5*size.width,0.5*size.height);
        
        shape.SetAsBox(size.width*0.5, size.height*0.5);
        b2BodyDef bodyDef;
        bodyDef.type = bodyType;
        bodyDef.position = b2Vec2(p.x,p.y);
        b2Body *body = world->CreateBody(&bodyDef);
        body->CreateFixture(&shape, 0);
        return body;
    }
}