//
// Created by Young Fan on 2019-02-05.
//

#ifndef OPENGL_COURSE_LIGHTSPOT_H
#define OPENGL_COURSE_LIGHTSPOT_H

#include "glm/glm.hpp"
#include "glm/gtx/rotate_vector.hpp"


class LightSpot {
public:
    LightSpot(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color = glm::vec3(1, 1, 1));
    ~LightSpot();

    glm::vec3 position;
    glm::vec3 color;
    glm::vec3 direction = glm::vec3(0, 0, 1);
    glm::vec3 angles;
    float cosPhy;
    void UpdateLightDirection();
};


#endif //OPENGL_COURSE_LIGHTSPOT_H
