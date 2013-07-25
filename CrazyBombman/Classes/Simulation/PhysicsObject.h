//
//  PhysicsObject.h
//  CrazyBombman
//
//  Created by Yao Melo on 7/21/13.
//
//

#ifndef __CrazyBombman__PhysicsObject__
#define __CrazyBombman__PhysicsObject__

#include <iostream>
#include "cocos2d.h"
#include "Box2D.h"
#include "AttachInfo.h"

namespace Simulation
{
class PhysicsObject :public cocos2d::CCObject
{
private:
    b2Body* _body;
public:
    PhysicsObject():_body(0)
    {
        
    }
    
    b2Body* getBody()
    {
        return _body;
    }
    
    void setBody(b2Body* body);
    
    void initBody(b2World *_world);
    
    void clearBody(b2World*_world);
    
    virtual ~PhysicsObject();
    
    
protected:
    virtual b2Body* createBody(b2World *_world) {CC_UNUSED_PARAM(_world); return NULL; };
    
    virtual AttachType getAttachType() {return AttachNone;};
    

};
}
#endif /* defined(__CrazyBombman__PhysicsObject__) */
