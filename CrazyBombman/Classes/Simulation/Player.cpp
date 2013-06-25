//
//  Player.cpp
//  CrazyBomber
//
//  Created by Yao Melo on 6/18/13.
//
//

#include "Player.h"
namespace Simulation
{
    Player::Player():_node(0),_direction(eNone)
    {
        
    }
    
    Player::~Player()
    {
        CC_SAFE_RELEASE(this->_node);
    }
    
    bool Player::init()
    {
        return true;
    }
    
    void Player::update(float time_inteval)
    {
        if(!_node)
            return;
        double dx = 0,dy = 0;
        switch (_direction) {
            case eLeft:
                dx = - (time_inteval* PLAYER_VELOCITY);
                break;
            case eUp:
                dy = (time_inteval* PLAYER_VELOCITY);
                break;
            case eRight:
                dx = (time_inteval* PLAYER_VELOCITY);
                break;
            case eDown:
                dy = - (time_inteval* PLAYER_VELOCITY);
                break;

            default:
                break;
        }
        cocos2d::CCPoint p = _node -> getPosition();
        p.x += dx;
        p.y += dy;
        _node->setPosition(p);
        
    }
    
    cocos2d::CCNode* Player::getNode()
    {
        return _node;
    }
    
    void Player::setNode(cocos2d::CCNode *playerNode)
    {
        
        if(_node!=playerNode)
        {
            CC_SAFE_RELEASE(_node);
            CC_SAFE_RETAIN(playerNode);
            _node = playerNode;
        }
    }
    
    cocos2d::CCPoint Player::getPlayerPosition()
    {
        return this->_node->getPosition();
    }
}