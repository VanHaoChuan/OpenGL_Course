//
// Created by Young Fan on 2019-01-28.
//

#include "Shader.h"



Shader::Shader(const char* vertexPath, const char* fragmentPath) {
    std::ifstream vertexFile;
    std::ifstream fragmentFile;
    vertexFile.open(vertexPath);
    fragmentFile.open(fragmentPath);
    std::stringstream vertexSString;
    std::stringstream fragmentSString;
    unsigned int vertexShader,fragmentShader;
    char errorLog[512];
    vertexFile.exceptions(std::ifstream::failbit||std::ifstream::badbit);
    fragmentFile.exceptions(std::ifstream::failbit||std::ifstream::badbit);
    try
    {
        if (!vertexFile.is_open() || !fragmentFile.is_open())
        {
            throw std::exception();
        }
        vertexSString << vertexFile.rdbuf();
        fragmentSString << fragmentFile.rdbuf();
        vertexString = vertexSString.str();
        fragmentString = fragmentSString.str();
        vertexSource = vertexString.c_str();
        fragmentSource = fragmentString.c_str();
    }
    catch (std::exception exception_e)
    {
        std::cout<< exception_e.what() <<std::endl;
    }

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1,&vertexSource,NULL);
    glCompileShader(vertexShader);

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader,1,&fragmentSource,NULL);
    glCompileShader(fragmentShader);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragmentShader);
    glLinkProgram(shaderProgram);
    CheckShaderError(shaderProgram,"program",errorLog);
    CheckShaderError(vertexShader,"vertex",errorLog);
    CheckShaderError(fragmentShader,"fragment",errorLog);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


}

void Shader::UseProgram() {
    glUseProgram(shaderProgram);
}

void Shader::CheckShaderError(unsigned int shaderID, char *kind,char* result) {
    if (kind != "program")
    {
        glGetShaderInfoLog(shaderID,512,NULL,result);
        std::cout<<result<<std::endl;
    } else
    {
        glGetProgramInfoLog(shaderID,512,NULL,result);
        std::cout<<result<<std::endl;

    }
}