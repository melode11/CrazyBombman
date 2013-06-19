//
//  Simulation.h
//  CrazyBomber
//
//  Created by Yao Melo on 6/18/13.
//
//

#ifndef CrazyBomber_Simulation_h
#define CrazyBomber_Simulation_h

namespace Simulation
{
    typedef enum _Direction
    {
        eNone = 0,
        eLeft = 1,
        eUp = 2,
        eRight=3,
        eDown = 4
    } Direction;
    
    typedef enum _Material
    {
        ePlain = 0,
        eDestroyable = 2,
        eSolid = 3
    } Material;
}

#endif
