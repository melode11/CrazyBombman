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
        return (phyObj->getPhysicalType() != PhysPlayer && phyObj->getPhysicalType() != PhysMob)||(phyObj2->getPhysicalType() != PhysPlayer && phyObj2->getPhysicalType() != PhysMob);
    }
}