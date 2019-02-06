//
// Created by Young Fan on 2019-02-04.
//

#include "LightDirectional.h"

void LightDirectional::UpdateLightDirection() {
    direction = glm::vec3(0, 0, 1);//point to z axis.
    direction = glm::rotateZ(direction, angles.z);
    direction = glm::rotateX(direction, angles.x);
    direction = glm::rotateY(direction, angles.y);
    direction *= -1;
}

LightDirectional::LightDirectional(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color) {
    position = _position;
    angles = _angles;
    color = _color;
    UpdateLightDirection();
}

LightDirectional::~LightDirectional() {

}
