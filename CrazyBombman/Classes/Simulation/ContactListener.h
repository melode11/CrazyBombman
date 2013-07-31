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
    class ContactLisenter:public b2ContactListener
    {
        virtual void BeginContact(b2Contact* contact);
        
        virtual void EndContact(b2Contact* contact);
 
    };
}

#endif /* defined(__CrazyBombman__ContactListener__) */
