#pragma once

#include <glm/glm.hpp>
#include <vector>

#include "transform.h"
#include "utils/vertex.h"
#include "core/events.h""
#include "core/common.h"

//#include "physics/collisionmodel.h"

namespace grafik
{

    struct PBRMaterial : public eventNode
    {
        glm::vec4 color;

        float metallic;
        float roughness;

        PBRMaterial(float metallic, float roughness, glm::vec4 color)
        {
            this->metallic = metallic;
            this->roughness = roughness;
            this->color = color;
        }
        PBRMaterial()
        {
            this->metallic = 0;
            this->roughness = 0.1;
            this->color = glm::vec4(1, 0, 0, 1);
        }
    };

    // not used
    struct PhongMaterial
    {

        float ambient;
        float diffuse;
        float specular;
        float n_Phong;

    };


    class VisualModel
    {
    public:


        // Construction
        VisualModel();    // for inheritance
        VisualModel(const std::string& fileName_obj);

        // Deconstruction
        ~VisualModel();
        Transform modelPose;

        PBRMaterial material;
        glm::vec4 modelColor;
        glm::vec4 lightCoeffs; // ambient diffuse point, diffuse dir, n_Phong

        const std::vector<Vertex>& GetVertices() { std::vector<Vertex>& vertices_out = m_vertices; return vertices_out; }
        const std::vector<unsigned int>& GetIndices() { std::vector<unsigned int>& indices_out = m_indices; return indices_out; }

        // keep track of all Models for Rendering -> maybe do this in a base class ot Factory instead
        //static std::vector<VisualModel*> modelObjects;    // maybe we need "inline" for some reason
        bool isLight = false;


        int GetVertexCount() { return m_numVertices; }
        int GetIndexCount() { return m_numIndices; }
        int GetModelID() { return m_model_ID; }

        int GetStart() { return m_start; }
        int GetEnd() { return m_end; }

        void SetStart(int m_start) { this->m_start = m_start; }
        void SetEnd(int m_end) { this->m_end = m_end; }
    protected:

        // actual vertex data
        std::vector<Vertex> m_vertices;
        std::vector<unsigned int> m_indices;

        // helper variables for assembling the meshes into one
        int m_numVertices;
        int m_numIndices;
        int m_start;
        int m_end;
        int m_model_ID;
    };

    //##############################################################################
    // derived objects for cration of primitives.
    // TODO: vector insertion code is bad -> use reserve and push_back

    struct Plane
    {
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
    };

    class DividedCube : public VisualModel
    {
    public:
        DividedCube(float edgeLength, int div);

    protected:
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;

        std::vector<Plane> faces;
        enum axis
        {
            X,
            Y,
            Z

        };

        Plane createFace(float edgeLength, int divs);

        Plane rotateFace(Plane in, axis ax, int steps);        // rotate in 90 degree steps

    };

    class Sphere : public DividedCube
    {
    public:
        Sphere(float r, int gridDivisions);

        float r;
    private:
        //collisionModel* model;
    };

    class PlaneModel : public VisualModel
    {
    public:
        PlaneModel(float w, float l, float h, float gridSize);
    protected:
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        Plane planeObj;
    };

}
