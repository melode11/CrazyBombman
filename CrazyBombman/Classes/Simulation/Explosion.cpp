//
//  Explosion.cpp
//  CrazyBombman
//
//  Created by Yao Melo on 6/23/13.
//
//

#include "Explosion.h"
#include "Simulation.h"
#include "TileUtils.h"
#include "AnimationLoader.h"

namespace Simulation
{
    Explosion::Explosion():_animateNodes(),_range(EXPLOSION_RANGE),_isFinished(false),_destroyMapcoords()
    {
        
    }
    
    Explosion::~Explosion()
    {

    }
    
    void Explosion::update(float dt)
    {
        bool isFinished = true;
        for (std::vector<AnimatedNode>::iterator it=_animateNodes.begin(); it!=_animateNodes.end();) {
            cocos2d::CCNode* node =  it->getNode();
            cocos2d::CCAction *anim = it->getAction();
            if(!it->isAnimated && anim && node)
            {
                node->setVisible(true);
                node->runAction(anim);
                it->isAnimated = true;
                isFinished = false;
            }
            else if(anim && anim->isDone())
            {
                node->getParent()->removeChild(node);
                it = _animateNodes.erase(it);
                continue;
            }
            else
            {
                isFinished = false;
            }
            it++;
        }
        _isFinished = isFinished;
        
    }
    
    bool Explosion::init()
    {
        return true;
    }
    
    float testExplosionRange(cocos2d::CCPoint const& origin, cocos2d::CCPoint const& dest,float maxRange, cocos2d::CCTMXTiledMap *tileMap, std::vector<int>& destroyGIDs)
    {
        std::vector<cocos2d::CCPoint> intersectCoords;
        Utility::GetMapCoordsOnPath(tileMap, origin, dest, intersectCoords);
        cocos2d::CCSize tilesize = tileMap->getTileSize();
        float range = maxRange;
        
        cocos2d::CCPoint mapp;
        cocos2d::CCTMXLayer *blockLayer = tileMap->layerNamed("Blocks");
        for(std::vector<cocos2d::CCPoint>::iterator it = intersectCoords.begin();it!= intersectCoords.end();++it)
        {
            do {
                mapp.x = (int)it->x;
                mapp.y = (int)it->y;
                int gid = blockLayer->tileGIDAt(mapp);
                cocos2d::CCDictionary* properties = tileMap->propertiesForGID(gid);
                CC_BREAK_IF(properties == NULL);
                cocos2d::CCObject *val = properties->objectForKey("material");
                CC_BREAK_IF(val == NULL);
                int material = static_cast<cocos2d::CCString*>(val) ->intValue();
                if(material == eSolid)
                {
                    range = origin.getDistance(Utility::GetGLPosition(tileMap, ccp(it->x*tilesize.width,it->y*tilesize.height)));
                    return range;
                }
                else if(material == eDestroyable)
                {
                    destroyGIDs.push_back(gid);
                }
            } while (0);
        }
        return range;
    }
    
    
    Material getTileMaterial(cocos2d::CCTMXTiledMap *tileMap,cocos2d::CCTMXLayer *layer, cocos2d::CCPoint const& p, cocos2d::CCPoint& outputMapCoord)
    {
        cocos2d::CCSize layerSize = layer->getLayerSize();
       
        outputMapCoord = Utility::GetMapCoords(tileMap, p);
        if(outputMapCoord.x<0 || outputMapCoord.y < 0 || outputMapCoord.x>= layerSize.width || outputMapCoord.y >=layerSize.height)
        {
            return eSolid;
        }
        int gid = layer->tileGIDAt(outputMapCoord);
        cocos2d::CCDictionary* properties = tileMap->propertiesForGID(gid);
        if(properties)
        {
            cocos2d::CCObject *val = properties->objectForKey("material");
            if(val)
            {
                int material = static_cast<cocos2d::CCString*>(val) ->intValue();
                return static_cast<Material>(material);
            }
        }
        return ePlain;
    }

    void Explosion::createNodesAt(cocos2d::CCPoint const& center, cocos2d::CCTMXTiledMap *tileMap)
    {
        using namespace cocos2d;

        CCSprite *explode = CCSprite::create();
        explode->setPosition(center);
        explode->setVisible(false);
        CCAnimation *animation = Utility::AnimationLoader::explosionAnimation();
        
        CCAnimate* action = CCAnimate::create(animation);
        AnimatedNode node;
        node.setAction(action);
        node.setNode(explode);
        _animateNodes.push_back(node);
        cocos2d::CCTMXLayer *blockLayer = tileMap->layerNamed("Blocks");
        cocos2d::CCPoint mapCoord;
        for(int d = 0;d < 4;d++)
        {//4 direction.
            CCPoint p = center;
            float* property = (d%2) == 0? &(p.x) : &(p.y);
            int sign = (d/2) == 0? -1:1;
            
            for (int radius = 1,end = (_range- 16)/16; radius <= end; radius ++) {
                (*property)+= (sign * 16);
                if(radius%2 == 0)
                {
                    Material mat = getTileMaterial(tileMap, blockLayer, p,mapCoord);

                    if(mat == eSolid)
                    {
                        break;
                    }
                    else if(mat == eDestroyable)
                    {
                        _destroyMapcoords.push_back(mapCoord);
                    }
                }
                CCAnimate* action = CCAnimate::create(animation);
                CCSequence* seq = CCSequence::create(CCDelayTime::create(radius*0.05),action,NULL);
                
                CCSprite* expSprite = CCSprite::create();
                expSprite -> setPosition(p);
                expSprite->setVisible(false);
                node.setAction(seq);
                node.setNode(expSprite);
                _animateNodes.push_back(node);
            }
       
        }
    }
    

    
    void Explosion::destroyBlocks(cocos2d::CCTMXTiledMap *tileMap)
    {
        using namespace cocos2d;
        CCTMXLayer *layer = tileMap->layerNamed("Blocks");
        for (std::vector<CCPoint>::iterator it = _destroyMapcoords.begin(); it != _destroyMapcoords.end(); ++it)
        {
            CCSprite *tile = layer ->tileAt(*it);
            if(tile)
            {
                CCSequence* seq = CCSequence::create(CCDelayTime::create(0.3),CCCallFuncND::create(this, callfuncND_selector(Simulation::Explosion::removeTile), layer),NULL);
                tile->runAction(seq);
            }
        }

    }
    
    void Explosion::removeTile(cocos2d::CCNode *tile, void *blockLayer)
    {
        cocos2d::CCTMXLayer* layer = static_cast<cocos2d::CCTMXLayer*>(blockLayer);
        if (tile->getParent()) {
            layer->removeChild(tile, true);
        }
    }
    
    unsigned int Explosion::getNodesCount()
    {
        return _animateNodes.size();
    }
    
    cocos2d::CCNode* Explosion::getNodeAt(unsigned int index)
    {
        return _animateNodes[index].getNode();
    }
    
    bool Explosion::isFinished()
    {
        return _isFinished;
    }
}