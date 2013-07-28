//
//  ContactListener.h
//  CrazyBombman
//
//  Created by Yao Melo on 7/24/13.
//
//

#ifndef __CrazyBombman__ContactListener__
#define __CrazyBombman__ContactListener__

#include <iostream>
#include "Box2D.h"

namespace Simulation {
    class ContactLisenter:public b2ContactListener,public b2ContactFilter
    {
        virtual void BeginContact(b2Contact* contact);
        
        virtual void EndContact(b2Contact* contact);
 
        virtual bool ShouldCollide(b2Fixture* fixtureA, b2Fixture* fixtureB);
    };
}

#endif /* defined(__CrazyBombman__ContactListener__) */
