#include <algorithm>
#include <glm/gtx/transform.hpp>

#include "visualModel.h"
#include "utils/loadMesh.h"

namespace grafik
{
    VisualModel::VisualModel(const std::string& fileName_obj)
    {

        loadOBJ(fileName_obj, m_vertices, m_indices);


        this->m_numIndices = m_indices.size();
        this->m_numVertices = m_vertices.size();

        //modelObjects.push_back(this);   // add Adress of this instance

        //m_model_ID = modelObjects.size();

        // default Color
        //material = PBRMaterial(0.5, 0.5, glm::vec4(0.8, 0.8, 0.8, 1.0));
        modelColor = glm::vec4(0.8, 0.8, 0.8, 1.0);
        lightCoeffs = glm::vec4(0.5, 0.5, 0.0, 1.0); // do we need this?
    }


    VisualModel::VisualModel()
    {
        // default Color
        material = PBRMaterial(0.5, 0.5, glm::vec4(0.8, 0.8, 0.8, 1.0));

        modelColor = glm::vec4(0.8, 0.8, 0.8, 1.0);

        lightCoeffs = glm::vec4(0.5, 0.5, 0.0, 1.0);

        //modelObjects.push_back(this);
        //m_model_ID = modelObjects.size();
    }


    VisualModel::~VisualModel()
    {
        // remove instance adress from ModelList
        //modelObjects.erase(std::remove(modelObjects.begin(), modelObjects.end(), this), modelObjects.end());

        // delete all the stuff
    }


    Plane createPlane(float width, float length, float height, float xDivs, float yDivs)
    {
        std::vector<Vertex> vertices;
        // 1.) create Vertices
        float dX = width / xDivs;
        float dY = length / yDivs;


        for (int i = 0; i < xDivs + 1; i++)
            for (int j = 0; j < yDivs + 1; j++)
            {                                                   // ^ y
                Vertex v = { glm::vec3(j * dX - width / 2, -length / 2 + i * dY, height / 2), glm::vec3(0.0f, 0.0f, 1.0f) };     // |-->x
                vertices.push_back(v);
            }

        // 2.) create Triangle connections
        std::vector<unsigned int> indices;

        int t1, t2, t3;

        for (int i = 0; i < xDivs; i++)
            for (int j = 0; j < yDivs; j++)
            {
                t1 = (j) * (xDivs + 1) + i;
                t2 = (j) * (xDivs + 1) + i + 1;
                t3 = (j + 1) * (xDivs + 1) + i + 1;
                indices.push_back(t1); indices.push_back(t2); indices.push_back(t3);

                t1 = (j) * (xDivs + 1) + i;
                t2 = (j + 1) * (xDivs + 1) + i + 1;
                t3 = (j + 1) * (xDivs + 1) + i;
                indices.push_back(t1); indices.push_back(t2); indices.push_back(t3);
            }

        return Plane{ vertices, indices };
    }
    Plane DividedCube::createFace(float edgeLength, int divs)
    {
        return createPlane(edgeLength, edgeLength, edgeLength, divs, divs);
    }

    Plane DividedCube::rotateFace(Plane in, axis ax, int steps)
    {
        Plane out(in);



        steps = steps % 4;  // wrap around

        float angle = glm::radians(steps * 90.0f);
        glm::mat3 R;
        switch (ax)
        {
        case X:
            R = glm::rotate(angle, glm::vec3(1.0f, 0.0f, 0.0f));
            break;
        case Y:
            R = glm::rotate(angle, glm::vec3(0.0f, 1.0f, 0.0f));
            break;
        case Z:
            R = glm::rotate(angle, glm::vec3(0.0f, 0.0f, 1.0f));
            break;
        }

        for (int i = 0; i < in.vertices.size(); i++)
        {
            out.vertices[i].pos = R * (in.vertices[i].pos);  // matmul each point
            out.vertices[i].normals = R * (in.vertices[i].normals);
        }

        return out;
    }

    DividedCube::DividedCube(float e, int divs)
    {

        // create inner vertices of the cube faces
        int vertCount = 0;

        float dE = e / divs;

        auto Top = createFace(e, divs);
        vertCount += Top.vertices.size();

        faces.push_back(Top);

        auto Front = rotateFace(Top, X, 1);
        for (auto& i : Front.indices)
            i += vertCount;
        vertCount += Front.vertices.size();
        faces.push_back(Front);

        auto Bottom = rotateFace(Top, X, 2);
        for (auto& i : Bottom.indices)
            i += vertCount;
        vertCount += Bottom.vertices.size();
        faces.push_back(Bottom);

        auto Back = rotateFace(Top, X, 3);
        for (auto& i : Back.indices)
            i += vertCount;
        vertCount += Back.vertices.size();
        faces.push_back(Back);

        auto Left = rotateFace(Top, Y, 1);
        for (auto& i : Left.indices)
            i += vertCount;
        vertCount += Left.vertices.size();
        faces.push_back(Left);

        auto Right = rotateFace(Top, Y, -1);
        for (auto& i : Right.indices)
            i += vertCount;
        vertCount += Right.vertices.size();
        faces.push_back(Right);

        for (auto f : faces)
        {
            m_vertices.insert(vertices.end(), f.vertices.begin(), f.vertices.end());
            m_indices.insert(indices.end(), f.indices.begin(), f.indices.end());
        }

        //m_vertices = vertices;
        //m_indices = indices;
        this->m_numIndices = m_indices.size();
        this->m_numVertices = m_vertices.size();

        //modelObjects.push_back(this);

    }


    Sphere::Sphere(float r, int gridDivisions) : DividedCube(2.0f, gridDivisions)
    {
        // Spherify Cube
        vertices.clear();

        for (auto& f : faces)
        {
            for (auto& v : f.vertices)
            {
                float x = v.pos[0];
                float y = v.pos[1];
                float z = v.pos[2];
                float x_ = x * sqrt(1 - 0.5 * y * y - 0.5 * z * z + y * y * z * z / 3);
                float y_ = y * sqrt(1 - 0.5 * x * x - 0.5 * z * z + x * x * z * z / 3);
                float z_ = z * sqrt(1 - 0.5 * x * x - 0.5 * y * y + x * x * y * y / 3);
                v.pos = glm::vec3(x_, y_, z_) * r;
                v.normals = glm::normalize(v.pos);
            }
            m_vertices.insert(vertices.end(), f.vertices.begin(), f.vertices.end());
        }

        // collison Model
        //model = new collisionModel(r, glm::vec3(0), modelPose.GetPosRef());

    }


    PlaneModel::PlaneModel(float w, float l, float h, float gridSize)
    {
        int xDivs, yDivs, zDivs;

        // recalculate width, so it fits the grid Size
        xDivs = floor(w / gridSize);
        yDivs = floor(l / gridSize);

        w = gridSize * xDivs;
        l = gridSize * yDivs;

        planeObj = createPlane(w, l, h, xDivs, yDivs);


        vertices = planeObj.vertices;
        indices = planeObj.indices;

        m_vertices = vertices;
        m_indices = indices;

        m_numIndices = planeObj.indices.size();
        m_numVertices = planeObj.vertices.size();

    }


}
