//
//  PhysicsSolver.hpp
//  gl-pong-demo
//
//  Created by Jake Pauls on 2022-03-23.
//

#ifndef PhysicsSolver_hpp
#define PhysicsSolver_hpp

#include "Box2D/Box2D.h"
#include "Box2D/Dynamics/b2Body.h"

class PhysicsSolver {
public:
    PhysicsSolver();
    
    void Test();
    
private:
    b2Vec2* _gravity;
    b2World* _world;
    
    b2Body* _groundBody;
    b2BodyDef* _groundBodyDef;
    b2PolygonShape* _groundBox;
};

#endif /* PhysicsSolver_hpp */
