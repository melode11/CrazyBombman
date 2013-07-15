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
#include "MobsSystem.h"
#include "SceneLevelParams.h"

namespace Simulation
{
    
    
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
    
    class Environment :public cocos2d::CCObject,public CollisionDetectDelegate
    {
    private:
        cocos2d::CCTMXTiledMap *_tileMap;
        cocos2d::CCArray *_bombs;
        cocos2d::CCArray *_explosions;
        MobsSystem* _mobsSystem;
        SceneLevelParams _slp;
        //hide copy constructor
        Environment(Environment const &env);
        Environment& operator= (Environment const &env);
        
    protected:
        void updateBombs(float dt);
        void updateExplosions(float dt);
        void updateMob(float dt);
        
        bool checkCollision(cocos2d::CCPoint& newP, cocos2d::CCPoint const& prevP);
    public:
        Environment():_player(0),_ppDelegate(0),_tileMap(0),_bombs(0),_slp(),_mobsSystem(0)
        {};
        
        Environment(SceneLevelParams const& slp):_player(0),_ppDelegate(0),_tileMap(0),_bombs(0),_slp(slp),_mobsSystem(0)
        {};
        
        ~Environment();
        
        virtual void update(float dt);
        
        bool init();
        
        void setTileMap(cocos2d::CCTMXTiledMap *tileMap);
        
        void addBomb(Bomb* bomb);
        
        void spawnPlayer();
        
        virtual bool checkMoveCollision(cocos2d::CCPoint& dest,cocos2d::CCPoint const& start,cocos2d::CCSize const& subjectSize);
        
        CC_SYNTHESIZE_RETAIN(Player*, _player, Player);
        
        CC_SYNTHESIZE(GameModelDelegate*, _ppDelegate, Delegate);
        
        CREATE_FUNC(Environment);
        
        static Environment* create(SceneLevelParams const& slp);
        
    };
}
#endif /* defined(__CrazyBomber__Environment__) */
