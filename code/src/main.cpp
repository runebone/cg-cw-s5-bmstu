#include <iostream>

#include "glad.h"
#include "gl_call.h"
#include "GLFW/glfw3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ui.h"
#include "type_aliases.h"

#define __MAIN__
#include "main_globals.h"
bool g_render_by_triangles = true;
bool g_depth_test_enabled = true;
bool g_cull_face_enabled = false;
bool g_r_pressed = false;
bool g_z_pressed = false;
bool g_c_pressed = false;

#include "shader.h"
#include "mesh.h"
#include "render.h"

#include "config.h"

void process_input(GLFWwindow *window);
void mouse_callback(GLFWwindow *window, f64 xpos, f64 ypos);

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

GLFWwindow *create_window(u32 width, u32 height, const char *title) {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(width, height, title, NULL, NULL);

    return window;
}

int main() {
    glfwInit();

    GLFWwindow *window = create_window(1200, 900, "Window");

    glfwMakeContextCurrent(window);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    UI::init_imgui(window);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);

    glfwSwapInterval(0); // Disable VSync

    glm::vec4 clear_color = glm::vec4(0.3f, 0.3f, 0.3f, 1.0f);
    glm::vec4 color = glm::vec4(1.0f, 0.5f, 0.3f, 1.0f);

    auto &cc = clear_color;

    Mesh teapot, cube, plane, triangle;
    teapot.load_from_obj(OBJECTS_DIR "utah_teapot.obj");
    cube.load_from_obj(OBJECTS_DIR "cube.obj");
    plane.load_from_obj(OBJECTS_DIR "plane.obj");
    triangle.load_from_obj(OBJECTS_DIR "triangle.obj");

    teapot.drawing_mode = &g_drawing_mode;
    cube.drawing_mode = &g_drawing_mode;
    plane.drawing_mode = &g_drawing_mode;
    triangle.drawing_mode = &g_drawing_mode;

    f32 aspect_ratio;
    i32 width, height;

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    glm::mat4 mvp = glm::mat4(1.0f);

    /* glEnable(GL_CULL_FACE); */
    glEnable(GL_DEPTH_TEST);

    Shader ourShader(SHADERS_DIR "shader.vert", SHADERS_DIR "shader.frag");
    Shader cubeShader(SHADERS_DIR "shader.vert", SHADERS_DIR "shader.frag");

    ourShader.use();
    ourShader.setVec3("color", color);

    cubeShader.use();
    cubeShader.setVec3("color", color);

    ImGuiIO &io = ImGui::GetIO();
    UI menu(window, io, cc);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        float currentFrame = static_cast<float>(glfwGetTime());
        g_deltaTime = currentFrame - g_lastFrame;
        g_lastFrame = currentFrame;

        process_input(window);

        glfwGetWindowSize(window, &width, &height);
        aspect_ratio = (float)(width) / height;

        GL_CALL(glClearColor(cc.x, cc.y, cc.z, cc.w));
        GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
        GL_CALL(glClear(GL_DEPTH_BUFFER_BIT));

        auto m = glm::rotate(model, currentFrame, glm::vec3(1, 1, 1));

        projection = glm::perspective(glm::radians(fpcam.fov), aspect_ratio, 0.1f, 100.0f);
        view = glm::lookAt(fpcam.pos, fpcam.pos + fpcam.front, fpcam.up);
        /* mvp = projection * view * m; */

        ourShader.use();
        ourShader.setMat4("model", m);
        ourShader.setMat4("view", view);
        ourShader.setMat4("projection", projection);
        /* render(teapot, fpcam, ourShader); //, mvp); */
        render(teapot, fpcam, ourShader, m);
        /* cube.render(ourShader); */

        cubeShader.use();
        cubeShader.setMat4("model", glm::translate(glm::scale(glm::mat4(1.0f), glm::vec3(10, 10, 10)), glm::vec3(0, -0.5, 0)));
        cubeShader.setMat4("view", view);
        cubeShader.setMat4("projection", projection);
        render(cube, fpcam, cubeShader, model);

        menu.render();

        glfwSwapBuffers(window);
    }
    glfwTerminate();

    // TODO: clean up

    return 0;
}

void process_input(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS
            || glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    float cameraSpeed = static_cast<float>(5 * g_deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
        cameraSpeed *= 3;
        fpcam.fov = g_defaultFov * 1.05;
    }
    else if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_RELEASE) {
        fpcam.fov = g_defaultFov;
    }

    if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS) {
        g_drawing_mode = GL_POINTS;
    }
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
        g_drawing_mode = GL_LINES;
    }
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
        g_drawing_mode = GL_LINE_LOOP;
    }
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
        g_drawing_mode = GL_LINE_STRIP;
    }
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) {
        g_drawing_mode = GL_TRIANGLES;
    }
    if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS) {
        g_drawing_mode = GL_TRIANGLE_STRIP;
    }
    if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS) {
        g_drawing_mode = GL_TRIANGLE_FAN;
    }
    if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS) {
        g_drawing_mode = GL_QUADS;
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        auto k = -fpcam.front.y / fpcam.up.y;
        // cameraForward always points forward in Front-Up plane || to the ground
        auto cameraForward = glm::normalize(fpcam.front + k * fpcam.up);
        fpcam.pos += cameraSpeed * cameraForward;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        auto k = -fpcam.front.y / fpcam.up.y;
        auto cameraForward = glm::normalize(fpcam.front + k * fpcam.up);
        fpcam.pos -= cameraSpeed * cameraForward;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        fpcam.pos -= glm::normalize(glm::cross(fpcam.front, fpcam.up)) * cameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        fpcam.pos += glm::normalize(glm::cross(fpcam.front, fpcam.up)) * cameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        fpcam.pos += cameraSpeed * fpcam.up;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        fpcam.pos -= cameraSpeed * fpcam.up;
    }
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}

void mouse_callback(GLFWwindow *window, f64 xpos, f64 ypos) {
    ImGui_ImplGlfw_CursorPosCallback(window, xpos, ypos);
    if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED) {
        if (g_firstMouse) {
            g_lastX = xpos;
            g_lastY = ypos;
            g_firstMouse = false;
        }

        float xoffset = xpos - g_lastX;
        float yoffset = g_lastY - ypos;
        g_lastX = xpos;
        g_lastY = ypos;

        float sensitivity = 0.1f;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        fpcam.yaw   += xoffset;
        fpcam.pitch += yoffset;

        if (fpcam.pitch > 89.0f) fpcam.pitch = 89.0f;
        if (fpcam.pitch < -89.0f) fpcam.pitch = -89.0f;

        glm::vec3 direction;
        direction.x = cos(glm::radians(fpcam.yaw)) * cos(glm::radians(fpcam.pitch));
        direction.y = sin(glm::radians(fpcam.pitch));
        direction.z = sin(glm::radians(fpcam.yaw)) * cos(glm::radians(fpcam.pitch));
        fpcam.front = glm::normalize(direction);

        /* glfwSetCursorPos(window, 960, 540); */
    }
}
