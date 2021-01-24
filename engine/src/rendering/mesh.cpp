#include "mesh.h"

#include <iostream>
#include <vector>
#include <algorithm>

namespace grafik
{   
    // Represents a Mesh that may consist of one or more 3D-Models, that
    // can be rendered with the same renderer

    Mesh::Mesh(std::vector<VisualModel*> models)
    {

        int n = models.size();
        m_VABCount = 0;  // vertex Array Buffer
        m_IABCount = 0;  // index array Buffer


        // put all Models vertices into one Buffer using "glBufferSubData"

        std::vector<Vertex> vertices;
        //vertices.reserve(n);

        for (int i = 0; i < n; i++)
        {
            m_indSizes.push_back(models[i]->GetIndexCount());
            m_vertSizes.push_back(models[i]->GetVertexCount());

            m_VABCount += m_vertSizes[i];
            m_IABCount += m_indSizes[i];
            vertices.insert(vertices.end(), models[i]->GetVertices().begin(), models[i]->GetVertices().end());
        }

        m_numIndices = m_IABCount;

        // pul all indices into one Array for Buffer
        //unsigned int indices[IABCount];
        std::vector <unsigned int> indices;
        indices.reserve(m_IABCount);

        int k = 0;
        unsigned int vOffset = 0;
        unsigned int iOffset = 0;

        for (int i = 0; i < n; i++)
        {
            //models[i].GetIndices()
            models[i]->SetStart(iOffset);         // offsets are needed again in the drawing stage
            for (int j = 0; j < m_indSizes[i]; j++)
            {
                indices.push_back(models[i]->GetIndices()[j] + vOffset);
                k++;
            }
            vOffset += m_vertSizes[i];
            iOffset += m_indSizes[i];
            models[i]->SetEnd(iOffset - 1);
        }

        glGenVertexArrays(1, &m_vertexArrayObject);
        glBindVertexArray(m_vertexArrayObject);

        glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);

        glBufferData(GL_ARRAY_BUFFER, m_VABCount * sizeof(vertices[0]), &vertices[0], GL_STATIC_DRAW); // specify Data, size, type, how to Draw

        glEnableVertexAttribArray(0);       // vertices
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (void*)0);    // Tell OpenGL how Data is structured, it's type (vector - "list" wothout attributes)


        glEnableVertexAttribArray(1);       // normals
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (void*)offsetof(Vertex, normals));


        glEnableVertexAttribArray(2);       // texcoords
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (void*)offsetof(Vertex, texCoords));


        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[INDEX_VB]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * m_IABCount, &indices[0], GL_STATIC_DRAW);


        glBindVertexArray(0);

        // default Color



    }

    void Mesh::Add(VisualModel& model)
    {
        // add new Model Data to the end of the VAB

        int vertexCount = model.GetVertexCount();
        int indexCount = model.GetVertexCount();
        // add the new vertices at the end
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
        glBufferSubData(GL_ARRAY_BUFFER, m_VABCount * sizeof(model.GetVertices()[0]), vertexCount, &model.GetVertices()[0]);

        std::vector<unsigned int> indices;
        for (auto i : model.GetIndices())
            indices.push_back(i + m_VABCount);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[INDEX_VB]);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, sizeof(model.GetIndices()[0]) * m_IABCount, indexCount, &indices[0]);

        model.SetStart(m_IABCount);         // offsets are needed again in the drawing stage

        m_IABCount += indexCount;

        model.SetEnd(m_IABCount - 1);
    }


    Mesh::~Mesh()
    {
        glDeleteBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
        glDeleteVertexArrays(1, &m_vertexArrayObject);

    }


    void Mesh::Draw(VisualModel& model)
    {
        glBindVertexArray(m_vertexArrayObject);

        unsigned int start = model.GetStart();
        unsigned int end = model.GetEnd();
        unsigned int count = model.GetIndexCount();

        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, reinterpret_cast<void*>(0 + start * sizeof(unsigned int)));

        glBindVertexArray(0);

    }

}
