#include "camera.h"

#include <iostream>     // for debugging
#include <cstdio>

Camera::Camera(float h_fov, float width, float height, float near, float far, glm::vec3 pos, glm::vec3 center)
{
    // fully specified definition
    float aspect = width/height;
    camProj = glm::perspective(glm::radians(h_fov), aspect, near, far);

    //camProj = glm::perspectiveFov(glm::radians(h_fov), width, height, near, far );
    std::printf("K = \t[%.4f, %.4f, %.4f, %.4f \n \t%.4f, %.4f, %.4f, %.4f \n \t%.4f, %.4f, %.4f, %.4f \n \t%.4f, %.4f, %.4f, %.4f] \n",
                camProj[0][0], camProj[0][1], camProj[0][2], camProj[0][3],
                camProj[1][0], camProj[1][1], camProj[1][2], camProj[1][3],
                camProj[2][0], camProj[2][1], camProj[2][2], camProj[2][3],
                camProj[3][0], camProj[3][1], camProj[3][2], camProj[3][3]);

    this->center = center;
    this->pos = pos;
    this->near = near;
    this->far = far;
    this->h_fov = h_fov;
    this->width = width;
    this->height = height;

    up = glm::vec3(0.0, 0.0, 1.0);
    pose = glm::lookAt(pos, center, up);

    // pitch angle wrt. the up direction
    glm::vec3 lookDir = glm::normalize(center - pos);
    pitch = glm::acos(glm::dot(lookDir, up));
    pitch = glm::degrees(pitch);
}

void Camera::setWindowSize(float width, float height)
{
    float aspect = width/height;
    camProj = glm::perspective(glm::radians(h_fov), aspect, near, far);
}



Camera::Camera(float h_fov, float width, float height, float near, float far)
{
    // default orientation and location
    float aspect = width/height;
    camProj = glm::perspective(glm::radians(h_fov), aspect, near, far);

    this->center = glm::vec3(0.0, 0.0, 0.0);
    this->pos = glm::vec3(0.0, 5.0, 0.0);
    this->width = width;
    this->height = height;
    this->near = near;
    this->far = far;
    this->h_fov = 70;

    up = glm::vec3(0.0, 0.0, 1.0);
    pose = glm::lookAt(pos, center, up);

    // pitch angle wrt. the up direction
    glm::vec3 lookDir = glm::normalize(center - pos);
    pitch = glm::acos(glm::dot(lookDir, up));
    pitch = glm::degrees(pitch);
}

void Camera::Update()
{
    pose = glm::lookAt(pos, center, up);
}

void Camera::moveForward(float units)
{
    glm::vec3 forward = glm::normalize(center - pos);
    forward.z = 0.0;
    forward = glm::normalize(forward) * units;

    this->center += forward;
    this->pos += forward;
}

void Camera::moveLeft(float units)
{
    glm::vec3 forward = glm::normalize(center - pos);

    glm::vec3 left = glm::cross(up, forward);
    left.z = 0.0;

    left = glm::normalize(left) * units;

    this->center += left;
    this->pos += left;
}

void Camera::moveUp(float units)
{

    this->center += up*units;
    this->pos += up*units;
}

void Camera::rotateUp(float degrees)
{
    glm::vec3 forward = glm::normalize(center - pos);

    glm::vec3 left = glm::cross(up, forward);
    // rotate around the "left" direction

    pitch += degrees;

    if (pitch >= 180)
    {
        pitch = 180;
        degrees = 0;
    } else if (pitch < 0)
    {
        pitch = 0;
        degrees = 0;
    }
    //std::cout << pitch << std::endl;

    glm::vec3 lookdir = glm::rotate(forward, glm::radians(degrees), left);
    this->center = pos + lookdir;
}

void Camera::rotateLeft(float degrees)
{
    glm::vec3 forward = glm::normalize(center - pos);


    // rotate around the "up" direction

    glm::vec3 lookdir = glm::rotate(forward, -glm::radians(degrees), up);
    this->center = pos + lookdir;
}

void Camera::move3(glm::vec3 translation)
{
    pos += translation;
    center += translation;
}
