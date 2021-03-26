#include "Camera.hpp"

namespace gps {

    //Camera constructor
    Camera::Camera(glm::vec3 cameraPosition, glm::vec3 cameraTarget, glm::vec3 cameraUp) {
        this->cameraPosition = cameraPosition;
        this->cameraTarget = cameraTarget;
        this->cameraUpDirection = cameraUp;

        this->cameraFrontDirection = glm::normalize(cameraTarget - cameraPosition);
        this->cameraRightDirection = glm::normalize(glm::cross(cameraFrontDirection, cameraUp));
        this->cameraUpDirection = glm::normalize(glm::cross(cameraRightDirection, cameraFrontDirection));

    }

    //return the view matrix, using the glm::lookAt() function
    glm::mat4 Camera::getViewMatrix() {
        return glm::lookAt(cameraPosition, cameraTarget, cameraUpDirection);
    }

    //update the camera internal parameters following a camera move event
    void Camera::move(MOVE_DIRECTION direction, float speed) {

        switch (direction) {
        case MOVE_FORWARD:
            this->cameraPosition = this->cameraPosition + this->cameraFrontDirection * speed;
            break;
        case MOVE_BACKWARD:
            this->cameraPosition = this->cameraPosition - this->cameraFrontDirection * speed;
            break;
        case MOVE_RIGHT:
            this->cameraPosition = this->cameraPosition + this->cameraRightDirection * speed;
            break;
        case MOVE_LEFT:
            this->cameraPosition = this->cameraPosition - this->cameraRightDirection * speed;
            break;
        }

        cameraTarget = cameraPosition + cameraFrontDirection; // are efect cand am depasit camera target
    }

    //update the camera internal parameters following a camera rotate event
    //yaw - camera rotation around the y axis
    //pitch - camera rotation around the x axis
    void Camera::rotate(float pitch, float yaw)
    {
        cameraFrontDirection.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        cameraFrontDirection.y = sin(glm::radians(pitch));
        cameraFrontDirection.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    }
}