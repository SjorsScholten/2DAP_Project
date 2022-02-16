#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <ResourceManager.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <SpriteRenderer.hpp>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void processInput(GLFWwindow *window);

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGl", nullptr, nullptr);
    if (window == nullptr) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    SpriteRenderer *renderer;
    {
        ResourceManager::LoadShader("../../../shaders/vertexShader.glsl", "../../../shaders/fragmentShader.glsl",
                                    nullptr, "sprite");
        auto projection = glm::ortho(0.0f, static_cast<float>(800.0f), static_cast<float>(600.0f), 0.0f, -1.0f, 1.0f);
        ResourceManager::GetShader("sprite").Use().SetInteger("Image", 0);
        ResourceManager::GetShader("sprite").Use().SetMatrix4("projection", projection);
        Shader s = ResourceManager::GetShader("sprite");
        renderer = new SpriteRenderer(s);

        ResourceManager::LoadTexture("../../../resources/images/Debug.PNG", true, "debug");
    }

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        auto t = ResourceManager::GetTexture("debug");
        renderer->DrawSprite(t, glm::vec2{200.0f, 200.0f}, glm::vec2(300.0f, 400.0f), 0.0f,
                             glm::vec3(1.0f, 1.0f, 1.0f));

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}