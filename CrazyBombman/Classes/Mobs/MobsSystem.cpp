//
//  MobsSystem.cpp
//  CrazyBombman
//
//  Created by Yao Melo on 7/14/13.
//
//

#include "MobsSystem.h"
#include "ArtworkLoader.h"

namespace Simulation
{
    Mob* randomMob(Level lvl,b2World* world)
    {
        MobPrototype proto(lvl);
        unsigned int mobId = proto.randomMobId();
        Mob* mob = Mob::create(mobId, proto.getLevel(), proto.hitpoint(), "mob",MOB_VELOCITY);
       
        return mob;
    }
    
    bool MobsSystem::init()
    {
        return true;
    }
    
    void MobsSystem::update(float dt)
    {
        CCObject* obj;
        vector<int> removeIndex;
        int index = 0;
        CCARRAY_FOREACH(_mobs, obj)
        {
            Mob* mob = (Mob*)obj;
            if(mob->isDead())
            {
                _destoryMobs->addObject(mob);
                removeIndex.push_back(index);
            }
            else
            {
                CCPoint p = mob->getNode()->getPosition();
                mob->update(dt);
            }
            ++index;
        }
        
        for (vector<int>::reverse_iterator it = removeIndex.rbegin(); it!=removeIndex.rend(); ++it) {
            _mobs->removeObjectAtIndex(*it);
        }
        this->spawnMob(dt);
        //FIXME: add mob destroy detection.
    }
    
    void MobsSystem::spawnMob(float dt)
    {
        _timeIntervalFromLastSpawn+=dt;
        if( _timeIntervalFromLastSpawn<_spawnInterval||_waitingMobCount == 0)
        {
            return;
        }
        _timeIntervalFromLastSpawn = 0;
        if(_mobs->count()<_maxMobCount)
        {
            Mob* mob = randomMob(1,_world);
            _mobs->addObject(mob);
            _spawnMobs->addObject(mob);
            _waitingMobCount--;
        }
    }
    
    void MobsSystem::updateMobsOnMap(cocos2d::CCTMXTiledMap *tilemap,GameModelDelegate *delegate)
    {
        if(tilemap == NULL || delegate == NULL)
        {
            return;
        }
        if(_batchNode == NULL)
        {
            _batchNode = CCSpriteBatchNode::createWithTexture(Utility::ArtworkLoader::mobsTexture(),50);
        }
        if(_batchNode->getParent() == NULL)
        {
            delegate->addNode(_batchNode, Z_MOBS);
        }
        
        CCObject* obj;
        CCTMXObjectGroup *mobsLayer = tilemap->objectGroupNamed(TILE_MAP_MOB_LAYER);
        CCARRAY_FOREACH(_spawnMobs, obj)
        {
            CCArray* mobSpawns = mobsLayer->getObjects();
            unsigned int index;
            unsigned int count = mobSpawns->count();
            do {
                index = (unsigned int)(count * CCRANDOM_0_1());
            } while (index >= count);
            CCDictionary* dic = (CCDictionary*)mobSpawns->objectAtIndex(index);
            float x = ((CCString*)dic->objectForKey("x"))->floatValue();
            float y = ((CCString*)dic->objectForKey("y"))->floatValue();
            Mob* mob = (Mob*)obj;
            mob->getNode()->setPosition(ccp(x,y));
            mob->initBody(_world);
            mob->freeMove();
            _batchNode->addChild(mob->getNode(), Z_MOBS);
        }
        _spawnMobs->removeAllObjects();
        
        CCARRAY_FOREACH(_destoryMobs, obj)
        {
            Mob* mob = (Mob*)obj;
            _batchNode->removeChild(mob->getNode(), true);
            mob->clearBody(_world);
        }
        _destoryMobs->removeAllObjects();
    }

    
    MobsSystem::~MobsSystem()
    {
        CC_SAFE_RELEASE(_spawnMobs);
        CC_SAFE_RELEASE(_mobs);
        CC_SAFE_RELEASE(_destoryMobs);
    }
}