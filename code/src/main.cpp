#include <iostream>

#include "glad.h"
#include "GLFW/glfw3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "type_aliases.h"

#define __MAIN__
#include "main_globals.h"

void process_input(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, f64 xpos, f64 ypos);

struct Mesh {
    std::vector<glm::fvec3> vertices;
    std::vector<glm::ivec3> indices;
};

face_t get_face(const Mesh& mesh, u32 index) {
    auto f = mesh.indices[index];

    auto v1 = mesh.vertices[f.x];
    auto v2 = mesh.vertices[f.y];
    auto v3 = mesh.vertices[f.z];

    face_t face;

    face.x = v1;
    face.y = v2;
    face.z = v3;

    return face;
}

void print_face(const face_t& face) {
    std::cout << "v1: " << face.x.x << ' ' << face.x.y << ' ' << face.x.z << std::endl;
    std::cout << "v2: " << face.y.x << ' ' << face.y.y << ' ' << face.y.z << std::endl;
    std::cout << "v3: " << face.z.x << ' ' << face.z.y << ' ' << face.z.z << std::endl;
}

i32 load_mesh_from_obj(Mesh& out_mesh, std::string obj_filename) {
    std::fstream file(obj_filename);

    if (!file.is_open()) { return -1; }

    std::string line;
    std::string prefix;

    f32 x, y, z;
    u32 a, b, c;

    while (std::getline(file, line)) {
        std::istringstream iss(line);

        iss >> prefix;

        if (prefix == "v") {
            if (iss >> x >> y >> z) {
                out_mesh.vertices.push_back(glm::vec3(x, y, z));
            }
        } else if (prefix == "f") {
            if (iss >> a >> b >> c) {
                // Start indexing from 0, not from 1.
                out_mesh.indices.push_back(glm::vec3(a - 1, b - 1, c - 1));
            }
        }
    }

    file.close();

    return 0;
}

void render_mesh(const Mesh& mesh, const glm::mat4& mvp) {
    for (u32 i = 0; i < mesh.indices.size(); i++) {
        auto f = get_face(mesh, i);
        auto v1 = mvp * glm::vec4(f.x, 1.0f);
        auto v2 = mvp * glm::vec4(f.y, 1.0f);
        auto v3 = mvp * glm::vec4(f.z, 1.0f);

        /* if (v1.w != 0.0f) */ v1.x = v1.x / v1.w;
        /* if (v2.w != 0.0f) */ v2.x = v2.x / v2.w;
        /* if (v3.w != 0.0f) */ v3.x = v3.x / v3.w;
        /* if (v1.w != 0.0f) */ v1.y = v1.y / v1.w;
        /* if (v2.w != 0.0f) */ v2.y = v2.y / v2.w;
        /* if (v3.w != 0.0f) */ v3.y = v3.y / v3.w;
        /* if (v1.w != 0.0f) */ v1.z = v1.z / v1.w;
        /* if (v2.w != 0.0f) */ v2.z = v2.z / v2.w;
        /* if (v3.w != 0.0f) */ v3.z = v3.z / v3.w;

        glVertex3f(v1.x, v1.y, v1.z);
        glVertex3f(v2.x, v2.y, v2.z);
        glVertex3f(v3.x, v3.y, v3.z);
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {
    glfwInit();
    /* GLFWwindow* window = glfwCreateWindow(800, 600, "Window", NULL, NULL); */
    GLFWwindow* window = glfwCreateWindow(1200, 900, "Window", NULL, NULL);

    glfwMakeContextCurrent(window);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);

    glm::vec4 clear_color = glm::vec4(0.3f, 0.3f, 0.3f, 1.0f);
    auto cc = clear_color;

    Mesh teapot, cube, plane;
    load_mesh_from_obj(teapot, "../../assets/objects/utah_teapot.obj");
    load_mesh_from_obj(cube, "../../assets/objects/cube.obj");
    load_mesh_from_obj(plane, "../../assets/objects/plane.obj");

    /* for (u32 i = 0; i < mesh.indices.size(); i++) { */
        /* auto face = get_face(mesh, i); */
        /* print_face(face); */
        /* std::cout << std::endl; */
    /* } */

    f32 aspect_ratio;
    i32 width, height;

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    glm::mat4 mvp = glm::mat4(1.0f);

    /* glEnable(GL_CULL_FACE); */

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        process_input(window);

        glfwGetWindowSize(window, &width, &height);
        aspect_ratio = (float)(width) / height;

        glClearColor(cc.x, cc.y, cc.z, cc.w);
        glClear(GL_COLOR_BUFFER_BIT);

        projection = glm::perspective(glm::radians(fov), aspect_ratio, 0.1f, 100.0f);
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

        mvp = projection * view * model;

        glBegin(GL_TRIANGLES);
        glColor4f(1.0f, 0.5f, 0.3f, 0.5f);

        render_mesh(teapot, mvp);
        /* mvp = glm::scale(mvp, glm::vec3{20, 20, 20}); */
        /* render_mesh(plane, mvp); */

        /* mvp = glm::translate(mvp, glm::vec3(3 * sin(glfwGetTime()), 3 * sin(glfwGetTime()), 3 * sin(glfwGetTime()))); */
        /* render_mesh(cube, mvp); */

        glEnd();

        glfwSwapBuffers(window);
    }
    glfwTerminate();

    return 0;
}

void process_input(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    float cameraSpeed = static_cast<float>(5 * deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
        cameraSpeed *= 2;
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        cameraPos += cameraSpeed * cameraFront;
        cameraPos.y -= cameraSpeed * cameraFront.y;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        cameraPos -= cameraSpeed * cameraFront;
        cameraPos.y += cameraSpeed * cameraFront.y;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        cameraPos += cameraSpeed * cameraUp;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        cameraPos -= cameraSpeed * cameraUp;
    }
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}

void mouse_callback(GLFWwindow* window, f64 xpos, f64 ypos) {
    if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED) {
        if (firstMouse) {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos;
        lastX = xpos;
        lastY = ypos;

        float sensitivity = 0.1f;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw   += xoffset;
        pitch += yoffset;

        if (pitch > 89.0f) pitch = 89.0f;
        if (pitch < -89.0f) pitch = -89.0f;

        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        cameraFront = glm::normalize(direction);

        /* glfwSetCursorPos(window, 960, 540); */
    }
}
