//
//  AttachInfo.h
//  CrazyBombman
//
//  Created by Yao Melo on 7/18/13.
//
//

#ifndef __CrazyBombman__AttachInfo__
#define __CrazyBombman__AttachInfo__

#include <iostream>
#include "cocos2d.h"
#include "PhysicsObject.h"

namespace Simulation
{
 
    enum AttachType
    {
        AttachNone,
        AttachPlayer,
        AttachMob,
        AttachTile,
        AttachBomb,
        AttachExplosion,
    };
    
    struct AttachInfo
    {
        AttachType type;
        cocos2d::CCObject *userObj;
        
        AttachInfo(AttachType type,cocos2d::CCObject* obj):type(type),userObj(obj)
        {
            CC_SAFE_RETAIN(userObj);
        }
        
        ~AttachInfo()
        {
            CC_SAFE_RELEASE(userObj);
        }
        
        AttachInfo(AttachInfo const& ai):type(ai.type),userObj(ai.userObj)
        {
            CC_SAFE_RETAIN(userObj);
        }
    private:
        void operator= (AttachInfo const& ai);
        
    };
    
}
#endif /* defined(__CrazyBombman__AttachInfo__) */
