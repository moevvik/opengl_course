#include <glwrapper.h>
#include "glfw3.h"
#include <thread>
#include <iostream>
#include <c++/cmath>
#include "ShadersLoader.h"

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    auto window = glfwCreateWindow(1280, 720, "OpenGL", NULL, NULL);

    if (window == NULL) {
        std::cerr << "Can not create glfw window! \n";
        glfwTerminate();
        return -1;
    }

    int width;
    int height;
    glfwGetFramebufferSize(window, &width, &height);
    glfwMakeContextCurrent(window);

#ifndef __APPLE__
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Error initializing glew. Exiting.\n";
        return -1;
    }
#endif

    auto vertexSource = shaders::loadShaderSourceFromFile("resources/shaders/vertex.glsl").c_str();
    auto vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);
    GLint success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar info[512];
        glGetShaderInfoLog(vertexShader, sizeof(info), NULL, info);
        std::cerr << "ERROR::SHADER LINK_FAILED\n" << info;
        return 0;
    }

    auto fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    auto fragmentShaderSourCe = shaders::loadShaderSourceFromFile("resources/shaders/fragment.glsl");
    const char *fragmentShaderSourceNative = fragmentShaderSourCe.c_str();
    glShaderSource(fragmentShader, 1, &fragmentShaderSourceNative, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar info[512];
        glGetShaderInfoLog(fragmentShader, sizeof(info), NULL, info);
        std::cerr << "Error initializing fragmentShader.\n%s\"", info;
        return 0;
    }

    auto shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        GLchar info[512];
        glGetProgramInfoLog(shaderProgram, sizeof(info), NULL, info);
        std::cerr << "Error initializing shaderProgram.\n%s\"", info;
        std::cerr << vertexSource << std::endl;
        std::cerr << fragmentShaderSourCe << std::endl;

        glDeleteProgram(shaderProgram);
        glfwTerminate();
        return 0;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    GLfloat colorHead[] = {
            1.0f, 1.0f, 0.0f
    };
    GLfloat colorHands[] = {
            0.6f, 0.8f, 0.4f
    };
    GLfloat colorBody[] = {
            0.6f, 0.3f, 0.3f
    };
    GLfloat colorPents[] = {
            0.1f, 0.3f, 0.3f
    };
    GLfloat colorShoes[] = {
            0.0f, 0.0f, 0.0f
    };
    
    GLfloat coordinates[] = {
            -0.1f, 0.5f, colorHands[0], colorHands[1], colorHands[2],
            -0.1f, 0.45f, colorHands[0], colorHands[1], colorHands[2],
            -0.3f, -0.1f, colorHands[0], colorHands[1], colorHands[2],
            -0.28f, -0.1f, colorHands[0], colorHands[1], colorHands[2],
            0.1f, 0.5f, colorHands[0], colorHands[1], colorHands[2],
            0.1f, 0.45f, colorHands[0], colorHands[1], colorHands[2],
            0.3f, -0.1f, colorHands[0], colorHands[1], colorHands[2],
            0.28f, -0.1f, colorHands[0], colorHands[1], colorHands[2],

            -0.1f, 0.5f, colorBody[0], colorBody[1], colorBody[2],
            -0.1f, -0.1f, colorBody[0], colorBody[1], colorBody[2],
            0.1f, 0.5f, colorBody[0], colorBody[1], colorBody[2],
            0.1f, -0.1f, colorBody[0], colorBody[1], colorBody[2],

            -0.07f, -0.6f, colorShoes[0], colorShoes[1], colorShoes[2],
            -0.07f, -0.72f, colorShoes[0], colorShoes[1], colorShoes[2],
            -0.2f, -0.72f, colorShoes[0], colorShoes[1], colorShoes[2],
            0.07f, -0.6f, colorShoes[0], colorShoes[1], colorShoes[2],
            0.07f, -0.72f, colorShoes[0], colorShoes[1], colorShoes[2],
            0.2f, -0.72f, colorShoes[0], colorShoes[1], colorShoes[2],

            -0.1f, -0.1f, colorPents[0], colorPents[1], colorPents[2],
            -0.12f, -0.65f, colorPents[0], colorPents[1], colorPents[2],
            -0.05f, -0.1f, colorPents[0], colorPents[1], colorPents[2],
            -0.07f, -0.65f, colorPents[0], colorPents[1], colorPents[2],
            0.1f, -0.1f, colorPents[0], colorPents[1], colorPents[2],
            0.12f, -0.65f, colorPents[0], colorPents[1], colorPents[2],
            0.05f, -0.1f, colorPents[0], colorPents[1], colorPents[2],
            0.07f, -0.65f, colorPents[0], colorPents[1], colorPents[2],

            0.0f, 0.5f, colorHead[0], colorHead[1], colorHead[2],
            -0.07f, 0.65f, colorHead[0], colorHead[1], colorHead[2],
            0.0f, 0.75f, colorHead[0], colorHead[1], colorHead[2],
            0.07f, 0.65f, colorHead[0], colorHead[1], colorHead[2],

    };
    GLuint indexes[] = {
            0, 1, 2,  1, 2, 3,  4, 5, 6,  5, 6, 7,
            8, 9, 10,  9, 10, 11,
            12, 13, 14,  15, 16, 17,
            18, 19, 20,  19, 20, 21,
            22, 23, 24,  23, 24, 25,
            26, 27, 28,  26, 28, 29
    };

    GLuint vbo;
    GLuint ebo;
    GLuint vao;

    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(coordinates), coordinates, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, (void *) (2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_STATIC_DRAW);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glViewport(0, 0, width, height);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClearColor(0.4f, 0.4f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, sizeof(coordinates), GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        std::this_thread::sleep_for(std::chrono::nanoseconds(15000));
    }

    glfwTerminate();
    return 0;
}