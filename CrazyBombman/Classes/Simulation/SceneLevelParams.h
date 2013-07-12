//
//  SceneLevelParams.h
//  CrazyBombman
//
//  Created by Yao Melo on 7/12/13.
//
//

#ifndef __CrazyBombman__SceneLevelParams__
#define __CrazyBombman__SceneLevelParams__

#include <iostream>
#include "Simulation.h"

namespace Simulation
{
    struct SceneLevelParams
    {
        double timelimit;
        float bombRange;
        float bombAmount;
        unsigned int hitPoints;
        
        SceneLevelParams():timelimit(INITIAL_TIMELIMIT),bombRange(INITIAL_EXPLOSION_RANGE),bombAmount(INITIAL_BOMB_AMOUNT),hitPoints(INITIAL_HITPOINT)
        {
            
        }
        
        static SceneLevelParams* globalSceneLevelParams();
    private:
        
        static SceneLevelParams* globalSLP;
    };
}

#endif /* defined(__CrazyBombman__SceneLevelParams__) */
