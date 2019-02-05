//
// Created by Young Fan on 2019-01-28.
//

#include "Shader.h"

Shader::Shader(const char *vertexPath, const char *fragmentPath) {
    std::ifstream vertexFile;
    std::ifstream fragmentFile;
    vertexFile.open(vertexPath);
    fragmentFile.open(fragmentPath);
    std::stringstream vertexSString;
    std::stringstream fragmentSString;
    unsigned int vertexShader, fragmentShader;
    char errorLog[512];
    vertexFile.exceptions(std::ifstream::badbit || std::ifstream::failbit);
    fragmentFile.exceptions(std::ifstream::badbit || std::ifstream::failbit);
    try {
        if (!vertexFile.is_open() || !fragmentFile.is_open()) {
            throw std::exception();
        }
        vertexSString << vertexFile.rdbuf();
        fragmentSString << fragmentFile.rdbuf();
        vertexString = vertexSString.str();
        fragmentString = fragmentSString.str();
        vertexSource = vertexString.c_str();
        fragmentSource = fragmentString.c_str();
    }
    catch (std::exception exception_e) {
        std::cout << exception_e.what() << std::endl;
    }

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, nullptr);
    glCompileShader(vertexShader);

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
    glCompileShader(fragmentShader);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    CheckShaderError(shaderProgram, (char *) "program", errorLog);
    CheckShaderError(vertexShader, (char *) "vertex", errorLog);
    CheckShaderError(fragmentShader, (char *) "fragment", errorLog);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


}

void Shader::UseProgram() {
    glUseProgram(shaderProgram);
}

void Shader::CheckShaderError(unsigned int shaderID, char *kind, char *result) {
    if (kind != "program") {
        glGetShaderInfoLog(shaderID, 512, NULL, result);
        std::cout << result << std::endl;
    } else {
        glGetProgramInfoLog(shaderID, 512, NULL, result);
        std::cout << result << std::endl;

    }
}

void Shader::SendUniformMat4(const char *paramName, glm::mat4 param) {
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, paramName), 1, GL_FALSE, glm::value_ptr(param));
}


void Shader::SendUniform1v(const char *paramName, glm::vec3 param) {
    glUniform3f(glGetUniformLocation(shaderProgram, paramName), param.x, param.y, param.z);
}

void Shader::SendUniform1f(const char *paramName, float param) {
    glUniform1f(glGetUniformLocation(shaderProgram, paramName), param);
}

void Shader::SendUniform1i(const char *paramName, int param) {
    glUniform1i(glGetUniformLocation(shaderProgram,paramName),param);
}
