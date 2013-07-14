//
//  MobPrototype.cpp
//  CrazyBombman
//
//  Created by Yao Melo on 7/14/13.
//
//

#include "MobPrototype.h"

namespace Simulation {
    unsigned int MobPrototype::randomMobId()
    {
        return (rand() / (RAND_MAX+1.0) * mobIdRange()) + minMobId();
    }
    
    float MobPrototype::hitpoint()
    {
        return 1.0;
    }
    
    unsigned int MobPrototype::mobIdRange()
    {
        return 9;
    }
    
    unsigned int MobPrototype::minMobId()
    {
        return 0;
    }
}