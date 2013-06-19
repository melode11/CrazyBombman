//
//  Environment.h
//  CrazyBomber
//
//  Created by Yao Melo on 6/18/13.
//
//

#ifndef __CrazyBomber__Environment__
#define __CrazyBomber__Environment__

#include <iostream>
#include "cocos2d.h"
#include "Player.h"


namespace Simulation
{
    
    static inline cocos2d::CCRect getCCRect(cocos2d::CCNode* node)
    {
        if(node)
        {
            cocos2d::CCSize size = node->getContentSize();
            cocos2d::CCPoint p = node->getPosition();
            using namespace cocos2d;
            return CCRectMake(p.x - size.width/2, p.y - size.height/2, size.width, size.height);
        }
        return cocos2d::CCRectZero;
    }
    
    class Environment :public cocos2d::CCObject
    {
    private:
        cocos2d::CCTMXTiledMap *_tileMap;
    protected:
        bool checkCollision();
    public:
        Environment(){};
        
        ~Environment(){};
        
        virtual void update(float dt);
        
        bool init();
        
        void setTileMap(cocos2d::CCTMXTiledMap *tileMap);
        
        
        CC_SYNTHESIZE_RETAIN(Player*, _player, Player);

        CREATE_FUNC(Environment);
    };
}
#endif /* defined(__CrazyBomber__Environment__) */
