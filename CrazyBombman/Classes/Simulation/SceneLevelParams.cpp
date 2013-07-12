//
//  SceneLevelParams.cpp
//  CrazyBombman
//
//  Created by Yao Melo on 7/12/13.
//
//

#include "SceneLevelParams.h"
namespace Simulation
{
    SceneLevelParams* SceneLevelParams::globalSLP = NULL;
    
    SceneLevelParams* SceneLevelParams::globalSceneLevelParams()
    {
        if(globalSLP == NULL)
        {
            globalSLP = new SceneLevelParams();
        }
        return globalSLP;
    }
}