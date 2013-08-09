//
//  ContactFilter.cpp
//  CrazyBombman
//
//  Created by Yao Melo on 8/1/13.
//
//

#include "ContactFilter.h"
#include "PhysicsObject.h"

namespace Simulation {
    bool ContactFilter::ShouldCollide(b2Fixture *fixtureA, b2Fixture *fixtureB)
    {
        PhysicsObject* phyObj =static_cast<PhysicsObject*>(fixtureA->GetBody()->GetUserData());
        PhysicsObject* phyObj2 =static_cast<PhysicsObject*>(fixtureB->GetBody()->GetUserData());
        return phyObj->acceptCollide(phyObj2) & phyObj2->acceptCollide(phyObj);//use '&' instead of '&&' to make sure both routines are called.
    }
}