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
    
    void AddFixturesOutlined(b2Body* body,cocos2d::CCRect const& rect,CCPoint const& bodyCenter)
    {
        b2EdgeShape shape;
        
        b2Vec2 a(rect.getMinX(),rect.getMinY()),b(rect.getMinX(),rect.getMaxY()),c(rect.getMaxX(),rect.getMaxY()),d(rect.getMaxX(),rect.getMinY()),origin(bodyCenter.x,bodyCenter.y);
        a-=origin;b-=origin;c-=origin;d-=origin;
        shape.Set(a, b);
        body->CreateFixture(&shape,0);
        shape.Set(b, c);
        body->CreateFixture(&shape, 0);
        shape.Set(c, d);
        body->CreateFixture(&shape, 0);
        shape.Set(d, a);
        body->CreateFixture(&shape, 0);

    }
    
    void AddFixturesFilled(b2Body* body,cocos2d::CCRect const& rect,cocos2d::CCPoint const& bodyCenter)
    {
        CCSize size = rect.size;
        float hw = 0.5* size.width;
        float hh = 0.5* size.height;
        
        b2PolygonShape shape;
        CCPoint localCenter = rect.origin + ccp(hw,hh) - bodyCenter;
        shape.SetAsBox(hw, hh, CCPoint2Vec(localCenter), 0.0f);
        body->CreateFixture(&shape, 0);
    }
    
    b2Body* CreateBodyOutlined(b2World* world,CCRect const& rect,b2BodyType bodyType)
    {
        CCSize size = rect.size;
        float hw = 0.5* size.width;
        float hh = 0.5* size.height;
        CCPoint p =rect.origin + ccp(hw,hh);
        b2BodyDef bodyDef;
        bodyDef.type = bodyType;
        bodyDef.position = CCPoint2Vec(p);
        b2Body *body = world->CreateBody(&bodyDef);
        
        AddFixturesOutlined(body, rect, p);
        
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
        AddFixturesFilled(body, rect, p);
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