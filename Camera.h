//
// Created by Young Fan on 2019-02-02.
//

#ifndef OPENGL_COURSE_CAMERA_H
#define OPENGL_COURSE_CAMERA_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Camera {
public:
    Camera(glm::vec3 _position, glm::vec3 targetPos, glm::vec3 _worldUp);

    Camera(glm::vec3 _position, float _pitch, float _yaw, glm::vec3 _worldUp);

    ~Camera();

    glm::vec3 position;
    glm::vec3 forward;
    glm::vec3 worldUp;
    glm::vec3 right;
    glm::vec3 up;
    float pitch;
    float yaw;

    glm::mat4 GetViewMatrix();

private:
    void UpdateCameraVectors();
};


#endif //OPENGL_COURSE_CAMERA_H
