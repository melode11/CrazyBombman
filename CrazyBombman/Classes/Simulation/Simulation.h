//
//  Simulation.h
//  CrazyBomber
//
//  Created by Yao Melo on 6/18/13.
//
//

#ifndef CrazyBomber_Simulation_h
#define CrazyBomber_Simulation_h

#define PLAYER_VELOCITY 80.0

#define BOMB_DURATION 3.0

#define EXPLOSION_RANGE 64.0

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
