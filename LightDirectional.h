//
// Created by Young Fan on 2019-02-04.
//

#ifndef OPENGL_COURSE_LIGHTDIRECTIONAL_H
#define OPENGL_COURSE_LIGHTDIRECTIONAL_H

#include "glm/glm.hpp"
#include "glm/gtx/rotate_vector.hpp"

class LightDirectional {
public:
    LightDirectional(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color = glm::vec3(1, 1, 1));

    ~LightDirectional();

    glm::vec3 position;
    glm::vec3 color;
    glm::vec3 direction = glm::vec3(0, 0, 1);
    glm::vec3 angles;

    void UpdateLightDirection();
};


#endif //OPENGL_COURSE_LIGHTDIRECTIONAL_H
