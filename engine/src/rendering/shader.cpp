#include "shader.h"

#include <glm/gtc/type_ptr.hpp>

#include <fstream>


namespace grafik
{
    // some functions we need
    void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
    std::string LoadShader(const std::string& fileName);
    GLuint createShader(const std::string& text, GLenum shaderType);

    Shader::Shader()
    {

    }

    Shader::Shader(const std::string& fileName, type initType)
    {
        switch (initType)
        {
        case EMPTY_SHADER:
            m_program = glCreateProgram();
            m_shaders.push_back(createShader(LoadShader(fileName + ".vsh"), GL_VERTEX_SHADER));
            m_shaders.push_back(createShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER));

            for (unsigned int i = 0; i < m_shaders.size(); i++)
                glAttachShader(m_program, m_shaders[i]);    // adding all shaders

            glBindAttribLocation(m_program, 0, "position");
            glBindAttribLocation(m_program, 2, "texCoord");

            glLinkProgram(m_program);
            CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: Pragram failed to link: ");

            glValidateProgram(m_program);
            CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Pragram invalid: ");
            break;
        case BASE_SHADER:
            m_program = glCreateProgram();
            m_shaders.push_back(createShader(LoadShader(fileName + ".vsh"), GL_VERTEX_SHADER));
            m_shaders.push_back(createShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER));

            for (unsigned int i = 0; i < m_shaders.size(); i++)
                glAttachShader(m_program, m_shaders[i]);    // adding all shaders

            glBindAttribLocation(m_program, 0, "position");
            glBindAttribLocation(m_program, 1, "normal");
            glBindAttribLocation(m_program, 2, "texCoord");

            glLinkProgram(m_program);
            CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: Pragram failed to link: ");

            glValidateProgram(m_program);
            CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Pragram invalid: ");

