//
//  Environment.cpp
//  CrazyBomber
//
//  Created by Yao Melo on 6/18/13.
//
//

#include "Environment.h"
#include "Player.h"

using namespace cocos2d;

namespace Simulation
{
    bool Environment::init()
    {
        _player = Player::create();
        _player -> retain();
        _tileMap = NULL;
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
        
    }
    
//    Player* Environment::getPlayer()
//    {
//        return _player;
//    }
    
    bool Environment::checkCollision()
    {
        Direction dir = _player->getDirection();
        int y = 0,x = 0;
        switch (dir) {
            case eUp:
                y = -1;
                break;
            case eDown:
                y = 1;
                break;
            case eLeft:
                x = -1;
            case eRight:
                x = 1;
            default:
                return false;
        }

        CCPoint p = _player->getPlayerPosition();
        CCSize tileSize = _tileMap->getTileSize();
        CCTMXLayer *blocks = _tileMap->layerNamed("Blocks");
        y += ((_tileMap->getMapSize().height * tileSize.height) - p.y) / tileSize.height;
        x += p.x/tileSize.width;
        //calculate heading tile
       
        int gid = blocks->tileGIDAt(ccp(x, y));
    
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
                CCSprite *tile = blocks -> tileAt(ccp(x,y));
                CCRect tileRect = getCCRect(tile);
                CCRect playerRect = getCCRect(_player->getPlayerNode());
                if(tileRect.intersectsRect(playerRect))
                {
                    return true;
                }
            }
        }
        return false;
    }
    
    
}