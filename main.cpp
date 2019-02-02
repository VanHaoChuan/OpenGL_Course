#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Shader.h"

#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"
#include "Camera.h"

#define GLEW_STATIC
#define WINDOW_TITLE "OpenGL Core"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
//float vertices[] = {
////     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
//        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
//        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
//        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
//        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
//};
unsigned int indices[] = { // 注意索引从0开始!
        0, 1, 3, // 第一个三角形
        1, 2, 3  // 第二个三角形
};
float vertices[] = {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f
};
glm::vec3 cubePositions[] = {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f, 2.0f, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),
        glm::vec3(-1.3f, 1.0f, -1.5f)
};
double lastX, lastY;
bool firstMouse = true;
Camera *camera = new Camera(glm::vec3(0, 0, 3), glm::radians(15.0f), glm::radians(180.0f), glm::vec3(0, 1, 0));


void WindowBufferSizeChange(GLFWwindow *, int, int);

void ProcessInput(GLFWwindow *);

void LoadImage(const char *, GLenum, GLenum, GLenum);

void ProcessMouse(GLFWwindow *, double, double);

int main() {

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
    if (window == nullptr) {
        std::cout << "Create window failed." << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    glewExperimental = static_cast<GLboolean>(true);
    if (glewInit() != GLEW_OK) {
        std::cout << "Init GLEW failed." << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwSetFramebufferSizeCallback(window, WindowBufferSizeChange);
    glfwSetCursorPosCallback(window, ProcessMouse);
    glEnable(GL_DEPTH_TEST);

    Shader *shader = new Shader("vertex.glsl", "fragment.glsl");
    shader->UseProgram();
    //Camera camera(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));;


    unsigned int VAO, VBO, EBO;
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glGenVertexArrays(1, &VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindVertexArray(VAO);
    //glVertexAttribPointer(4,3,GL_FLOAT,GL_FALSE,8 * sizeof(float),(void*)0);
    //glEnableVertexAttribArray(4);//Vertex

    //glVertexAttribPointer(2,3,GL_FLOAT,GL_FALSE,8 * sizeof(float),(void*)(3 * sizeof(float)));
    //glEnableVertexAttribArray(2);//Color

    //glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,8 * sizeof(float),(void*)(6 * sizeof(float)));
    //glEnableVertexAttribArray(0);//UV

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    LoadImage("wall.jpg", GL_TEXTURE0, GL_RGB, GL_RGB);
    LoadImage("awesomeface.png", GL_TEXTURE3, GL_RGBA, GL_RGBA);
    while (!glfwWindowShouldClose(window)) {

        glClearColor(0, 0.5f, 0, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //glm::mat4 model = glm::mat4(1.0f);
        //model = glm::rotate(model,(float)glfwGetTime()*glm::radians(-55.0f),glm::vec3(1,0,0));
        glm::mat4 view = glm::mat4(1.0f);
        view = camera->GetViewMatrix();
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), (float) (WINDOW_WIDTH / WINDOW_HEIGHT), 0.1f, 100.0f);

        shader->SendUniformMat4(view, "view");
        shader->SendUniformMat4(projection, "projection");
        for (const auto &cubePosition : cubePositions) {
            glm::mat4 model = glm::mat4(1);
            model = glm::translate(model, cubePosition);
            model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.5f, 0.3f, 0.5f));
            shader->SendUniformMat4(model, "model");
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }


        //glm::mat4 trans;
        //trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0));
        //trans = glm::scale(trans, glm::vec3(1.5, 1.5, 1.5));
        //shader->UseProgram();
        //glUniformMatrix4fv(glGetUniformLocation(shader->shaderProgram,"transform"),1,GL_FALSE,glm::value_ptr(trans));

        glUniform1i(glGetUniformLocation(shader->shaderProgram, "texture_"), 0);
        glUniform1i(glGetUniformLocation(shader->shaderProgram, "textureFace"), 3);
        //glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
        //glDrawArrays(GL_TRIANGLES,0,36);
        glfwSwapBuffers(window);
        ProcessInput(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

void WindowBufferSizeChange(GLFWwindow *window, int _width, int _height) {
    glViewport(0, 0, _width, _height);
}

void ProcessInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void LoadImage(const char *fileName, GLenum textureChannel, GLenum localFormat, GLenum targetFormat) {
    int width, height, channel;
    unsigned char *data = stbi_load(fileName, &width, &height, &channel, 0);
    if (data != nullptr) {
        unsigned int texture;
        glGenTextures(1, &texture);
        glActiveTexture(textureChannel);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, localFormat, width, height, 0, targetFormat, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    } else {
        std::cout << "Texture loaded failed." << std::endl;
    }
}

void ProcessMouse(GLFWwindow *window, double xPos, double yPos) {

    double deltaX, deltaY;
    if (firstMouse) {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }
    deltaX = xPos - lastX;
    deltaY = yPos - lastY;
    lastX = xPos;
    lastY = yPos;
    camera->ProcessMouseMovement(static_cast<float>(deltaX), static_cast<float>(deltaY));
}
