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
#include <vector>

namespace Utility{
    using namespace cocos2d;
    
    //axis-align bounding box intersection.
    static inline bool AABBContains(CCRect const& rectA,CCRect const& rectB)
    {

    }
    
    static inline CCPoint GetGLPosition(const CCTMXTiledMap *tileMap,const CCPoint& point)
    {
        CCSize tileSize = tileMap->getTileSize();
        int y = (tileMap->getMapSize().height * tileSize.height) - point.y;
        int x = point.x;
        return ccp(x,y);
    }
   
    static inline CCPoint GetMapPosition(const CCTMXTiledMap *tileMap,const CCPoint& point)
    {
        CCSize tileSize = tileMap->getTileSize();
        int y = (tileMap->getMapSize().height * tileSize.height) - point.y;
        int x = point.x;
        return ccp(x,y);
    }
    
    static inline CCPoint GetMapCoords(const CCTMXTiledMap *tileMap,const CCPoint& point)
    {
        CCSize tileSize = tileMap->getTileSize();
        int y = ((tileMap->getMapSize().height * tileSize.height) - point.y) / tileSize.height;
        int x = point.x/tileSize.width;
        return ccp(x,y);
    }
    
    //output coords need to multiply tilesize to get the intersection point.
    //also they can be used for map coordinates when truncate the float part.
    void GetMapCoordsOnPath(const CCTMXTiledMap *tileMap,const CCPoint& startPoint,const CCPoint& endPoint,std::vector<CCPoint>& outputCoords);
}

#endif
