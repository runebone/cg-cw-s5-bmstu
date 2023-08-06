cmake_minimum_required(VERSION 3.10)
project(cgcw VERSION 1.0.0)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(DEPS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/deps)

set(LIBS_DIR /nix/var/nix/profiles/per-user/human/profile/lib)
set(INCS_DIR /nix/var/nix/profiles/per-user/human/profile/include)

set(SOURCE
    # ${SOURCE_DIR}/algorithm.cpp
    )


include_directories(
    ${INCS_DIR} # Needed for <GL/gl.h>, glm stuff
    ${DEPS_DIR} # Needed for "GLFW/glfw3.h"
    ${DEPS_DIR}/OpenGL/glad
    ${DEPS_DIR}/ImGui
    )

link_directories(
    ${LIBS_DIR} # Needed for -lGL -lX11 -lXrandr -lXi
    ${DEPS_DIR}/GLFW/lib
    )


list(APPEND OPENGL_LIBRARIES "-ldl -lGL -lX11 -lpthread -lXrandr -lXi -lglfw3")

# ADD OpenGL LIBRARY: glad
add_library(glad STATIC
    ${DEPS_DIR}/OpenGL/glad/glad.c
    )

# ADD LIBRARY: imgui
add_library(imgui STATIC
    ${DEPS_DIR}/ImGui/imgui.cpp
    ${DEPS_DIR}/ImGui/imgui_demo.cpp
    ${DEPS_DIR}/ImGui/imgui_draw.cpp
    ${DEPS_DIR}/ImGui/imgui_tables.cpp
    ${DEPS_DIR}/ImGui/imgui_widgets.cpp
    ${DEPS_DIR}/ImGui/imgui_impl_glfw.cpp
    ${DEPS_DIR}/ImGui/imgui_impl_opengl3.cpp
    )


set(EXE "main")
add_executable(${EXE} ${SOURCE} ${SOURCE_DIR}/main.cpp)

target_link_libraries(${EXE} ${OPENGL_LIBRARIES} glad imgui)
