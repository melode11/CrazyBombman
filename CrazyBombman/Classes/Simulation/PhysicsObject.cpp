//
//  PhysicsObject.cpp
//  CrazyBombman
//
//  Created by Yao Melo on 7/21/13.
//
//

#include "PhysicsObject.h"

namespace Simulation
{
    void PhysicsObject::setBody(b2Body *body)
    {
        
        if(body == _body)
        {
            return;
        }
        if(_body)
        {
            _body->SetUserData(NULL);
        }
        if(body)
        {
            body->SetUserData(this);
        }
        _body = body;
    }
    
    PhysicsObject::~PhysicsObject()
    {
        if(_body)
        {
            void* userData = _body->GetUserData();
            if(userData == this)
            {
                _body->SetUserData(NULL);
            }
        }
    }
    
    void PhysicsObject::clearBody(b2World* _world)
    {
        if(_body)
        {
            b2Body* body = _body;
            setBody(NULL);
            _world->DestroyBody(body);
        }
    }
    
    void PhysicsObject::initBody(b2World* world)
    {
        b2Body* body = this->createBody(world);
        if(body)
        {
            this->setBody(body);
        }
    }
    
}