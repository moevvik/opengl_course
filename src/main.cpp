#include <glwrapper.h>
#include "glfw3.h"
#include <thread>
#include <iostream>
#include <c++/cmath>
#include <stb_image.h>
#include "ShadersLoader.h"

GLuint getTexture(char const *filename);

GLuint getProgram(char const *vertexFilePath, char const *fragmentFilePath) ;

GLuint getVaoTexture(const void *coordinates, GLsizeiptr sizeCoordinates,
                     const void *indexes, GLsizeiptr sizeIndexes) ;

GLuint getVaoColor(const void *coordinates, GLsizeiptr sizeCoordinates,
                     const void *indexes, GLsizeiptr sizeIndexes) ;

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

    auto humanProgram = getProgram("resources/shaders/vertex.glsl", "resources/shaders/fragment.glsl");
    auto circleProgram = getProgram("resources/shaders/vertex_circle.glsl", "resources/shaders/fragment_circle.glsl");
    auto textureProgram = getProgram("resources/shaders/vertexTexture.glsl", "resources/shaders/fragmentTexture.glsl");

    GLfloat coordinatesNature[] = {
            -1.0f, -1.0f, 0.0f, 0.0f,
            -1.0f, 1.0f,  0.0f, 1.0f,
            1.0f, 1.0f,   1.0f, 1.0f,
            1.0f, -1.0f,  1.0f, 0.0f,
    };
    GLuint texturesNature[] = {
            0, 1, 2, 2, 3, 0
    };
    GLuint vaoNature = getVaoTexture(coordinatesNature, sizeof(coordinatesNature), texturesNature, sizeof(texturesNature));

    GLfloat colorHands[] = {
            0.6f, 0.8f, 0.4f
    };
    GLfloat colorShoes[] = {
            0.0f, 0.0f, 0.0f
    };

    GLfloat coordinatesHuman[] = {
            -0.1f, 0.5f, colorHands[0], colorHands[1], colorHands[2],
            -0.1f, 0.45f, colorHands[0], colorHands[1], colorHands[2],
            -0.3f, -0.1f, colorHands[0], colorHands[1], colorHands[2],
            -0.28f, -0.1f, colorHands[0], colorHands[1], colorHands[2],
            0.1f, 0.5f, colorHands[0], colorHands[1], colorHands[2],
            0.1f, 0.45f, colorHands[0], colorHands[1], colorHands[2],
            0.3f, -0.1f, colorHands[0], colorHands[1], colorHands[2],
            0.28f, -0.1f, colorHands[0], colorHands[1], colorHands[2],  //7
//
            -0.07f, -0.6f, colorShoes[0], colorShoes[1], colorShoes[2],
            -0.07f, -0.72f, colorShoes[0], colorShoes[1], colorShoes[2],
            -0.2f, -0.72f, colorShoes[0], colorShoes[1], colorShoes[2],
            0.07f, -0.6f, colorShoes[0], colorShoes[1], colorShoes[2],
            0.07f, -0.72f, colorShoes[0], colorShoes[1], colorShoes[2],
            0.2f, -0.72f, colorShoes[0], colorShoes[1], colorShoes[2],  //13
    };
    GLuint indexesHuman[] = {
            0, 1, 2,  1, 2, 3,  4, 5, 6,  5, 6, 7,  //Hands
            8, 9, 10,  11, 12, 13,  //Shoes
    };
    GLuint vaoHuman = getVaoColor(coordinatesHuman, sizeof(coordinatesHuman), indexesHuman, sizeof(indexesHuman));


    GLfloat coordinatesBody[] = {
            -0.1f, 0.5f, 0.0f, 1.0f,
            -0.1f, -0.1f, 0.0f, 0.0f,
            0.1f, 0.5f, 1.0f, 1.0f,
            0.1f, -0.1f, 1.0f, 0.0f,
    };
    GLuint indexesBody[] = {
            0, 1, 2, 1, 2, 3,
    };
    GLuint vaoBody = getVaoTexture(coordinatesBody, sizeof(coordinatesBody), indexesBody, sizeof(indexesBody));

    GLfloat coordinatesPents[] = {
            -0.1f, -0.1f, 1.0f, 0.0f,
            -0.12f, -0.65f, 0.0f, 0.0f,
            -0.05f, -0.1f, 1.0f, 1.0f,
            -0.07f, -0.65f, 0.2f, 0.0f,

            0.1f, -0.1f, 1.0f, 1.0f,
            0.12f, -0.65f, 1.0f, 0.0f,
            0.05f, -0.1f, 0.6f, 1.0f,
            0.07f, -0.65f, 0.8f, 0.0f,
    };
    GLuint indexesPents[] = {
            0, 1, 2, 1, 2, 3,
            4, 5, 6, 5, 6, 7,
    };
    GLuint vaoPents = getVaoTexture(coordinatesPents, sizeof(coordinatesPents), indexesPents, sizeof(indexesPents));


    GLfloat coordinatesHead[] = {
            0.0f, 0.64f, 1.0f, 0.95f, 0.55f
    };

    GLuint indexesHead[] = {
            0
    };
    GLuint vaoHead = getVaoColor(coordinatesHead, sizeof(coordinatesHead), indexesHead, sizeof(indexesHead));


    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    stbi_set_flip_vertically_on_load(true);
    GLuint textureNature = getTexture("resources/nature.jpg");
    GLuint texture = getTexture("resources/kletka2.jpg");  // texture.jpeg
    GLuint texturePents = getTexture("resources/texture.jpeg");

    glViewport(0, 0, width, height);
    glPointSize(150);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClearColor(0.4f, 0.4f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(textureProgram);
        glUniform1i(glGetUniformLocation(textureProgram, "sampler"), 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureNature);
        glBindVertexArray(vaoNature);
        glDrawElements(GL_TRIANGLES, sizeof(coordinatesHead), GL_UNSIGNED_INT, 0);

        glUseProgram(humanProgram);
        glBindVertexArray(vaoHuman);
        glDrawElements(GL_TRIANGLES, sizeof(coordinatesHuman), GL_UNSIGNED_INT, 0);

        glUseProgram(circleProgram);
        glUniform2f(glGetUniformLocation(circleProgram, "uResolution"), width, height);
        glBindVertexArray(vaoHead);
        glDrawElements(GL_POINTS, 1, GL_UNSIGNED_INT, 0);

        glUseProgram(textureProgram);
        glUniform1i(glGetUniformLocation(textureProgram, "sampler"), 0);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(vaoBody);
        glDrawElements(GL_TRIANGLES, sizeof(coordinatesBody), GL_UNSIGNED_INT, 0);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texturePents);
        glBindVertexArray(vaoPents);
        glDrawElements(GL_TRIANGLES, sizeof(coordinatesPents), GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        std::this_thread::sleep_for(std::chrono::nanoseconds(15000));
    }

    glfwTerminate();
    return 0;
}

