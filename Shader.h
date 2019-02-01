//
// Created by Young Fan on 2019-01-28.
//

#ifndef OPENGL_COURSE_SHADER_H
#define OPENGL_COURSE_SHADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
class Shader {
public:
    Shader(const char *vertexPath, const char *fragmentPath);
    void UseProgram();
    std::string vertexString;
    std::string fragmentString;
    const char* fragmentSource;
    const char* vertexSource;
    unsigned int shaderProgram;
private:
    void CheckShaderError(unsigned int shaderID,char* kind,char* result);
};


#endif //OPENGL_COURSE_SHADER_H
