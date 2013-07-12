//
//  TileUtils.cpp
//  CrazyBombman
//
//  Created by Yao Melo on 6/28/13.
//
//

#include "TileUtils.h"
#include "Box2D.h"

namespace Utility {
    
    using namespace cocos2d;
    
    
    static inline bool TestRect2Rect(CCRect const& rect1,CCRect const& rect2,CCPoint const& intrudePoint, CCPoint const& dirVec, CCPoint* outputVec)
    {
        b2Manifold man;
        b2PolygonShape poly1,poly2;
        poly1.SetAsBox(rect1.size.width/2, rect1.size.height/2);
        poly2.SetAsBox(rect2.size.width/2, rect2.size.height/2);
        b2Transform tf1,tf2;
        tf1.Set(b2Vec2(rect1.origin.x + rect1.size.width/2, rect1.origin.y + rect1.size.height/2), 0);
        tf2.Set(b2Vec2(rect2.origin.x + rect2.size.width/2, rect2.origin.y + rect2.size.height/2), 0);
        b2CollidePolygons(&man, &poly1, tf1, &poly2, tf2);
        if(man.pointCount < 1)
        {
            return false;
        }
        else if(man.pointCount == 1)
        {
            if(outputVec)
            {
                outputVec->x = 0;
                outputVec->y = 0;
            }
            return true;
        }
        else
        {
            if(outputVec)
            {
                b2WorldManifold worldMan;
                worldMan.Initialize(&man, tf1, 0, tf2, 0);
                b2Vec2 intrudeV(intrudePoint.x, intrudePoint.y);
                b2Vec2 dir(dirVec.x,dirVec.y);
                float32 dot = b2Dot(intrudeV - worldMan.points[0], dir);
                if(dot == 0)
                {
                    dot = b2Dot(intrudeV - worldMan.points[1], dir);
                }
                
                dir*=(dot/dir.LengthSquared());
                outputVec->x = -dir.x;
                outputVec->y = -dir.y;
            }
            return true;
        }
    }
    
    bool TestRectCollision(CCTMXTiledMap *tileMap, CCPoint const& dirVec,CCRect const& subjectRect,FP_COLLIDABLE_TESTER colTester,CCPoint* contactVec)
    {
        bool isCollide = false;
        CCPoint corner,center;
        center.setPoint(subjectRect.origin.x+subjectRect.size.width/2,subjectRect.origin.y+subjectRect.size.height/2);
        float x = subjectRect.origin.x,y=subjectRect.origin.y,w = subjectRect.size.width,h=subjectRect.size.height;
        CCRect collideRect;
        float maxLen = 0;
        CCPoint maxContact;
        for (int i = 0; i<4; ++i) {
            corner.setPoint((i/2 == 0)?x:x+w, (i%2 == 0)?y:y+h);
            if(dirVec.dot(corner-center) > 0)
            {
                CCPoint mapCoord = GetMapCoords(tileMap, corner);
                if(colTester(tileMap,mapCoord,&collideRect))
                {
                    if(collideRect.equals(CCRectZero))
                    {
                        if(contactVec)
                        {
                            *contactVec = CCPointZero;
                        }
                        return true;
                    }
                    CCPoint contact;
                    if(TestRect2Rect(collideRect, subjectRect,corner, dirVec, &contact))
                    {
                        float len = contact.getDistanceSq(CCPointZero);
                        if(maxLen < len)
                        {
                            maxContact = contact;
                            maxLen = len;
                            isCollide = true;
                        }
                    }

                }
            }
        }
        if(contactVec)
        {
            *contactVec = maxContact;
        }
        return isCollide;
    }
    
    
    bool TestSegCollision(CCTMXTiledMap *tileMap,CCPoint const& start, CCPoint const& dest,FP_COLLIDABLE_TESTER colTester, CCPoint* contactVec)
    {
        CCRect tileRect;
        bool isCollidable = colTester(tileMap,GetMapCoords(tileMap, dest),&tileRect);
        if(isCollidable)
        {
            b2Vec2 vecStart(start.x,start.y),vecDest(dest.x,dest.y);
            b2Vec2 edgeCenter = (vecStart + vecDest);
            edgeCenter *= 0.5;
            b2EdgeShape shape;
            shape.Set(vecStart - edgeCenter, vecDest- edgeCenter);
            b2Transform trans1,trans2;
            trans1.Set(edgeCenter, 0);
            trans2.Set(b2Vec2(tileRect.origin.x+tileRect.size.width/2 , tileRect.origin.y + tileRect.size.height/2), 0);
            
            b2Manifold man;
            b2PolygonShape poly;
            poly.SetAsBox(tileRect.size.width/2, tileRect.size.height/2);
            b2CollideEdgeAndPolygon(&man,&shape , trans1, &poly, trans2);
            if(man.pointCount <= 0)
            {
                return false;
            }
            else
            {
                if(contactVec)
                {
                    float maxLengthSq = 0;
                    b2Vec2 maxVec;
                    b2WorldManifold wman;
                    wman.Initialize(&man, trans1, shape.m_radius, trans2, poly.m_radius);
                    for (int i = 0; i<man.pointCount; ++i) {
                        b2Vec2 vec =  wman.points[i] - vecDest;
                        float lenSq = vec.LengthSquared();
                        if(maxLengthSq<lenSq)
                        {
                            maxLengthSq = lenSq;
                            maxVec = vec;
                        }
                    }
                    contactVec->x = maxVec.x;
                    contactVec->y = maxVec.y;
                }
                return true;
            }
        }
        return false;
    }
    
}
