//
// Created by Young Fan on 2019-02-05.
//

#include "LightPoint.h"

LightPoint::LightPoint(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color) {
    position = _position;
    angles = _angles;
    color = _color;
    constant = 1.0f;
    linear = 0.09f;
    quadratic = 0.032f;
}

LightPoint::~LightPoint() = default;
