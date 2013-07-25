//
//  Player.h
//  CrazyBomber
//
//  Created by Yao Melo on 6/18/13.
//
//

#ifndef __CrazyBomber__Player__
#define __CrazyBomber__Player__

#include <iostream>
#include "cocos2d.h"
#include "Simulation.h"
#include "PhysicsObject.h"

namespace Simulation{
    class Player : public PhysicsObject
    {
//    private:
//        Direction _direction;
//        cocos2d::CCNode *_playerNode;
    CC_PROPERTY(cocos2d::CCNode*, _node, Node);
        
    public:
        
        bool init();

        Player();
        
        virtual ~Player();
        
//        void setPlayerNode(cocos2d::CCNode *playerNode);
        
        cocos2d::CCPoint getPlayerPosition();
        
        virtual void update(float dt);
        
        CC_SYNTHESIZE_READONLY(Direction, _direction, Direction);
        
        void setDirection(Direction var);
        
        void createNode();
        
        virtual AttachType getAttachType();
        
        virtual b2Body* createBody(b2World *_world);
        
        CREATE_FUNC(Player);
    };
}

#endif /* defined(__CrazyBomber__Player__) */
