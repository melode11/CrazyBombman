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
    
    static inline cocos2d::CCRect GetBoundingBox(cocos2d::CCNode* node)
    {
        if(node)
        {
            cocos2d::CCSize size = node->getContentSize();
            cocos2d::CCPoint p = node->getPosition();
            cocos2d::CCPoint anchor = node->getAnchorPoint();;
            using namespace cocos2d;
            return CCRectMake(p.x - anchor.x*size.width, p.y - anchor.y*size.height, size.width, size.height);
        }
        return cocos2d::CCRectZero;
    }
    
    static inline CCPoint GetGLPosition(const CCTMXTiledMap *tileMap,const CCPoint& point)
    {
        CCSize tileSize = tileMap->getTileSize();
        float y = (tileMap->getMapSize().height * tileSize.height) - point.y;
        float x = point.x;
        return ccp(x,y);
    }
    
    static inline CCPoint GetMapPosition(const CCTMXTiledMap *tileMap,const CCPoint& point)
    {
        CCSize tileSize = tileMap->getTileSize();
        float y = (tileMap->getMapSize().height * tileSize.height) - point.y;
        float x = point.x;
        return ccp(x,y);
    }
    
    static inline CCPoint GetMapCoords(const CCTMXTiledMap *tileMap,const CCPoint& point)
    {
        CCSize tileSize = tileMap->getTileSize();
        float y = ((tileMap->getMapSize().height * tileSize.height) - point.y) / tileSize.height;
        float x = point.x/tileSize.width;
        return ccp(x<0?((int)x)-1:(int)x,y<0?((int)y)-1:(int)y);
    }
    
    //output coords need to multiply tilesize to get the intersection point.
    //also they can be used for map coordinates when truncate the float part.
//    void GetMapCoordsOnPath(const CCTMXTiledMap *tileMap,const CCPoint& startPoint,const CCPoint& endPoint,std::vector<CCPoint>& outputCoords);
    
    typedef bool (*FP_COLLIDABLE_TESTER)(CCTMXTiledMap *tilemap,CCPoint const& mapCoord,CCRect* collideRect);
    
    bool TestRectCollision(CCTMXTiledMap *tileMap, CCPoint const& dirVec,CCRect const& subjectRect,FP_COLLIDABLE_TESTER colTester, CCPoint* contactVec);
    
    
    bool TestSegCollision(CCTMXTiledMap *tileMap,CCPoint const& start, CCPoint const& dest,FP_COLLIDABLE_TESTER colTester, CCPoint* contactPoint);
}

#endif
