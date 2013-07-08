//
//  Explosion.h
//  CrazyBombman
//
//  Created by Yao Melo on 6/23/13.
//
//

#ifndef __CrazyBombman__Explosion__
#define __CrazyBombman__Explosion__

#include <iostream>
#include "cocos2d.h"
#include <vector>

namespace Simulation {
    
    class AnimatedNode
    {
        CC_SYNTHESIZE_RETAIN(cocos2d::CCNode*, _node, Node);
        CC_SYNTHESIZE_RETAIN(cocos2d::CCAction*, _action, Action);
    public:
        bool isAnimated;
        
        AnimatedNode(AnimatedNode const& node):_node(node._node),_action(node._action),isAnimated(node.isAnimated)
        {
            CC_SAFE_RETAIN(_node);
            CC_SAFE_RETAIN(_action);
        }
        
        AnimatedNode& operator=(AnimatedNode const& node)
        {
            this->setAction(node.getAction());
            this->setNode(node.getNode());
            return *this;
        }
        
        AnimatedNode():_node(0),_action(0),isAnimated(false)
        {
            
        }
        
        ~AnimatedNode()
        {
            CC_SAFE_RELEASE(_node);
            CC_SAFE_RELEASE(_action);
        }
    };
    
    class Explosion : public cocos2d::CCObject
    {
    private:
        std::vector<AnimatedNode> _animateNodes;
        std::vector<cocos2d::CCPoint> _destroyMapcoords;
        bool _isFinished;
        void removeTile(cocos2d::CCNode *tile, void* callbackObj);
    public:
        void createNodesAt(cocos2d::CCPoint const& center, cocos2d::CCTMXTiledMap *tileMap);
        
        void destroyBlocks(cocos2d::CCTMXTiledMap *tileMap);
        
        unsigned int getNodesCount();
        
        cocos2d::CCNode* getNodeAt(unsigned int index);
        
        Explosion();
        
        ~Explosion();
        
        virtual bool init();
        
        virtual void update(float dt);
        
        bool isFinished();
        
        CC_SYNTHESIZE(float, _range, Range);
        
        CREATE_FUNC(Explosion);
    };
}

#endif /* defined(__CrazyBombman__Explosion__) */
