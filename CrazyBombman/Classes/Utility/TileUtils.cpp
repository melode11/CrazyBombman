//
//  TileUtils.cpp
//  CrazyBombman
//
//  Created by Yao Melo on 6/28/13.
//
//

#include "TileUtils.h"

namespace Utility {
    
    using namespace cocos2d;
    
    typedef float (*FP_ACCESSOR)(CCPoint const& p);
    
    typedef void (*FP_INTERSECTION_HANDLER)(float variable, float co_variable, void* userObj);
    
    
    static inline void push_back(std::vector<CCPoint>& v, CCPoint const& p)
    {
        v.push_back(p);
    }
    
    float getX(CCPoint const& p)
    {
        return p.x;
    }
    
    float getY(CCPoint const& p)
    {
        return p.y;
    }
    
    void intersectsByX(float v,float cv, void* intersects)
    {
        std::vector<CCPoint> *inters = (std::vector<CCPoint>*) intersects;
        push_back(*inters, ccp(v,cv));

    }
    
    void intersectsByY(float v,float cv, void* intersects)
    {
        std::vector<CCPoint> *inters = (std::vector<CCPoint>*) intersects;
        push_back(*inters, ccp(cv,v));
    }
   
    void CheckIntersection(float s,float e, float k, float c, FP_INTERSECTION_HANDLER handler, void* userObj)
    {
        int start, end, step;
        if(s < e)
        {
            start =((int)s) + 1;
            end = ceil(e);
            step = 1;
        }
        else
        {
            start = ceil(s);
            end = ((int)e) + 1;
            step = -1;
        }
        if(start >= end)
        {
            return;
        }
        for(int  i = start; i!=end; i+=step)
        {
            handler(i, k*i+c,userObj);
        }
        
    }
    
    void GetMapCoordsOnPath(const CCTMXTiledMap *tileMap,const CCPoint& startPoint,const CCPoint& endPoint,std::vector<CCPoint>& outputCoords)
    {
        CCSize tileSize = tileMap->getTileSize();
        float sy = ((tileMap->getMapSize().height * tileSize.height) - startPoint.y)/tileSize.height ;
        float sx = startPoint.x/tileSize.width;
        float ey = ((tileMap->getMapSize().height * tileSize.height) - endPoint.y)/tileSize.height ;
        float ex = endPoint.x/tileSize.width;
        
        FP_ACCESSOR getVar;
        FP_INTERSECTION_HANDLER intersector;
        std::vector<CCPoint> xIntersections;
        float k,c;
        if((ex - sx) == 0)
        {
            CCPoint p;
            p.x = sx;
            p.y = sy;
            push_back(xIntersections, p);
            p.x = ex;
            p.y = ey;
            push_back(xIntersections, p);
            k = 0;
            c = sx;
            getVar = getY;
            intersector = intersectsByY;
        }
        else if((ey - sy) == 0)
        {
            CCPoint p;
            p.x = sx;
            p.y = sy;
            push_back(xIntersections, p);
            p.x = ex;
            p.y = ey;
            push_back(xIntersections, p);
            k = 0;
            c = sy;
            intersector = intersectsByX;
            getVar = getX;
        }
        else
        {
            float kx = (ey - sy) / (ex - sx);
            float cx = sy - (kx * sx); //keep in mind y = kx + c
            
            CCPoint p = ccp(sx,sy);
            push_back(xIntersections, p);
            
            CheckIntersection(sx, ex, kx, cx, intersectsByX, &xIntersections);
            
            p.x = ex;
            p.y = ey;
            push_back(xIntersections, p);
            k = 1.0/kx;
            c = sx - k*sy;
            intersector = intersectsByY;
            getVar = getY;
        }
        

        CCPoint lastPoint,p;
        
        for (std::vector<CCPoint>::iterator it = xIntersections.begin(); it!=xIntersections.end(); it++) {
            if(it == xIntersections.begin())
            {
                lastPoint = *it;
                continue;
            }
            p = *it;
            CheckIntersection(getVar(lastPoint), getVar(p), k, c, intersector, &outputCoords);
            lastPoint = p;
            if(it != xIntersections.end() - 1)
            {
                push_back(outputCoords, p);
            }
        }

    }
}
