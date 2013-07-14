//
//  MobPrototype.h
//  CrazyBombman
//
//  Created by Yao Melo on 7/14/13.
//
//

#ifndef __CrazyBombman__MobPrototype__
#define __CrazyBombman__MobPrototype__

#include <iostream>

namespace Simulation
{
    typedef unsigned int Level;
    
    class MobPrototype
    {
    private:
        Level _lvl;
        
    public:
        MobPrototype(Level lvl):_lvl(lvl){};
        
        ~MobPrototype(){};
        
        Level getLevel(){return _lvl;};
        
        unsigned int mobIdRange();
        
        unsigned int minMobId();
        
        unsigned int randomMobId();
        
        float hitpoint();
    };
}
#endif /* defined(__CrazyBombman__MobPrototype__) */
