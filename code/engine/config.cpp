#include "config.h"

float gTargetFPS = 0.0f;
glm::vec3 gGravity{0.0f, -9.81f, 0.0f};
float gStaticFrictionCoef = 0.5f;
float gKineticFrictionCoef = 0.3f;
bool gRenderAABB = false;
int gDrawCalls = 0;
bool gRenderByTriangles = false;
