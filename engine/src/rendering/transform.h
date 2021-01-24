#pragma once

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/transform.hpp"
#include "glm/gtx/euler_angles.hpp"

#include <iostream>
class Transform
{
public:

    Transform();
    Transform(glm::vec3 pos, glm::vec3 rpy);
    Transform(glm::vec3 pos, glm::vec3 rpy, glm::vec3 scale);

    inline glm::mat4 GetTransform() const
    {
        glm::mat4 T = glm::yawPitchRoll(glm::radians(rpy.x), glm::radians(rpy.y), glm::radians(rpy.z));

        //glm::mat4 T = glm::mat4(1.0);
        T[3] = glm::vec4(pos, 1.0);
        glm::mat4 S = glm::scale(scale);
        return T * S;
    }

    inline glm::vec3* GetRot() { return &rpy; }
    glm::vec3 GetPos() { return pos; }
    inline glm::vec3* GetPosRef() { return &pos; }
    inline glm::vec3* GetScale() { return &scale; }

    inline void SetRot(glm::vec3 rpy) { this->rpy = rpy; }
    inline void SetPos(glm::vec3 pos) { this->pos = pos; }
    inline void SetScale(glm::vec3 scale) { this->scale = scale; }

private:
    glm::vec3 rpy;
    glm::vec3 pos;
    glm::vec3 scale;
};


