//
//  ContactFilter.h
//  CrazyBombman
//
//  Created by Yao Melo on 8/1/13.
//
//

#ifndef __CrazyBombman__ContactFilter__
#define __CrazyBombman__ContactFilter__

#include <iostream>
#include "Box2D.h"
namespace Simulation
{
    class ContactFilter : public b2ContactFilter
    {
         virtual bool ShouldCollide(b2Fixture* fixtureA, b2Fixture* fixtureB);
    };
}
#endif /* defined(__CrazyBombman__ContactFilter__) */
