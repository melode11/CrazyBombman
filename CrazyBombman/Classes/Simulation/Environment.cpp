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

using namespace cocos2d;

namespace Simulation
{
    bool Environment::init()
    {
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
        
        CCPoint p = _player->getPlayerPosition();
        _player ->update(dt);
        CCPoint newP = _player->getPlayerPosition();
        if(checkCollision(newP))
        {//collision happen, back to the old position.
            _player->getPlayerNode()->setPosition(p);
        }
        else if(_ppDelegate)
        {
            _ppDelegate -> updatePlayerPostion(newP);
        }
        
    }
    

    bool Environment::checkCollision(CCPoint& p)
    {

        CCTMXLayer *blocks = _tileMap->layerNamed("Blocks");
        //calculate heading tile
        CCPoint mapCoord = Utility::GetMapCoords(_tileMap, p);
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
                CCSprite *tile = blocks -> tileAt(mapCoord);
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