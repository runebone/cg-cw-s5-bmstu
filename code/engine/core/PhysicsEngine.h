#ifndef __PHYSICS_ENGINE_H__
#define __PHYSICS_ENGINE_H__

#include "../util/typedefs.h"

class PhysicsEngine {
public:
    PhysicsEngine();
    ~PhysicsEngine();

    void update(f32 deltaTime);
};

#endif // __PHYSICS_ENGINE_H__