            m_uniforms.push_back(glGetUniformLocation(m_program, "transform"));     // create variable, that can be sent to GPU (vertex shader)
            m_uniforms.push_back(glGetUniformLocation(m_program, "tfMesh"));
            m_uniforms.push_back(glGetUniformLocation(m_program, "camaraPos"));
            m_uniforms.push_back(glGetUniformLocation(m_program, "objColor"));
            m_uniforms.push_back(glGetUniformLocation(m_program, "lightCoeffs"));
            m_uniforms.push_back(glGetUniformLocation(m_program, "nPhong"));
            break;

        }

    }

    Shader::Shader(const std::string& fileName, const std::string& header, type initType)
    {
        switch (initType)
        {
        case EMPTY_SHADER:
            m_program = glCreateProgram();
            m_shaders[0] = createShader(LoadShader(fileName + ".vsh"), GL_VERTEX_SHADER);
            m_shaders[1] = createShader(header + LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);

            for (unsigned int i = 0; i < m_shaders.size(); i++)
                glAttachShader(m_program, m_shaders[i]);    // adding all shaders

            glBindAttribLocation(m_program, 0, "position");

            glLinkProgram(m_program);
            CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: Pragram failed to link: ");

            glValidateProgram(m_program);
            CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Pragram invalid: ");
            break;
        case BASE_SHADER:
            m_program = glCreateProgram();
            m_shaders[0] = createShader(LoadShader(fileName + ".vsh"), GL_VERTEX_SHADER);
            m_shaders[1] = createShader(header + LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);

            for (unsigned int i = 0; i < m_shaders.size(); i++)
                glAttachShader(m_program, m_shaders[i]);    // adding all shaders

            glBindAttribLocation(m_program, 0, "position");
            glBindAttribLocation(m_program, 1, "normal");
            glBindAttribLocation(m_program, 2, "texCoord");

            glLinkProgram(m_program);
            CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: Pragram failed to link: ");

            glValidateProgram(m_program);
            CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Pragram invalid: ");

            m_uniforms.push_back(glGetUniformLocation(m_program, "transform"));     // create variable, that can be sent to GPU (vertex shader)
            m_uniforms.push_back(glGetUniformLocation(m_program, "tfMesh"));
            m_uniforms.push_back(glGetUniformLocation(m_program, "camaraPos"));
            m_uniforms.push_back(glGetUniformLocation(m_program, "objColor"));
            m_uniforms.push_back(glGetUniformLocation(m_program, "lightCoeffs"));
            m_uniforms.push_back(glGetUniformLocation(m_program, "nPhong"));
            break;

        }

    }

    Shader::Shader(const std::string& fileName, const std::string& header)
    {
        Shader(fileName, fileName, header);

    }

    Shader::Shader(const std::string& vertShader, const std::string& fragShader, const std::string& header)
    {
        m_program = glCreateProgram();
        m_shaders[0] = createShader(LoadShader(vertShader + ".vsh"), GL_VERTEX_SHADER);
        m_shaders[1] = createShader(header + LoadShader(fragShader + ".fs"), GL_FRAGMENT_SHADER);

        for (unsigned int i = 0; i < m_shaders.size(); i++)
            glAttachShader(m_program, m_shaders[i]);    // adding all shaders

        glBindAttribLocation(m_program, 0, "position");
        glBindAttribLocation(m_program, 1, "normal");
        glBindAttribLocation(m_program, 2, "texCoord");

        glLinkProgram(m_program);
        CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: Pragram failed to link: ");

        glValidateProgram(m_program);
        CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Program invalid: ");

        m_uniforms.push_back(glGetUniformLocation(m_program, "transform"));     // create variable, that can be sent to GPU (vertex shader)
        m_uniforms.push_back(glGetUniformLocation(m_program, "tfMesh"));
        m_uniforms.push_back(glGetUniformLocation(m_program, "camaraPos"));
        addUniform("objColor");
        addUniform("lightCoeffs");
        addUniform("nPhong");

    }

    void Shader::addShader(const std::string& fileName, type shaderType)
    {
        switch (shaderType)
        {
        case COMPUTE_SHADER:
            m_program = glCreateProgram();
            m_shaders.push_back(createShader(LoadShader(fileName + ".csh"), GL_COMPUTE_SHADER));

            for (unsigned int i = 0; i < m_shaders.size(); i++)
                glAttachShader(m_program, m_shaders[i]);    // adding all shaders

            glLinkProgram(m_program);
            CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: Pragram failed to link: ");

            glValidateProgram(m_program);
            CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Program invalid: ");
            break;
        }
    }

    void Shader::setTexture(const std::string& name, GLuint unitID)
    {
        // set uniforms for texture sampling
        GLuint textureLocation = glGetUniformLocation(m_program, name.c_str());
        //GLuint shadowMapLocation  = glGetUniformLocation(m_program, "shadowMap");
        if (textureLocation == -1)
        {
            std::cerr << "Uniform name " + name + " does not exist in Shader!" << std::endl;
        }
        else
        {
            glUniform1i(textureLocation, unitID);
        }
        //nTextures ++;
        //glUniform1i(shadowMapLocation,  1);
    }

    void Shader::addUniform(const std::string& name)
    {

        m_uniforms.push_back(glGetUniformLocation(m_program, name.c_str()));
        m_uniform_names.push_back(name);
    }

    void Shader::UpdateUniform1f(const std::string& name, float data)
    {
        // check if name exists as uniform
        auto it = std::find(m_uniform_names.begin(), m_uniform_names.end(), name);
        if (it != m_uniform_names.end())
        {
            glUniform1f(m_uniforms.at(it - m_uniform_names.begin()), data);
        }
        else
            std::cerr << "Uniform 1f has not been initialized!" << std::endl;
    }

    void Shader::UpdateUniform1i(const std::string& name, int data)
    {
        // check if name exists as uniform
        auto it = std::find(m_uniform_names.begin(), m_uniform_names.end(), name);
        if (it != m_uniform_names.end())
        {
            glUniform1i(m_uniforms.at(it - m_uniform_names.begin()), data);
        }
        else
            std::cerr << "Uniform 1i has not been initialized!" << std::endl;
    }

    void Shader::UpdateUniformVec3(const std::string& name, const glm::vec3& data)
    {
        // check if name exists as uniform
        auto it = std::find(m_uniform_names.begin(), m_uniform_names.end(), name);
        if (it != m_uniform_names.end())
        {
            glUniform3f(m_uniforms.at(it - m_uniform_names.begin()), data.x, data.y, data.z);
        }
        else
            std::cerr << "Uniform vec3 has not been initialized!" << std::endl;
    }

    void Shader::UpdateUniformVec2(const std::string& name, const glm::vec2& data)
    {
        // check if name exists as uniform
        auto it = std::find(m_uniform_names.begin(), m_uniform_names.end(), name);
        if (it != m_uniform_names.end())
        {
            glUniform2f(m_uniforms.at(it - m_uniform_names.begin()), data.x, data.y);
        }
        else
            std::cerr << "Uniform vec2 has not been initialized!" << std::endl;
    }

    void Shader::UpdateUniformArrayVec3(const std::string& name, std::vector<glm::vec3>& data, int nElements)
    {
        // check if name exists as uniform
        auto it = std::find(m_uniform_names.begin(), m_uniform_names.end(), name);

        if (it != m_uniform_names.end())
        {
            glUniform3fv(m_uniforms.at(it - m_uniform_names.begin()), (GLsizei)(nElements), glm::value_ptr(data[0]));
        }
        else
            std::cerr << "Uniform Array of vec3 has not been initialized!" << std::endl;
    }

    void Shader::UpdateUniform1fArray(const std::string& name, std::vector<float>& data, int nElements)
    {
        // check if name exists as uniform
        auto it = std::find(m_uniform_names.begin(), m_uniform_names.end(), name);


        if (it != m_uniform_names.end())
        {
            glUniform1fv(m_uniforms.at(it - m_uniform_names.begin()), (GLsizei)(nElements), (const float*)(&data[0]));
        }
        else
            std::cerr << "Uniform Array of floats has not been initialized!" << std::endl;
    }

    void Shader::UpdateUniformMat4(const std::string& name, const glm::mat4& data)
    {
        // check if name exists as uniform
        auto it = std::find(m_uniform_names.begin(), m_uniform_names.end(), name);

        if (it != m_uniform_names.end())
        {
            glUniformMatrix4fv(m_uniforms.at(it - m_uniform_names.begin()), 1, GL_FALSE, &data[0][0]);
        }
        else
            std::cerr << "Uniform Matrix 4x4 has not been initialized!" << std::endl;
    }


    void Shader::Bind()
    {
        glUseProgram(m_program);
    }

    /*void Shader::Update(Camera& camera, Model& model)
    {
        glm::mat4 tfMesh = model.modelPose.GetTransform();
        glm::mat4 MVP = camera.getCamTrans() * tfMesh;

        UpdateUniformMat4("transform", MVP);
        UpdateUniformMat4("tfMesh", tfMesh);

        UpdateUniformVec3("cameraPos", camera.GetPos());
    }*/


    // helper method to load the shader text files

    GLuint createShader(const std::string& text, GLenum shaderType)
    {
        GLuint shader = glCreateShader(shaderType);

        if (shader == 0)
            std::cerr << "shader failed to create!" << std::endl;

        const GLchar* shaderSourceStrings[1];
        GLint shaderSourceStringLengths[1];

        shaderSourceStrings[0] = text.c_str();              // Source Code conversion to c String
        shaderSourceStringLengths[0] = text.length();

        glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
        glCompileShader(shader);



        CheckShaderError(shader, GL_COMPILE_STATUS, false, "shader compilation failed:  ");


        return shader;
    }

    std::string LoadShader(const std::string& fileName)
    {
        std::ifstream file;
        file.open((fileName).c_str());

        std::string output;
        std::string line;

        if (file.is_open())
        {
            while (file.good())
            {
                std::getline(file, line);
                output.append(line + "\n");
            }
        }
        else
        {
            std::cerr << "Unable to load shader: " << fileName << std::endl;
        }

        return output;
    }

    // helper method to get error messages
    void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
    {
        GLint success = 0;
        GLchar error[1024] = { 0 };

        if (isProgram)
            glGetProgramiv(shader, flag, &success);
        else
            glGetShaderiv(shader, flag, &success);

        if (success == GL_FALSE)
        {
            if (isProgram)
                glGetProgramInfoLog(shader, sizeof(error), NULL, error);
            else
                glGetShaderInfoLog(shader, sizeof(error), NULL, error);

            std::cerr << errorMessage << ": '" << error << "'" << std::endl;
        }
    }


}



