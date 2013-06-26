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
#include "Delegations.h"
#include <vector>
#include "Bomb.h"

namespace Simulation
{
    
    static inline cocos2d::CCRect getCCRect(cocos2d::CCNode* node)
    {
        if(node)
        {
            cocos2d::CCSize size = node->getContentSize();
            cocos2d::CCPoint p = node->getPosition();
            cocos2d::CCPoint anchor;
            anchor.operator=(node->getAnchorPoint());
            using namespace cocos2d;
            return CCRectMake(p.x - anchor.x, p.y - anchor.y, size.width, size.height);
        }
        return cocos2d::CCRectZero;
    }
    
//    static inline cocos2d::CCRect getCCRectForLeftBottomAligned(cocos2d::CCNode* node)
//    {
//        if(node)
//        {
//            cocos2d::CCSize size = node->getContentSize();
//            cocos2d::CCPoint p = node->getPosition();
//            using namespace cocos2d;
//            return CCRectMake(p.x, p.y, size.width, size.height);
//        }
//        return cocos2d::CCRectZero;
//    }
    
    class Environment :public cocos2d::CCObject
    {
    private:
        cocos2d::CCTMXTiledMap *_tileMap;
        cocos2d::CCArray *_bombs;
        cocos2d::CCArray *_explosions;
        //hide copy constructor
        Environment(Environment const &env);
        Environment& operator= (Environment const &env);
        
    protected:
        void updateBombs(float dt);
        void updateExplosions(float dt);
        bool checkCollision(cocos2d::CCPoint& postion);
    public:
        Environment():_player(0),_ppDelegate(0),_tileMap(0),_bombs(0)
        {};
        
        
        ~Environment();
        
        virtual void update(float dt);
        
        bool init();
        
        void setTileMap(cocos2d::CCTMXTiledMap *tileMap);
        
        void addBomb(Bomb* bomb);
        
        CC_SYNTHESIZE_RETAIN(Player*, _player, Player);

        CC_SYNTHESIZE(GameModelDelegate*, _ppDelegate, Delegate);
        
        CREATE_FUNC(Environment);
    };
}
#endif /* defined(__CrazyBomber__Environment__) */
