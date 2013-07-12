//
//  Environment.cpp
//  CrazyBomber
//
//  Created by Yao Melo on 6/18/13.
//
//

#include "Environment.h"
#include "Player.h"
#include "TileUtils.h"
#include "Explosion.h"

using namespace cocos2d;

namespace Simulation
{
    void Environment::spawnPlayer()
    {
        Player* player = Player::create();
        player->createNode();
        CCTMXObjectGroup *group = _tileMap->objectGroupNamed(TILE_MAP_OBJ_LAYER);
        CCDictionary *spawn = group->objectNamed(TILE_MAP_SPAWN_OBJ);
        float x = ((CCString*)spawn->objectForKey("x"))->floatValue();
        float y = ((CCString*)spawn->objectForKey("y"))->floatValue();
        //sample 357,800
        CCPoint p = ccp(x,y);
        player->getNode()->setPosition(p);
        _ppDelegate->addNode(player->getNode(),Z_PLAYER);
        _ppDelegate->updatePlayerPostion(p);
        setPlayer(player);
    }
    
    bool Environment::init()
    {
        _bombs = CCArray::create();
        _bombs->retain();
        _explosions = CCArray::create();
        _explosions->retain();
        return true;
    }
    
    void Environment::setTileMap(CCTMXTiledMap *tileMap)
    {
        if(tileMap!=_tileMap)
        {
            CC_SAFE_RETAIN(tileMap);
            CC_SAFE_RELEASE(_tileMap);
            _tileMap = tileMap;
        }
    }
    
    void Environment::update(float dt)
    {
        CCObject::update(dt);
        
        updateBombs(dt);
        updateExplosions(dt);
        CCPoint p = _player->getPlayerPosition();
        _player ->update(dt);
        CCPoint newP = _player->getPlayerPosition();
        if(!p.equals(newP))
        {//collision happen, back to the old position.
            if(checkCollision(newP, p))
            {
                _player->getNode()->setPosition(newP);
            }
            
            if(_ppDelegate)
            {
                _ppDelegate -> updatePlayerPostion(newP);
            }
        }
        
    }
    
    void Environment::updateExplosions(float dt)
    {
        std::vector<int> indecies;
        for (int i = 0;i<_explosions->count();i++)
        {
            Explosion* exp = (Explosion*)_explosions->objectAtIndex(i);
            exp->update(dt);
            if(exp->isFinished())
            {
                indecies.push_back(i);
            }
        }
        for(std::vector<int>::iterator it = indecies.begin();it!=indecies.end();it++)
        {
            _explosions->removeObjectAtIndex(*it);
        }
    }
    
    void Environment::updateBombs(float dt)
    {
        std::vector<int> indecies;
        for (int i = 0;i<_bombs->count();i++) {
            Bomb* bomb = (Bomb*)(_bombs->objectAtIndex(i));

            bomb->update(dt);
            if(bomb->isExplode())
            {
                //FIXME add explosion
                //remove bomb node
                CCNode* bombNode = bomb->getNode();
                bombNode->getParent()->removeChild(bombNode);
                indecies.push_back(i);
                Explosion *exp = Explosion::create();
                exp->createNodesAt(bombNode->getPosition(),_tileMap);
                exp->destroyBlocks(_tileMap);
                _explosions->addObject(exp);
                for(int i =0;i<exp->getNodesCount();i++)
                {
                    _ppDelegate->addNode(exp->getNodeAt(i), Z_EXPLOSION);
                }
            }
        }
        for(std::vector<int>::iterator it = indecies.begin();it!=indecies.end();it++)
        {
            _bombs->removeObjectAtIndex(*it);
        }
    }
    
    bool testTileCollidable(CCTMXTiledMap *tilemap,CCPoint const& mapCoord,CCRect* tileRect)
    {
        CCTMXLayer *blocks = tilemap->layerNamed(TILE_MAP_MATERIAL_LAYER);
        CCSize mapSize = blocks->getLayerSize();
        if(mapCoord.x<0||mapCoord.x>=mapSize.width || mapCoord.y<0 || mapCoord.y>=mapSize.height)
        {
            if(tileRect)
            {
                *tileRect = CCRectZero;
            }
            //collide with map border.
            return true;
        }
        int gid = blocks->tileGIDAt(mapCoord);
        

        if(gid)
        {
            CCDictionary *dictionary = tilemap->propertiesForGID(gid);
            CCString* mat = (CCString*)dictionary->objectForKey(TILE_MAP_MATERIAL_KEY);
            if(mat)
            {
                Material material = static_cast<Material>(mat->intValue());
                if(material == eDestroyable || material == eSolid)
                {
                    if(tileRect)
                    {
                        *tileRect = Utility::GetBoundingBox(blocks->tileAt(mapCoord));
                    }
                    return true;
                }
            }
        }
        return false;
    }

    bool Environment::checkCollision(CCPoint& p, CCPoint const& prevP)
    {
//        CCTMXLayer *blocks = _tileMap->layerNamed(TILE_MAP_MATERIAL_LAYER);
//
//        //calculate heading tile
//        CCPoint mapCoord = Utility::GetMapCoords(_tileMap, p);
//        CCSize mapSize = blocks->getLayerSize();
//        if(mapCoord.x<0||mapCoord.x>=mapSize.width || mapCoord.y<0 || mapCoord.y>=mapSize.height)
//        {
//            //collide with map border.
//            return true;
//        }
//        int gid = blocks->tileGIDAt(mapCoord);
//    
//        CCLOGINFO("tileGid %d",gid);
//        if(gid)
//        {
//            CCDictionary *dictionary = _tileMap->propertiesForGID(gid);
//            CCString* mat = (CCString*)dictionary->objectForKey(TILE_MAP_MATERIAL_KEY);
//            if(mat)
//            {
//                Material material = static_cast<Material>(mat->intValue());
//                if(material == eDestroyable || material == eSolid)
//                {
//                    return true;
//                }
//            }
//        }
//        return false;
        CCPoint dir = p- prevP;
        CCSize playerSize = _player->getNode()->getContentSize();
        CCPoint playerVec = ccp(playerSize.width/2,playerSize.height/2);
        float dot = dir.dot(playerVec);
        dir = dir * (fabs(dot)/dir.getLengthSq());
        CCPoint contactVec;
        bool collide = Utility::TestSegCollision(_tileMap, p, p+dir, testTileCollidable,&contactVec);
        p = p+contactVec;
        return collide;
    }
    
    
    void Environment::addBomb(Simulation::Bomb *bomb)
    {
        CCObject *b;
        CCARRAY_FOREACH(_bombs, b)
        {
            if(((Bomb*)b)->getNode()->getPosition().equals(bomb->getNode()->getPosition()))
            {
                return;
            }
        }
        _bombs->addObject(bomb);
        _ppDelegate->addNode(bomb->getNode(), Z_BOMB);
    }
    
    Environment::~Environment()
    {
        CC_SAFE_RELEASE(_player);
        CC_SAFE_RELEASE(_bombs);
        CC_SAFE_RELEASE(_explosions);
    }
    
}