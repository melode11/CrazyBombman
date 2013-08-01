//
//  BomberMapScene.cpp
//  CrazyBomber
//
//  Created by Yao Melo on 6/17/13.
//
//

#include "BomberMapScene.h"
#include "TileUtils.h"
#include "Simulation.h"
#include "ArtworkLoader.h"
#include "SceneLevelParams.h"
#include <OpenGLES/ES1/gl.h>

using namespace cocos2d;


//void testMapHelper(CCTMXTiledMap *tileMap)
//{
//    std::vector<CCPoint> coords;
//    Utility::GetMapCoordsOnPath(tileMap, ccp(450,800), ccp(800,200), coords);
//    float delaytime = 0;
//    printf("coords size:%ld",coords.size());
//    for (std::vector<CCPoint>::iterator it = coords.begin(); it != coords.end() ; it++) {
//        CCTMXLayer* layer = tileMap->layerNamed("Backgroud");
//        CCSprite* tile = layer->tileAt(ccp((int)it->x, (int)it->y));
//        CCSequence *seq = CCSequence::create(CCDelayTime::create(delaytime),CCHide::create(),NULL);
//        tile->runAction(seq);
//        delaytime+= 0.1f;
//        
//    }
//}



void setViewPointCenter(CCLayer* layer, const CCPoint& position,const CCSize& mapSize, const CCSize& tileSize)
{
    int mapW = mapSize.width * tileSize.width;
    int mapH = mapSize.height * tileSize.height;
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    int offsetX = MAX(0,(winSize.width - mapW)/2);
    int offsetY = MAX(0,(winSize.height - mapH)/2);
    int x = MIN(position.x, mapW - winSize.width / 2 + offsetX);
    int y = MIN(position.y, mapH - winSize.height/2 + offsetY);
    x = MAX(x, winSize.width/2 - offsetX);
    y = MAX(y, winSize.height/2- offsetY);
    CCPoint actualPosition = ccp(x, y);
    
    CCPoint centerOfView = ccp(winSize.width/2, winSize.height/2);
    CCPoint viewPoint = ccpSub(centerOfView, actualPosition);
    layer->setPosition(viewPoint);
}


bool BomberMapScene::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    this->_tileMap = CCTMXTiledMap::create(TILE_MAP_FILE);
    this->_tileMap->retain();
    this->_tileMap->layerNamed(TILE_MAP_MATERIAL_LAYER)->setVisible(false);
#ifndef PHYSICS_DEBUG
    this->addChild(this->_tileMap,-1);
#endif
    this->_tileMap->setContentSize(CCDirector::sharedDirector()->getWinSize());

    _env = Simulation::Environment::create(*(Simulation::SceneLevelParams::globalSceneLevelParams()));
    _env->retain();
    _env->setTileMap(this->_tileMap);
    _env->setDelegate(this);
    _env->spawnPlayer();
#ifdef PHYSICS_DEBUG
    _debugDraw = new cocos2d::extension::GLESDebugDraw(1.0);
    uint32 flags = 0;
    flags|=cocos2d::extension::GLESDebugDraw::e_shapeBit;
    _debugDraw->SetFlags(flags);
    _env->setDebugDraw(_debugDraw);
#endif
    CCDirector::sharedDirector()->getScheduler()->scheduleUpdateForTarget(_env, 0, false);
    this->setAccelerometerEnabled(true);
    this->setTouchEnabled(true);
    srand((unsigned int)time(NULL));
    return true;
}

CCScene* BomberMapScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    BomberMapScene *layer = BomberMapScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

void BomberMapScene::didAccelerate(CCAcceleration* pAccelerationValue)
{
    if(!_env || !_env->getPlayer())
    {
        return;
    }
    Simulation::Player *player = _env -> getPlayer();
    double x = pAccelerationValue->x;
    double y = pAccelerationValue->y;
//    double zabs = fabs(pAccelerationValue->z);
    if(fabs(x) > fabs(y) && fabs(x)>0.1)
    {
        player->setDirection(x>0?Simulation::eRight:Simulation::eLeft);
    }
    else if(fabs(y) > 0.1)
    {
        player->setDirection(y>0?Simulation::eUp:Simulation::eDown);
    }
    else
    {
        player->setDirection(Simulation::eNone);
    }
}

void BomberMapScene::updatePlayerPostion(CCPoint &postion)
{
    setViewPointCenter(this, postion, _tileMap->getMapSize(), _tileMap->getTileSize());
}

void BomberMapScene::addNode(cocos2d::CCNode *node, int z_order)
{
    if(node)
    {
        this->addChild(node, z_order);
    }
}

void BomberMapScene::removeNode(cocos2d::CCNode *node)
{
    if(node)
    {
        this->removeNode(node);
    }
}

void BomberMapScene::ccTouchesEnded(cocos2d::CCSet *pTouch, cocos2d::CCEvent *pEvent)
{
    CCSprite* bombNode = Utility::ArtworkLoader::bombSprite();
    CCPoint position = _env->getPlayer()->getPlayerPosition();
    CCSize size = _tileMap->getTileSize();
    bombNode->setPosition(ccp(((int)(position.x/size.width) + 0.5)*size.width, (ceil(position.y/size.height)-0.5)*size.width));
    Simulation::Bomb *bomb = Simulation::Bomb::create();
    bomb->setNode(bombNode);
    _env->addBomb(bomb);
}


BomberMapScene::~BomberMapScene()
{
    if(_env->getDelegate() == this)
    {
        _env->setDelegate(NULL);
    }
    CC_SAFE_RELEASE(_env);
    CC_SAFE_RELEASE(_tileMap);
#ifdef PHYSICS_DEBUG
    CC_SAFE_DELETE(_debugDraw);
#endif
}

void BomberMapScene::draw()
{
    CCLayer::draw();
#ifdef PHYSICS_DEBUG
    _env->drawDebugInfo();
#endif
    
}

