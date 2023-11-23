#include <iostream>

#include "glad.h"
#include "gl_call.h"
#include "GLFW/glfw3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ui.h"
#include "type_aliases.h"

#include "globals.h"
bool g_render_by_triangles = false;
bool g_depth_test_enabled = true;
bool g_cull_face_enabled = false;
bool g_draw_menu = true;
bool g_use_depth_shader = false;

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

void render_menu();

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

    Mesh teapot, cube, plane, triangle, isosphere, uvsphere, monkey;
    teapot.load_from_obj(OBJECTS_DIR "utah_teapot.obj");
    cube.load_from_obj(OBJECTS_DIR "cube.obj");
    plane.load_from_obj(OBJECTS_DIR "plane.obj");
    triangle.load_from_obj(OBJECTS_DIR "triangle.obj");
    isosphere.load_from_obj(OBJECTS_DIR "isosphere.obj");
    uvsphere.load_from_obj(OBJECTS_DIR "uv_sphere.obj");
    monkey.load_from_obj(OBJECTS_DIR "monkey.obj");

    teapot.drawing_mode = &g_drawing_mode;
    cube.drawing_mode = &g_drawing_mode;
    plane.drawing_mode = &g_drawing_mode;
    triangle.drawing_mode = &g_drawing_mode;
    isosphere.drawing_mode = &g_drawing_mode;
    uvsphere.drawing_mode = &g_drawing_mode;
    monkey.drawing_mode = &g_drawing_mode;

    f32 aspect_ratio;
    s32 width, height;

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    glm::mat4 mvp = glm::mat4(1.0f);

    /* Shader ourShader(SHADERS_DIR "shader.vert", SHADERS_DIR "shader.frag"); */
    Shader lShader(SHADERS_DIR "basic_lighting.vert", SHADERS_DIR "basic_lighting.frag");
    Shader dShader(SHADERS_DIR "basic_lighting.vert", SHADERS_DIR "depth_buffer.frag");
    Shader ourShader = lShader;

    ourShader.use();

    glm::vec3 lp = glm::vec3(1, 1, 1);
    glm::vec3 lp2 = glm::vec3(-1, -2, 1);
    ourShader.setVec3("lightPos", lp);
    ourShader.setVec3("lightColor", glm::vec3(1, 1, 1));
    ourShader.setVec3("objectColor", glm::vec3(1.0f, 1.0f, 1.0f));

    ImGuiIO &io = ImGui::GetIO();
    UI menu(window, io, cc, [](){ render_menu(); });

    RenderData rd_cube(cube, fpcam, ourShader, g_render_by_triangles);
    RenderData rd_teapot(teapot, fpcam, ourShader, g_render_by_triangles);
    RenderData rd_uvsphere(uvsphere, fpcam, ourShader, g_render_by_triangles);
    RenderData rd_isosphere(isosphere, fpcam, ourShader, g_render_by_triangles);
    RenderData rd_monkey(monkey, fpcam, ourShader, g_render_by_triangles);
    RenderData rd_plane(plane, fpcam, ourShader, g_render_by_triangles);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        if (!g_depth_test_enabled) {
            GL_CALL(glDisable(GL_DEPTH_TEST));
        } else {
            GL_CALL(glEnable(GL_DEPTH_TEST));
        }

        if (!g_cull_face_enabled) {
            GL_CALL(glDisable(GL_CULL_FACE));
        } else {
            GL_CALL(glEnable(GL_CULL_FACE));
        }

        ourShader = g_use_depth_shader ? dShader : lShader;

        float currentFrame = static_cast<float>(glfwGetTime());
        g_deltaTime = currentFrame - g_lastFrame;
        g_lastFrame = currentFrame;

        process_input(window);

        glfwGetWindowSize(window, &width, &height);
        aspect_ratio = (float)(width) / height;

        GL_CALL(glClearColor(cc.x, cc.y, cc.z, cc.w));
        GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
        GL_CALL(glClear(GL_DEPTH_BUFFER_BIT));

        /* auto m = glm::rotate(model, currentFrame, glm::vec3(0, 1, 1)); */
        auto m = glm::rotate(model, 0.0f, glm::vec3(0, 1, 1));

        projection = glm::perspective(glm::radians(fpcam.fov), aspect_ratio, 0.1f, 100.0f);
        view = glm::lookAt(fpcam.pos, fpcam.pos + fpcam.front, fpcam.up);

        // Light cube stuff
        auto rm = glm::rotate(model, currentFrame, glm::vec3(1, 0, 0));
        /* auto mc = glm::translate(model, glm::vec3(1, 1, 1)); */
        auto mc = glm::translate(rm, glm::vec3(3, 1, 1));
        mc = glm::scale(mc, glm::vec3(0.1, 0.1, 0.1));
        /* auto rm = glm::rotate(mc, currentFrame, glm::vec3(1, 0, 0)); */
        auto rlp = glm::vec3(mc * glm::vec4(lp, 1.0f));

        // Cube (not mesh)
        ourShader.use();
        auto mmm = glm::translate(m, glm::vec3(1, 1, -10));
        ourShader.setMat4("model", mmm);
        ourShader.setMat4("view", view);
        ourShader.setMat4("projection", projection);
        ourShader.setVec3("viewPos", fpcam.pos);
        /* ourShader.setVec3("lightPos", lp); */
        ourShader.setVec3("lightPos", rlp);
        rd_cube.matrix = mmm;
        render(rd_cube);

        // Teapot
        Shader s1 = ourShader;
        auto m1 = glm::translate(m, glm::vec3(-1, -1, 1));
        m1 = glm::scale(m1, glm::vec3(0.3, 0.3, 0.3));
        s1.use();
        s1.setMat4("model", m1);
        rd_teapot.matrix = m1;
        render(rd_teapot);

        // Sphere mesh
        Shader s2 = ourShader;
        auto m2 = glm::translate(m, glm::vec3(1, 1, -5));
        s2.use();
        s2.setMat4("model", m2);
        rd_uvsphere.matrix = m2;
        render(rd_uvsphere);

        // Light cube
        Shader sc = ourShader;
        sc.use();
        sc.setMat4("model", mc);
        sc.setVec3("lightPos", rlp);
        sc.setVec3("objectColor", glm::vec3(1.0f, 1.0f, 0.0f));
        rd_cube.matrix = mc;
        render(rd_cube);
        sc.setVec3("objectColor", glm::vec3(1.0f, 1.0f, 1.0f));

        // Light cube 2
        sc.use();
        sc.setMat4("model", mc);
        sc.setVec3("lightPos", lp2);
        sc.setVec3("objectColor", glm::vec3(0.0f, 1.0f, 1.0f));
        sc.setVec3("lightColor", glm::vec3(0, 1, 0));
        rd_cube.matrix = mc;
        render(rd_cube);
        sc.setVec3("objectColor", glm::vec3(0.0f, 1.0f, 1.0f));
        sc.setVec3("lightColor", glm::vec3(1, 1, 1));

        if (g_draw_menu) menu.render();

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

    static bool g_z_pressed = false;
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
        if (!g_z_pressed) {
            /* if (!g_depth_test_enabled) { */
            /*     glDisable(GL_DEPTH_TEST); */
            /* } else { */
            /*     glEnable(GL_DEPTH_TEST); */
            /* } */
            g_depth_test_enabled = !g_depth_test_enabled;
        }
        g_z_pressed = true;
    }
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_RELEASE) {
        g_z_pressed = false;
    }

    static bool g_c_pressed = false;
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
        if (!g_c_pressed) {
            /* if (!g_cull_face_enabled) { */
            /*     glDisable(GL_CULL_FACE); */
            /* } else { */
            /*     glEnable(GL_CULL_FACE); */
            /* } */
            g_cull_face_enabled = !g_cull_face_enabled;
        }
        g_c_pressed = true;
    }
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_RELEASE) {
        g_c_pressed = false;
    }

    static bool g_r_pressed = false;
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        if (!g_r_pressed) {
            g_render_by_triangles = !g_render_by_triangles;
        }
        g_r_pressed = true;
    }
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_RELEASE) {
        g_r_pressed = false;
    }

    static bool g_g_pressed = false;
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
        if (!g_g_pressed) {
            g_use_depth_shader = !g_use_depth_shader;
        }
        g_g_pressed = true;
    }
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_RELEASE) {
        g_g_pressed = false;
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

void render_menu() {
    static bool *gs[] = {
        &g_render_by_triangles,
        &g_depth_test_enabled,
        &g_cull_face_enabled,
        &g_use_depth_shader
    };

    ImGui::ShowDemoWindow();

    ImGui::SeparatorText("Управление");
    ImGui::Text("Выбор режима отрисовки: 0 - 7");
    ImGui::Text("Движение: W, A, S, D");
    ImGui::Text("Вверх/Вниз: Space/L-Shift");
    ImGui::Text("Ускорение: L-Ctrl");
    ImGui::Text("ЛКМ: Управление курсором");
    ImGui::Text("ПКМ: Управление камерой");
    ImGui::Text("Выход: Q, Esc");

    ImGui::SeparatorText("Настройки");
    if (ImGui::BeginTable("split", 1))
    {
        ImGui::TableNextColumn(); ImGui::Checkbox("(R) Отрисовка по треугольникам", gs[0]);
        ImGui::TableNextColumn(); ImGui::Checkbox("(G) Шейдер глубины", gs[3]);
        ImGui::TableNextColumn(); ImGui::Checkbox("(Z) Тест глубины", gs[1]);
        ImGui::TableNextColumn(); ImGui::Checkbox("(C) Отброс нелицевых граней", gs[2]);
        ImGui::EndTable();
    }
}
