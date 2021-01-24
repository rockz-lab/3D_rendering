#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>

#include "visualModel.h"

namespace grafik
{
    class Mesh
    {
    public:
        Mesh(std::vector<VisualModel*> models);       // Init mesh based on a number of Models

        void Draw(VisualModel& model);    // needs to know model ID

        void Add(VisualModel& model);     // no delete

        virtual ~Mesh();

        GLuint m_vertexArrayObject;
    protected:
    private:
        Mesh(const Mesh& other) {}
        void operator=(const Mesh& other) {}

        enum
        {
            POSITION_VB,
            NORMAL_VB,
            TEXCOORD_VB,
            INDEX_VB,
            NUM_BUFFERS
        };

        GLuint m_vertexArrayBuffers[NUM_BUFFERS];
        unsigned int m_numIndices;

        std::vector<int> m_indSizes;
        std::vector<int> m_vertSizes;

        int m_VABCount;
        int m_IABCount;
    };

}
