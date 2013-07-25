//
//  ContactListener.cpp
//  CrazyBombman
//
//  Created by Yao Melo on 7/24/13.
//
//

#include "ContactListener.h"
namespace Simulation
{
    void ContactLisenter::BeginContact(b2Contact *contact)
    {
//        contact->get
                printf("begin contact" );
    }
    
    void ContactLisenter::EndContact(b2Contact *contact)
    {
        printf("end contact" );
    }
}