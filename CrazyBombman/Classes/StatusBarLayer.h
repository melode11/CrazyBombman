//
//  StatusBarLayer.h
//  CrazyBombman
//
//  Created by Yao Melo on 8/13/13.
//
//

#ifndef __CrazyBombman__StatusBarLayer__
#define __CrazyBombman__StatusBarLayer__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;
class StatusBar :public CCLayer
{
private:
    CCLabelAtlas *_labelMobCount;
    CCLabelAtlas *_labelRestHP;
    CCLabelAtlas *_labelRestBombs;
public:
    StatusBar();
    ~StatusBar();
    void updateStatus(unsigned int restMobCount,int restHP,int restBombs = 0);
    bool init();
    CREATE_FUNC(StatusBar);
};

#endif /* defined(__CrazyBombman__StatusBarLayer__) */
