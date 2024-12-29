#include "Camera.hpp"
#include <glm/glm.hpp>

namespace gps {

    Camera::Camera(glm::vec3 cameraPosition, glm::vec3 cameraTarget, glm::vec3 cameraUp) {
        this->cameraPosition = cameraPosition;
        this->cameraTarget = cameraTarget;
        this->cameraUpDirection = cameraUp;

        this->cameraFrontDirection = glm::normalize(cameraTarget - cameraPosition);
        this->cameraRightDirection = glm::normalize(glm::cross(cameraFrontDirection, cameraUpDirection));
    }

    glm::mat4 Camera::getViewMatrix() {
        return glm::lookAt(this->cameraPosition, this->cameraTarget, this->cameraUpDirection);
    }

    void Camera::move(MOVE_DIRECTION direction, float speed) {
        switch (direction) {
        case MOVE_LEFT:
            this->cameraPosition -= this->cameraRightDirection * speed;
            break;
        case MOVE_RIGHT:
            this->cameraPosition += this->cameraRightDirection * speed;
            break;
        case MOVE_FORWARD:
            this->cameraPosition += this->cameraFrontDirection * speed;
            break;
        case MOVE_BACKWARD:
            this->cameraPosition -= this->cameraFrontDirection * speed;
            break;
        default:
            break;
        }

        this->cameraTarget = this->cameraPosition + this->cameraFrontDirection;
    }

    void Camera::rotate(float pitch, float yaw) {

        if (pitch > 89.0f) pitch = 89.0f;
        if (pitch < -89.0f) pitch = -89.0f;

        this->cameraFrontDirection = glm::normalize(glm::vec3(
            cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
            sin(glm::radians(pitch)),
            sin(glm::radians(yaw)) * cos(glm::radians(pitch))
        ));

      
        this->cameraRightDirection  = glm::normalize(glm::cross(cameraFrontDirection, cameraUpDirection));
        this->cameraUpDirection     = glm::normalize(glm::cross(cameraRightDirection, cameraFrontDirection));


        this->cameraTarget = this->cameraPosition + this->cameraFrontDirection;
    }

}