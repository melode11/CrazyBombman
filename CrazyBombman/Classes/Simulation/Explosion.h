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
        
        AnimatedNode():_node(0),_action(0)
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
        
    public:
        void createNodesAt(cocos2d::CCPoint const & center);
        
        Explosion();
        
        ~Explosion();
        
        virtual bool init();
        
        virtual void update(float dt);
        
        CC_SYNTHESIZE(float, _range, Range);
        
        CREATE_FUNC(Explosion);
    };
}

#endif /* defined(__CrazyBombman__Explosion__) */
