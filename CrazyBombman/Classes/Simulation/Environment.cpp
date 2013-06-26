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
        if(checkCollision(newP))
        {//collision happen, back to the old position.
            _player->getNode()->setPosition(p);
        }
        else if(_ppDelegate)
        {
            _ppDelegate -> updatePlayerPostion(newP);
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
                exp->createNodesAt(bombNode->getPosition());
                _explosions->addObject(exp);
                for(int i =0;i<exp->getNodesCount();i++)
                {
                    _ppDelegate->addNode(exp->getNodeAt(i), 1);
                }
            }
        }
        for(std::vector<int>::iterator it = indecies.begin();it!=indecies.end();it++)
        {
            _bombs->removeObjectAtIndex(*it);
        }
    }

    bool Environment::checkCollision(CCPoint& p)
    {
        CCTMXLayer *blocks = _tileMap->layerNamed("Blocks");

        //calculate heading tile
        CCPoint mapCoord = Utility::GetMapCoords(_tileMap, p);
        CCSize mapSize = blocks->getLayerSize();
        if(mapCoord.x<0||mapCoord.x>=mapSize.width || mapCoord.y<0 || mapCoord.y>=mapSize.height)
        {
            //collide with map border.
            return true;
        }
        int gid = blocks->tileGIDAt(mapCoord);
    
        CCLOGINFO("tileGid %d",gid);
        if(gid)
        {
            CCDictionary *dictionary = _tileMap->propertiesForGID(gid);
            CCString* mat = (CCString*)dictionary->objectForKey("material");
            Material material = ePlain;
            switch(mat->intValue())
            {
                case 2:
                    material = eDestroyable;
                    break;
                case 3:
                    material = eSolid;
                    break;
                default:
                    ;
            }
            if(material == eDestroyable || material == eSolid)
            {
                return true;
            }
        }
        return false;
    }
    
    
    void Environment::addBomb(Simulation::Bomb *bomb)
    {
        _bombs->addObject(bomb);
    }
    
    Environment::~Environment()
    {
        CC_SAFE_RELEASE(_player);
        CC_SAFE_RELEASE(_bombs);
        CC_SAFE_RELEASE(_explosions);
    }
    
}