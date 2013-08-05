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
    
    b2Body* CreateBodyOutlined(b2World* world,CCRect const& rect,b2BodyType bodyType)
    {
        CCSize size = rect.size;
        float hw = 0.5* size.width;
        float hh = 0.5* size.height;
        CCPoint p = rect.origin + ccp(hw,hh);
        
        b2BodyDef bodyDef;
        bodyDef.type = bodyType;
        bodyDef.position = b2Vec2(p.x,p.y);
        b2Body *body = world->CreateBody(&bodyDef);
        
     
        b2EdgeShape shape;
        shape.Set(b2Vec2(-hw,-hh), b2Vec2(-hw,hh));
        body->CreateFixture(&shape,0);
        shape.Set(b2Vec2(-hw,hh), b2Vec2(hw,hh));
        body->CreateFixture(&shape, 0);
        shape.Set(b2Vec2(hw,hh), b2Vec2(hw,-hh));
        body->CreateFixture(&shape, 0);
        shape.Set(b2Vec2(hw,-hh), b2Vec2(-hw,-hh));
        body->CreateFixture(&shape, 0);
        return body;
    }
    
    
    b2Body* CreateBodyFilled(b2World* world,cocos2d::CCRect const& rect,b2BodyType bodyType)
    {
        CCSize size = rect.size;
        float hw = 0.5* size.width;
        float hh = 0.5* size.height;
        CCPoint p = rect.origin + ccp(hw,hh);
        
        b2BodyDef bodyDef;
        bodyDef.type = bodyType;
        bodyDef.position = b2Vec2(p.x,p.y);
        b2Body *body = world->CreateBody(&bodyDef);
        
        b2PolygonShape shape;
        shape.SetAsBox(size.width*0.5, size.height*0.5);
        body->CreateFixture(&shape, 0);
        
        return body;
    }
    
    bool CropRect(cocos2d::CCRect& rect,float maxWidth,float maxHeight)
    {
        bool isCropped = false;
        if(rect.size.width>maxWidth)
        {
            float offset = rect.size.width - maxWidth;
            rect.origin.x+=0.5*offset;
            rect.size.width-=offset;
            isCropped = true;
        }
        if(rect.size.height>maxHeight)
        {
            float offset = rect.size.height - maxHeight;
            rect.origin.y+=0.5*offset;
            rect.size.height-=offset;
            isCropped = true;
        }
        return isCropped;
    }
}