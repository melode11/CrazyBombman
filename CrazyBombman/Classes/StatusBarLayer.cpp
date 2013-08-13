//
//  StatusBarLayer.cpp
//  CrazyBombman
//
//  Created by Yao Melo on 8/13/13.
//
//

#include "StatusBarLayer.h"
#include "ArtworkLoader.h"

bool StatusBar::init()
{
    return true;
}

StatusBar::StatusBar()
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCSprite* bg = Utility::ArtworkLoader::statusBarSprite();
    CCSize contentSize(size.width,60);
    this->setContentSize(contentSize);
    bg->setScaleX(size.width/bg->getContentSize().width);
    bg->setScaleY(60/bg->getContentSize().height);
    bg->setAnchorPoint(ccp(0.0,0.0));
    bg->setPosition(ccp(0.0, 0.0));
    bg->setContentSize(contentSize);
    addChild(bg);
    
    CCNode* container = CCNode::create();
    
    float xpos = 0;
    CCSprite* player = Utility::ArtworkLoader::playerSprite();
    
    player->setAnchorPoint(ccp(0.0,0.0));
    player->setPosition(ccp(xpos,10));
    container->addChild(player);
    xpos+=player->getContentSize().width;
    xpos+=5;
    float factor = size.height / 320.0f;
    CCTexture2D* texture = CCTextureCache::sharedTextureCache()->textureForKey("cc_fps_images");
    _labelRestHP = new CCLabelAtlas();
    _labelRestHP->setAnchorPoint(ccp(0.0,0.0));
    _labelRestHP->initWithString("0", texture, 12, 32, '.');
    _labelRestHP->setPosition(ccp(xpos,10));
    _labelRestHP->setScale(factor);
    container->addChild(_labelRestHP);
    xpos+=100;
    CCSprite* mob = Utility::ArtworkLoader::mobSprite(0);
    mob->setAnchorPoint(ccp(0.0,0.0));
    mob->setPosition(ccp(xpos,10));
    container->addChild(mob);
    xpos+=mob->getContentSize().width;
    xpos+=5;
    
    _labelMobCount = new CCLabelAtlas();
    
    _labelMobCount->setAnchorPoint(ccp(0.0,0.0));
    _labelMobCount->initWithString("0", texture, 12, 32, '.');
    _labelMobCount->setPosition(ccp(xpos,10));
    _labelMobCount->setScale(factor);
    xpos+=24;
    container->addChild(_labelMobCount);
    container->setContentSize(ccp(xpos,60));
    container->setAnchorPoint(ccp(0.5,0.5));
    container->setPosition(ccp(size.width*0.5,30));
    addChild(container);
}

StatusBar::~StatusBar()
{
    CC_SAFE_RELEASE(_labelMobCount);
    CC_SAFE_RELEASE(_labelRestHP);
}

void StatusBar::updateStatus(unsigned int restMobCount, int restHP)
{
    if(_labelMobCount == NULL || _labelRestHP == NULL)
    {
        return;
    }
    char buf[10];
    snprintf(buf, 10, "%d",restMobCount);
    _labelMobCount->setString(buf);
    snprintf(buf, 10, "%d",restHP);
    _labelRestHP->setString(buf);
}