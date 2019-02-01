#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define GLEW_STATIC
#define WINDOW_TITLE "OpenGL Core"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
float vertices[] = {
//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
};
unsigned int indices[] = { // 注意索引从0开始!
        0, 1, 3, // 第一个三角形
        1, 2, 3  // 第二个三角形
};
void WindowBufferSizeChange(GLFWwindow * , int, int);
void ProcessInput(GLFWwindow *);
int main()
{

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH,WINDOW_HEIGHT,WINDOW_TITLE,NULL,NULL);
    if (window == nullptr)
    {
        std::cout<<"Create window failed."<<std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glViewport(0,0,WINDOW_WIDTH,WINDOW_HEIGHT);
    glewExperimental = true;
    if (glewInit() != GLEW_OK)
    {
        std::cout<<"Init GLEW failed."<<std::endl;
        glfwTerminate();
        return -1;
    }
    glfwSetFramebufferSizeCallback(window,WindowBufferSizeChange);

    unsigned int VAO,VBO,EBO;
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&EBO);

    glGenVertexArrays(1,&VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindVertexArray(VAO);
    glVertexAttribPointer(4,3,GL_FLOAT,GL_FALSE,8 * sizeof(float),(void*)0);
    glEnableVertexAttribArray(4);//Vertex

    glVertexAttribPointer(2,3,GL_FLOAT,GL_FALSE,8 * sizeof(float),(void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);//Color

    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,8 * sizeof(float),(void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(0);//UV

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices),indices,GL_STATIC_DRAW);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    int width,height,channel;
    unsigned char * data = stbi_load("wall.jpg",&width,&height,&channel,0);
    unsigned int texture1,texture2;
    glGenTextures(1,&texture1);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,texture1);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    data = stbi_load("awesomeface.png",&width,&height,&channel,0);
    glGenTextures(1,&texture2);
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D,texture2);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    Shader * shader = new Shader("vertex.glsl","fragment.glsl");
    shader->UseProgram();


    while (!glfwWindowShouldClose(window))
    {

        glClearColor(0,0.5f,0,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model,(float)glfwGetTime()*glm::radians(-55.0f),glm::vec3(1,0,0));
        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view,glm::vec3(0,0,-3));
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), (float)(WINDOW_WIDTH / WINDOW_HEIGHT), 0.1f, 100.0f);

        //glm::mat4 trans;
        //trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0));
        //trans = glm::scale(trans, glm::vec3(1.5, 1.5, 1.5));
        //shader->UseProgram();
        //glUniformMatrix4fv(glGetUniformLocation(shader->shaderProgram,"transform"),1,GL_FALSE,glm::value_ptr(trans));
        shader->SendUniformMat4(model,"model");
        shader->SendUniformMat4(view,"view");
        shader->SendUniformMat4(projection,"projection");
        glUniform1i(glGetUniformLocation(shader->shaderProgram,"texture_"),0);
        glUniform1i(glGetUniformLocation(shader->shaderProgram,"textureFace"),3);
        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
        glfwSwapBuffers(window);
        ProcessInput(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
void WindowBufferSizeChange(GLFWwindow * window, int _width, int _height)
{
    glViewport(0,0,_width,_height);
}
void ProcessInput(GLFWwindow * window)
{
    if (glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window,true);
}
