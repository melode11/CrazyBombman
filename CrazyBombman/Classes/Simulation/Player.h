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


namespace Simulation{
    class Player : public cocos2d::CCObject
    {
//    private:
//        Direction _direction;
//        cocos2d::CCNode *_playerNode;
    CC_PROPERTY(cocos2d::CCNode*, _playerNode, PlayerNode);
        
    public:
        
        bool init();

        Player(){};
        
        ~Player()
        {
            CC_SAFE_RELEASE(this->_playerNode);
        };
        
//        void setPlayerNode(cocos2d::CCNode *playerNode);
        
        cocos2d::CCPoint getPlayerPosition();
        
        virtual void update(float dt);
        

        
        CC_SYNTHESIZE(Direction, _direction, Direction);
        
        CREATE_FUNC(Player);
    };
}

#endif /* defined(__CrazyBomber__Player__) */
