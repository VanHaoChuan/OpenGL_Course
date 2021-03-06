#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Shader.h"
#include <vector>
#include "LightSpot.h"
#include "LightPoint.h"

#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"
#include "Camera.h"
#include "Material.h"
#include "LightPoint.h"

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
//float vertices[] = {
//        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
//        0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
//        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
//        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
//        -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
//        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
//
//        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
//        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
//        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
//        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
//        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
//        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
//
//        -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
//        -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
//        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
//        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
//        -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
//        -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
//
//        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
//        0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
//        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
//        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
//        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
//        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
//
//        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
//        0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
//        0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
//        0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
//        -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
//        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
//
//        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
//        0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
//        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
//        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
//        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
//        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f
//};
float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

        -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,

        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
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
Camera *camera = new Camera(glm::vec3(0, 0, 0), glm::radians(15.0f), glm::radians(180.0f), glm::vec3(0, 1, 0));

//Camera *camera = new Camera(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));;
LightSpot lightPoint = LightSpot(glm::vec3(0, 10.0f, 0),
                                 glm::vec3(glm::radians(5.0f), glm::radians(90.0f), 0),
                                 glm::vec3(1.0f, 1.0f, 1.0f));

void WindowBufferSizeChange(GLFWwindow *, int, int);

void ProcessInput(GLFWwindow *);

void LoadImage(const char *, GLenum, GLenum, GLenum);

void ProcessMouse(GLFWwindow *, double, double);

int main() {

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 16);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
    if (window == nullptr) {
        std::cout << "Create window failed." << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
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
    glEnable(GL_MULTISAMPLE);
    Shader *shader = new Shader("vertex.glsl", "fragment.glsl");
    shader->UseProgram();


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

    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) 0);
    //glEnableVertexAttribArray(1);
    //glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
    //glEnableVertexAttribArray(0);
    //glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) (3 * sizeof(float)));
    //glEnableVertexAttribArray(2);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));
    glEnableVertexAttribArray(3);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);





    //LoadImage("wall.jpg", GL_TEXTURE0, GL_RGB, GL_RGB);
    //LoadImage("awesomeface.png", GL_TEXTURE3, GL_RGBA, GL_RGBA);
    glUniform3f(glGetUniformLocation(shader->shaderProgram, "objColor"), 0.5f, 0.5f, 0.5f);
    glUniform3f(glGetUniformLocation(shader->shaderProgram, "ambientColor"), 0.5f, 0.5f, 0.5f);
    glUniform3f(glGetUniformLocation(shader->shaderProgram, "lightPos"), lightPoint.position.x,
                lightPoint.position.y,
                lightPoint.position.z);
    glUniform3f(glGetUniformLocation(shader->shaderProgram, "lightColor"), lightPoint.color.x,
                lightPoint.color.y, lightPoint.color.z);


    Material *material = new Material(shader, glm::vec3(0.5f, 0.5f, 0.1f), glm::vec3(0.6f, 0.6f, 0.6f),
                                      glm::vec3(1, 1, 1),
                                      256.0f);
    LoadImage("container.png", GL_TEXTURE0, GL_RGBA, GL_RGBA);
    LoadImage("container_specular.png", GL_TEXTURE1, GL_RGBA, GL_RGBA);
    shader->SendUniform1v("material.ambient", material->ambient);
    shader->SendUniform1i("material.diffuse", 0);
    shader->SendUniform1i("material.specular", 1);
    shader->SendUniform1f("material.shininess", material->shininess);
    shader->SendUniform1v("lightDirUniform", lightPoint.direction);
    shader->SendUniform1f("lightSpot.cosPhy",lightPoint.cosPhy);
    //glUniform1f(glGetUniformLocation(shader->shaderProgram, "lightPoint.constant"), lightPoint.constant);
    //glUniform1f(glGetUniformLocation(shader->shaderProgram, "lightPoint.linear"), lightPoint.linear);
    //glUniform1f(glGetUniformLocation(shader->shaderProgram, "lightPoint.quadratic"), lightPoint.quadratic);
    //shader->SendUniform1i("material.texture",0);
    //glUniform1f(glGetUniformLocation(shader->shaderProgram, "material.shininess"), material->shininess);
    //glUniform1i(glGetUniformLocation(shader->shaderProgram, "texture_"), 0);
    //glUniform1i(glGetUniformLocation(shader->shaderProgram, "textureFace"), 3);
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0, 0.5f, 0.7f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUniform3f(glGetUniformLocation(shader->shaderProgram, "cameraPos"), camera->position.x, camera->position.y,
                    camera->position.z);
        //glm::mat4 model = glm::mat4(1.0f);
        //model = glm::rotate(model,(float)glfwGetTime()*glm::radians(-55.0f),glm::vec3(1,0,0));
        glm::mat4 view = glm::mat4(1.0f);
        view = camera->GetViewMatrix();
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), (float) (WINDOW_WIDTH / WINDOW_HEIGHT), 0.1f, 100.0f);

        shader->SendUniformMat4("view", view);
        shader->SendUniformMat4("projection", projection);
        for (const auto &cubePosition : cubePositions) {
            glm::mat4 model = glm::mat4(1);
            model = glm::translate(model, cubePosition);
            model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.5f, 0.3f, 0.5f));
            //model = glm::scale(model, glm::vec3(2, 2, 1));
            shader->SendUniformMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }


        //glm::mat4 trans;
        //trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0));
        //trans = glm::scale(trans, glm::vec3(1.5, 1.5, 1.5));
        //shader->UseProgram();
        //glUniformMatrix4fv(glGetUniformLocation(shader->shaderProgram,"transform"),1,GL_FALSE,glm::value_ptr(trans));

        //glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
        //glDrawArrays(GL_TRIANGLES,0,36);
        glfwSwapBuffers(window);
        ProcessInput(window);
        glfwPollEvents();
        camera->UpdateCameraPosition();
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


    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->speedZ = 0.01f;
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->speedZ = -0.01f;
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->speedX = 0.01f;
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->speedX = -0.01f;
    else {
        camera->speedZ = 0;
        camera->speedX = 0;
    }
}

void LoadImage(const char *fileName, GLenum textureChannel, GLenum localFormat, GLenum targetFormat) {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
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
