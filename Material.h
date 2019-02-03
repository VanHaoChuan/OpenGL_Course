//
// Created by Young Fan on 2019-02-03.
//

#ifndef OPENGL_COURSE_MATERIAL_H
#define OPENGL_COURSE_MATERIAL_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Shader.h"

class Material {
public:
    Shader *shader;
    glm::vec3 diffuse;
    glm::vec3 ambient;
    glm::vec3 specular;
    float shininess;

    Material(Shader *_shader, glm::vec3 _diffuse, glm::vec3 _ambient, glm::vec3 _specular,
             float _shininess);

    ~Material();
};


#endif //OPENGL_COURSE_MATERIAL_H
