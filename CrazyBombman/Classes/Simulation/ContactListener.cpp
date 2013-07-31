//
//  ContactListener.cpp
//  CrazyBombman
//
//  Created by Yao Melo on 7/24/13.
//
//

#include "ContactListener.h"
#include "PhysicsObject.h"

namespace Simulation
{
    void ContactLisenter::BeginContact(b2Contact *contact)
    {
        PhysicsObject* phyObj =static_cast<PhysicsObject*>(contact->GetFixtureA()->GetBody()->GetUserData());
        PhysicsObject* phyObj2 =static_cast<PhysicsObject*>(contact->GetFixtureB()->GetBody()->GetUserData());
        phyObj->collideWith(phyObj2);
        phyObj2->collideWith(phyObj);
        printf("begin contact\n" );
    }
    
    void ContactLisenter::EndContact(b2Contact *contact)
    {
        printf("end contact\n" );
    }
   
}