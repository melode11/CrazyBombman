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

#define MOB_KEEP_DIR_INTERVAL 5.0

#define MOB_VELOCITY 50.0

//initial SLPs
#define INITIAL_EXPLOSION_RANGE 128.0

#define INITIAL_BOMB_AMOUNT 20

#define INITIAL_HITPOINT 1

#define INITIAL_TIMELIMIT 120.0

#define INITIAL_MOB_SPAWN_INTERVAL 3.0

#define INITIAL_MAX_MOB_COUNT 10
//z_order
#define Z_EXPLOSION 3
#define Z_PLAYER 2
#define Z_MOBS 2
#define Z_BOMB 1

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
        eNonBlock = 1,
        eDestroyable = 2,
        eSolid = 3
    } Material;
}

#endif
