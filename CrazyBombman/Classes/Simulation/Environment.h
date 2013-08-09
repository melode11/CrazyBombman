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
#include "Box2D.h"
#include "PhysicsObject.h"
#include "GLES-Render.h"
#include "ContactFilter.h"
#include "ContactListener.h"

namespace Simulation
{    
    
    
    class TileInfo:public PhysicsObject
    {
    public:
        TileInfo():material(ePlain),mapcoord(0,0)
        {
            
        }
        
        virtual PhysicalType getPhysicalType();
        
        Material material;
        
        cocos2d::CCPoint mapcoord;
        
    };
    
    class Environment :public cocos2d::CCObject,public CollisionDetectDelegate
    {
    private:
        cocos2d::CCTMXTiledMap *_tileMap;
        cocos2d::CCArray *_bombs;
        cocos2d::CCArray *_explosions;
        cocos2d::CCArray *_blockTiles;
        ContactLisenter _contactListener;
        ContactFilter _contactFilter;
        MobsSystem* _mobsSystem;
        SceneLevelParams _slp;
        //hide copy constructor
        Environment(Environment const &env);
        Environment& operator= (Environment const &env);
        b2World *_world;
        bool _isGameover;
    protected:
        void updateBombs(float dt);
        void updateExplosions(float dt);
        void updateMob(float dt);
        void updatePlayer(float dt);
        
        void buildPhysicalMap(cocos2d::CCTMXTiledMap* tilemap);
        
        bool checkCollision(cocos2d::CCPoint& newP, cocos2d::CCPoint const& prevP);
    public:
        Environment():_player(0),_ppDelegate(0),_tileMap(0),_bombs(0),_slp(),_mobsSystem(0),_contactFilter(),_contactListener(),_isGameover(false)
        {};
        
        Environment(SceneLevelParams const& slp):_player(0),_ppDelegate(0),_tileMap(0),_bombs(0),_slp(slp),_mobsSystem(0),_isGameover(false)
        {};
        
        ~Environment();
        
        virtual void update(float dt);
        
        bool init();
        
        void setTileMap(cocos2d::CCTMXTiledMap *tileMap);
        
        void addBomb(Bomb* bomb);
        
        void spawnPlayer();
        
        bool checkGameResult();
        
        virtual bool checkMoveCollision(cocos2d::CCPoint& dest,cocos2d::CCPoint const& start,cocos2d::CCSize const& subjectSize);
        
        void setDebugDraw(cocos2d::extension::GLESDebugDraw* debugDraw);
        
        void drawDebugInfo();
        
        CC_SYNTHESIZE_RETAIN(Player*, _player, Player);
        
        CC_SYNTHESIZE(GameModelDelegate*, _ppDelegate, Delegate);
        
        CREATE_FUNC(Environment);
        
        static Environment* create(SceneLevelParams const& slp);
        
    };
}
#endif /* defined(__CrazyBomber__Environment__) */
