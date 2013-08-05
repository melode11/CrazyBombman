//
//  GameOverScene.h
//  CrazyBombman
//
//  Created by Yao Melo on 8/3/13.
//
//

#ifndef __CrazyBombman__GameOverScene__
#define __CrazyBombman__GameOverScene__

#include <iostream>
#include "cocos2d.h"
#include "CCLabelAtlas.h"
class GameOverScene :public cocos2d::CCLayer
{
private:
    cocos2d::CCLabelAtlas *_gameoverLabel;
public:
    static cocos2d::CCScene* scene();
    
    virtual bool init();
    
    CREATE_FUNC(GameOverScene);
    
    GameOverScene():_gameoverLabel(NULL)
    {
        
    }
    
    ~GameOverScene();
};

#endif /* defined(__CrazyBombman__GameOverScene__) */
