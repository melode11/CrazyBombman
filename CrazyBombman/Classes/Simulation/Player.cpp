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
    bool Player::init()
    {
        
            this->_playerNode = NULL;
            this->_direction = eNone;
            return true;
    }
    
    void Player::update(float time_inteval)
    {
        if(!_playerNode)
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
        cocos2d::CCPoint p = _playerNode -> getPosition();
        p.x += dx;
        p.y += dy;
        _playerNode->setPosition(p);
        
    }
    
    cocos2d::CCNode* Player::getPlayerNode()
    {
        return _playerNode;
    }
    
    void Player::setPlayerNode(cocos2d::CCNode *playerNode)
    {
        
        if(_playerNode!=playerNode)
        {
            CC_SAFE_RELEASE(_playerNode);
            CC_SAFE_RETAIN(playerNode);
            _playerNode = playerNode;
        }
    }
    
    cocos2d::CCPoint Player::getPlayerPosition()
    {
        return this->_playerNode->getPosition();
    }
}