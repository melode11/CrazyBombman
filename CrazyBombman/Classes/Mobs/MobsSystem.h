//
//  MobsSystem.h
//  CrazyBombman
//
//  Created by Yao Melo on 7/14/13.
//
//

#ifndef __CrazyBombman__MobsSystem__
#define __CrazyBombman__MobsSystem__

#include <iostream>
#include "Mob.h"
#include "cocos2d.h"
#include "Simulation.h"
#include "Delegations.h"
#include "Box2D.h"

namespace Simulation
{
    class MobsSystem : public cocos2d::CCObject
    {
        
        CC_SYNTHESIZE(unsigned int, _maxMobCount, MaxMobCount);
        CC_SYNTHESIZE(float, _spawnInterval, SpawnInterval);
        CC_SYNTHESIZE(b2World*, _world, World);

    private:
        cocos2d::CCArray* _spawnMobs;
        cocos2d::CCArray* _mobs;
        cocos2d::CCArray* _destoryMobs;
        cocos2d::CCSpriteBatchNode* _batchNode;
        float _timeIntervalFromLastSpawn;
        unsigned int _waitingMobCount;
    protected:
        void spawnMob(float dt);
    public:
        MobsSystem():_spawnMobs(NULL), _mobs(NULL),_destoryMobs(NULL),_batchNode(NULL), _maxMobCount(INITIAL_MAX_MOB_COUNT),_waitingMobCount(INITIAL_MAX_MOB_COUNT),_spawnInterval(INITIAL_MOB_SPAWN_INTERVAL),_timeIntervalFromLastSpawn(0),_world(0)
        {
            _spawnMobs = new CCArray(1);
            _mobs = new CCArray(20);
            _destoryMobs = new CCArray(3);
        }
        
        ~MobsSystem();
        
        void setWaitingMobCount(unsigned int waitingMobCount)
        {
            _waitingMobCount = waitingMobCount;
        }
        
        unsigned int getRestMobCount()
        {
            return _waitingMobCount + _mobs->count();
        }
        
        virtual bool init();
        virtual void update(float dt);
        //spawnMob
        void updateMobsOnMap(cocos2d::CCTMXTiledMap *tilemap,GameModelDelegate* delegate);
        CREATE_FUNC(MobsSystem);
    };
}
#endif /* defined(__CrazyBombman__MobsSystem__) */
