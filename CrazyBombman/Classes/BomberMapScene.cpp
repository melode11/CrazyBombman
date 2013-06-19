//
//  BomberMapScene.cpp
//  CrazyBomber
//
//  Created by Yao Melo on 6/17/13.
//
//

#include "BomberMapScene.h"
using namespace cocos2d;

static double lastTime;

CCSprite* spawnPlayer(CCTMXTiledMap *tileMap,CCLayer* layer)
{
    CCTMXObjectGroup *group = tileMap->objectGroupNamed("Objects");
    CCDictionary *spawn = group->objectNamed("PlayerSpawn");
    float x = ((CCString*)spawn->objectForKey("x"))->floatValue();
    float y = ((CCString*)spawn->objectForKey("y"))->floatValue();
    CCSprite *player = CCSprite::create("Player.png");
    player->setPosition(ccp(x, y));
    layer->addChild(player);
    return player;
}

void setViewPointCenter(CCLayer* layer, const CCPoint& position,const CCSize& mapSize, const CCSize& tileSize)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSizeInPixels();
    int x = MAX(position.x, winSize.width/2);
    int y = MAX(position.y, winSize.height/2);
    x = MIN(x, (mapSize.width * tileSize.width) - winSize.width / 2);
    y = MIN(y, (mapSize.height * tileSize.height) - winSize.height/2);
    CCPoint actualPosition = ccp(x, y);
    
    CCPoint centerOfView = ccp(winSize.width/2, winSize.height/2);
    CCPoint viewPoint = ccpSub(centerOfView, actualPosition);
    layer->setPosition(viewPoint);
}


bool BomberMapScene::init()
{
    this->_tileMap = CCTMXTiledMap::create("bombermap.tmx");
    this->addChild(this->_tileMap,-1);
    CCSprite *playerNode = spawnPlayer(this->_tileMap, this);
    this->_tileMap->setContentSize(CCDirector::sharedDirector()->getWinSizeInPixels());
    setViewPointCenter(this,playerNode->getPosition(),_tileMap->getMapSize(),_tileMap->getTileSize());
    _player = Simulation::Player::create();
    _player->setPlayerNode(playerNode);
    _player->retain();
    lastTime = 0;
    this->setAccelerometerEnabled(true);
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
    if(!_player)
    {
        return;
    }
    double x = pAccelerationValue->x;
    double y = pAccelerationValue->y;
//    double zabs = fabs(pAccelerationValue->z);
    if(fabs(x) > fabs(y) && fabs(x)>0.05)
    {
        this->_player->setDirection(x>0?Simulation::eRight:Simulation::eLeft);

    }
    else if(fabs(y) > 0.05)
    {
        this->_player->setDirection(y>0?Simulation::eUp:Simulation::eDown);
    }
    else
    {
        this->_player->setDirection(Simulation::eNone);
    }
    if(lastTime==0)
    {
        lastTime = pAccelerationValue->timestamp;
    }
    else
    {
        this->_player->update(pAccelerationValue->timestamp - lastTime);
        setViewPointCenter(this, this->_player->getPlayerPosition(),_tileMap->getMapSize(), _tileMap->getTileSize());
        lastTime = pAccelerationValue->timestamp;
    }
    
}

BomberMapScene::~BomberMapScene()
{
    CC_SAFE_RELEASE(_player);
//    CC_SAFE_RELEASE(_tileMap);
}

