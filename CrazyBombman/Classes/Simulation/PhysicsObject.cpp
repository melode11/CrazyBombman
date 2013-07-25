//
//  PhysicsObject.cpp
//  CrazyBombman
//
//  Created by Yao Melo on 7/21/13.
//
//

#include "PhysicsObject.h"
#include "AttachInfo.h"
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
            void* userData = _body->GetUserData();
            if(userData)
            {
                _body->SetUserData(NULL);
                delete (AttachInfo*)userData;
            }
        }
        if(body)
        {
            AttachInfo* ai = new AttachInfo(getAttachType(), this);
            body->SetUserData(ai);
        }
        _body = body;
    }
    
    PhysicsObject::~PhysicsObject()
    {
        if(_body)
        {
            void* userData = _body->GetUserData();
            if(userData)
            {
                _body->SetUserData(NULL);

                delete (AttachInfo*)userData;

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