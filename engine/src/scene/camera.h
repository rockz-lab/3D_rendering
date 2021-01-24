    #ifndef CAMERA_H
#define CAMERA_H


#include <glm/glm.hpp>

#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/matrix_inverse.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>


class Camera
{
public:
    Camera(float h_fov, float width, float height, float near, float far);
    Camera(float h_fov, float width, float height, float near, float far, glm::vec3 pos, glm::vec3 center);

    void setWindowSize(float width, float height);
    void Update();
    void moveForward(float units);
    void moveLeft(float units);

    void moveUp(float units);

    void rotateUp(float degrees);
    void rotateLeft(float degrees);

    void setUp(glm::vec3 up) {this->up = up;}

    void move3(glm::vec3 translation);

    inline glm::mat4 getCamTrans() const
    {
        return camProj*pose;
    }

    const glm::mat4 getCamProj() const
    {
        return camProj;
    }

    const glm::mat4 getCamPose() const
    {
        return pose;
    }

    //inline glm::vec3* GetCenter() { return &center; }
    const glm::vec3 GetPos() const { return pos; }
    glm::vec3* GetPosRef() { return &pos; }

    inline void SetRot(glm::vec3 center) { this->center = center; }
    inline void SetPos(glm::vec3 pos) { this->pos = pos; }

    float getHeight() const { return height; }
    float getWidth() const { return width; }
    float getFar() const { return far; }
    float getNear() const { return near; }
    float getHVOF() const { return h_fov; }

    glm::vec3 up;
private:
    glm::vec3 pos;
    glm::vec3 center;
    glm::mat4 pose;
    glm::mat4 camProj;
    float pitch;

    float near;
    float far;
    float width;
    float height;

    float h_fov;


};

#endif // CAMERA_H
