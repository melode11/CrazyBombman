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
#include "Environment.h"

namespace Simulation
{
    Player::Player():_node(0),_direction(eNone),_lastPoint()
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
        cocos2d::CCPoint p = _node -> getPosition();
        _lastPoint = p;
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
    
    PhysicalType Player::getPhysicalType()
    {
        return PhysPlayer;
    }
    
    b2Body* Player::createBody(b2World *_world)
    {
        return  Utility::CreateBodyFilled(_world, Utility::GetBoundingBox(this->getNode()),b2_dynamicBody);
    }
    
    void Player::collideWith(Simulation::PhysicsObject *other)
    {
        if(_node)
        {   
            if(other->getPhysicalType() == PhysTile)
            {
                TileInfo* ti = static_cast<TileInfo*>(other);
                if(ti->material == eSolid || ti->material == eDestroyable)
                {
                    _node->setPosition(_lastPoint);
                }
            }
        }
    }
    
}