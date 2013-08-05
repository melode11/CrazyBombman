//
//  GameOverScene.cpp
//  CrazyBombman
//
//  Created by Yao Melo on 8/3/13.
//
//

#include "GameOverScene.h"
#include "CCTextureCache.h"
USING_NS_CC;

CCScene* GameOverScene::scene()
{
    CCScene* scene = CCScene::create();
    scene->addChild(GameOverScene::create());
    return scene;
}

bool GameOverScene::init()
{
    _gameoverLabel = new CCLabelAtlas();
    CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("blocks.png");
    _gameoverLabel->initWithString("GAMEOVER",texture, 64,64, 'A');
    _gameoverLabel->setAnchorPoint(ccp(0.5,0.5));
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    _gameoverLabel->setPosition(winSize.width/2, winSize.height/2);
    this->addChild(_gameoverLabel);
    return true;
}

GameOverScene::~GameOverScene()
{
    CC_SAFE_DELETE(_gameoverLabel);
}
