//
// Created by Young Fan on 2019-02-02.
//

#include "Camera.h"

Camera::Camera(glm::vec3 _position, glm::vec3 targetPos, glm::vec3 _worldUp) {
    position = _position;
    forward = glm::normalize(targetPos - position);
    worldUp = _worldUp;
    right = glm::normalize(glm::cross(worldUp, forward));
    up = glm::normalize(glm::cross(right, forward));
}

Camera::~Camera() {

}

glm::mat4 Camera::GetViewMatrix() {
    return glm::lookAt(position, position + forward, worldUp);
}
