#pragma once

#include "core/common.h"

#include <GL/glew.h>

// automate shader creation, Updating, Uniform creation as much as possible
namespace grafik
{   

    enum type
    {
        EMPTY_SHADER,
        BASE_SHADER,
        COMPUTE_SHADER,
    };

    class Shader
    {
    public:
        Shader();
        Shader(const std::string& fileName, type initType);

        Shader(const std::string& fileName, const std::string& header);
        Shader(const std::string& vertShader, const std::string& fragShader, const std::string& header);
        Shader(const std::string& fileName, const std::string& header, type initType);

        void addShader(const std::string& fileName, type shaderType);
        void Bind();

        // set texture samplers
        void setTexture(const std::string& name, GLuint unitID);
        
        // move this elsewhere
        //void Update(Camera& camera, Model& model);
        //virtual ~Shader();

        void addUniform(const std::string& name);
        void UpdateUniform1f(const std::string& name, float data);
        void UpdateUniform1fArray(const std::string& name, std::vector<float>& data, int nElements);
        void UpdateUniform1i(const std::string& name, int data);
        void UpdateUniformArrayVec3(const std::string& name, std::vector<glm::vec3>& data, int nElements);
        void UpdateUniformVec3(const std::string& name, const glm::vec3& data);
        void UpdateUniformVec2(const std::string& name, const glm::vec2& data);
        void UpdateUniformMat4(const std::string& name, const glm::mat4& data);

        GLuint getProgram() { return m_program; }

    protected:
        // needed?
        Shader(const Shader& other) {}
        void operator=(const Shader& other) {}

        GLuint m_program;
        std::vector<GLuint> m_shaders;
        std::vector<GLuint> m_uniforms;
        std::vector<std::string> m_uniform_names;
        int nTextures = 0;

    };
}