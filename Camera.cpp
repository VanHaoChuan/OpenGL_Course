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

Camera::Camera(glm::vec3 _position, float _pitch, float _yaw, glm::vec3 _worldUp) {
    position = _position;
    worldUp = _worldUp;
    yaw = _yaw;
    pitch = _pitch;
    forward.x = glm::cos(_pitch) * glm::sin(_yaw);
    forward.y = glm::sin(_pitch);
    forward.z = glm::cos(_pitch) * glm::cos(_yaw);
    right = glm::normalize(glm::cross(worldUp, forward));
    up = glm::normalize(glm::cross(right, forward));
}


Camera::~Camera() {

}

glm::mat4 Camera::GetViewMatrix() {
    return glm::lookAt(position, position + forward, worldUp);
}

void Camera::UpdateCameraVectors() {
    forward.x = glm::cos(pitch) * glm::sin(yaw);
    forward.y = glm::sin(pitch);
    forward.z = glm::cos(pitch) * glm::cos(yaw);
    right = glm::normalize(glm::cross(worldUp, forward));
    up = glm::normalize(glm::cross(right, forward));
}

