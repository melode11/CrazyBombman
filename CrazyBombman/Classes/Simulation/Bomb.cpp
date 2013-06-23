//
//  Bomb.cpp
//  CrazyBombman
//
//  Created by Yao Melo on 6/23/13.
//
//

#include "Bomb.h"

namespace Simulation {
    bool Bomb::init()
    {
        return true;
    }
    
    void Bomb::update(float dt)
    {
        _lifetime+=dt;
        if(_lifetime>BOMB_DURATION)
        {
            _isExplode = true;
        }
    }
    
    bool Bomb::isExplode()
    {
        return _isExplode;
    }
}