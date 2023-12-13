#ifndef __CONFIG_H__
#define __CONFIG_H__

#define CFG_PROJECT_DIR "/home/human/University/cg-cw-s4-bmstu/code/"

#define CFG_ASSETS_DIR  CFG_PROJECT_DIR "assets/"
#define CFG_SOURCE_DIR  CFG_PROJECT_DIR "engine/"
#define CFG_OBJECTS_DIR CFG_ASSETS_DIR  "objects/"
#define CFG_FONTS_DIR   CFG_ASSETS_DIR  "fonts/"
#define CFG_MAIN_FONT   CFG_FONTS_DIR   "mononoki-Regular.ttf"
#define CFG_SHADERS_DIR CFG_ASSETS_DIR  "shaders/"

#define CFG_WINDOW_NAME "Runov IU7-54B Engine"

#include <glm/glm.hpp>

extern float gTargetFPS;
extern glm::vec3 gGravity;
extern float gStaticFrictionCoef;
extern float gKineticFrictionCoef;
extern bool gRenderAABB;
extern int gDrawCalls;
extern bool gRenderByTriangles;
extern long gRenderTime;

#define CFG_BENCHMARK_FILE CFG_PROJECT_DIR "benchmark.csv"

#endif // __CONFIG_H__
