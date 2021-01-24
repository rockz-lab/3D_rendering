#pragma once

#include "world.h"
//#include "pbrpost.h"

//#include "terrainMesh.h"

namespace grafik
{
    class Renderer
    {

    public:
        Renderer(Scene);

        void setTerrain(ChunkManager* manager);

        void Render();
        void Render(float dT);

    private:
        vector<Model*> models;
        Mesh* mainMesh;

        TerrainMesh* terrain;
        ChunkManager* manager;

        multiLights* multiLightsShader;
        Shader* sunShader;
        Camera* cam;
        Lights* lights;
        Display* display;

        PBRpost* postPipeline;

        float m_whitePoint;

        bool terrainSet = false;
    };

}

