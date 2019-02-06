//
// Created by Young Fan on 2019-02-05.
//

#include "LightSpot.h"

LightSpot::LightSpot(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color) {
    position = _position;
    angles = _angles;
    color = _color;
}

void LightSpot::UpdateLightDirection() {

    direction = glm::vec3(0, 0, 1);//point to z axis.
    direction = glm::rotateZ(direction, angles.z);
    direction = glm::rotateX(direction, angles.x);
    direction = glm::rotateY(direction, angles.y);
    direction *= -1;
    float cosPhy = 0.9f;
}

LightSpot::~LightSpot() = default;
