//
//  Bomb.h
//  CrazyBombman
//
//  Created by Yao Melo on 6/23/13.
//
//

#ifndef __CrazyBombman__Bomb__
#define __CrazyBombman__Bomb__

#include <iostream>
#include "cocos2d.h"
#include "Simulation.h"

namespace Simulation
{
    class Bomb : public cocos2d::CCObject
    {
    private:
        float _lifetime;
        bool _isExplode;
        
    public:
        CC_SYNTHESIZE_RETAIN(cocos2d::CCNode*, _node, Node);
        
        bool isExplode();
        
        Bomb():_node(0),_lifetime(0),_isExplode(false)
        {}
        
        ~Bomb()
        {
            CC_SAFE_RELEASE(_node);
        }
        
        virtual bool init();
        
        virtual void update(float dt);
        
        CREATE_FUNC(Bomb);
    };
}
#endif /* defined(__CrazyBombman__Bomb__) */
