//
//  TileUtils.h
//  CrazyBombman
//
//  Created by Yao Melo on 6/21/13.
//
//

#ifndef CrazyBombman_TileUtils_h
#define CrazyBombman_TileUtils_h

#include "cocos2d.h"
namespace Utility{
    using namespace cocos2d;
    static inline CCPoint GetMapCoords(CCTMXTiledMap *tileMap,CCPoint& point)
    {
        CCSize tileSize = tileMap->getTileSize();
        int y = ((tileMap->getMapSize().height * tileSize.height) - point.y) / tileSize.height;
        int x = point.x/tileSize.width;
        return ccp(x,y);
    }
    
}

#endif
