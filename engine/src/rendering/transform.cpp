#include "transform.h"


Transform::Transform()
{
    this->pos = glm::vec3(0.0, 0.0, 0.0);
    this->rpy = glm::vec3(0.0, 0.0, 0.0);
    this->scale = glm::vec3(1.0, 1.0, 1.0);
}

Transform::Transform(glm::vec3 pos, glm::vec3 rpy)
{
    this->pos = pos;
    this->rpy = rpy;
    this->scale = glm::vec3(1.0, 1.0, 1.0);
}

Transform::Transform(glm::vec3 pos, glm::vec3 rpy, glm::vec3 scale)
{
    this->pos = pos;
    this->rpy = rpy;
    this->scale = scale;
}