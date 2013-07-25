//
//  Player.cpp
//  CrazyBomber
//
//  Created by Yao Melo on 6/18/13.
//
//

#include "Player.h"
#include "ArtworkLoader.h"
#include "PhysicsUtil.h"
#include "TileUtils.h"

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
        getBody()->SetTransform(b2Vec2(p.x,p.y), 0);
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
    
    void Player::setDirection(Direction var)
    {
        if(_node&&var!= _direction)
        {
            cocos2d::CCAnimation *anim = Utility::ArtworkLoader::walkingAnimation(var);
            if(anim)
            {
                cocos2d::CCRepeatForever* act = cocos2d::CCRepeatForever::create(cocos2d::CCAnimate::create(anim));
                _node->stopAllActions();
                _node->runAction(act);
            }
            else
            {
                _node->stopAllActions();
            }
        }
        _direction = var;
    }
    
    cocos2d::CCPoint Player::getPlayerPosition()
    {
        return this->_node->getPosition();
    }
    
    void Player::createNode()
    {
        cocos2d::CCSprite* sprite = Utility::ArtworkLoader::playerSprite();
        setNode(sprite);
    }
    
    AttachType Player::getAttachType()
    {
        return AttachPlayer;
    }
    
    b2Body* Player::createBody(b2World *_world)
    {
        return  Utility::CreateBodyForRect(_world, Utility::GetBoundingBox(this->getNode()));
    }
    
}