GLuint getVaoColor(const void *coordinates, GLsizeiptr sizeCoordinates,
                     const void *indexes, GLsizeiptr sizeIndexes) {
    GLuint vbo;
    GLuint ebo;
    GLuint vao;

    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeCoordinates, coordinates, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, (void *) (2 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeIndexes, indexes, GL_STATIC_DRAW);

    return vao;
}

GLuint getVaoTexture(const void *coordinates, GLsizeiptr sizeCoordinates,
                     const void *indexes, GLsizeiptr sizeIndexes) {
    GLuint vbo;
    GLuint ebo;
    GLuint vao;

    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeCoordinates, coordinates, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4, 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4, (void *) (2 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeIndexes, indexes, GL_STATIC_DRAW);

    return vao;
}

GLuint getProgram(char const *vertexFilePath, char const *fragmentFilePath) {
    auto vertexSource = shaders::loadShaderSourceFromFile(vertexFilePath).c_str();
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
    auto fragmentShaderSourCe = shaders::loadShaderSourceFromFile(fragmentFilePath);
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

    GLuint shaderProgram = glCreateProgram();
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

    return shaderProgram;
}

GLuint getTexture(char const *filename) {
    GLuint texturePents;
    glGenTextures(1, &texturePents);
    glBindTexture(GL_TEXTURE_2D, texturePents);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    GLint texturePentsWeight;
    GLint texturePentsHeight;
    GLint texturePentsChannelsCount;
    auto dataPents = stbi_load(filename, &texturePentsWeight, &texturePentsHeight, &texturePentsChannelsCount,
                               STBI_rgb);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texturePentsWeight, texturePentsHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,
                 dataPents);
    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(dataPents);

    return texturePents;
}