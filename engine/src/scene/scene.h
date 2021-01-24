#pragma once
#include "core/common.h"

#include "rendering/visualModel.h"
#include "lights.h"
#include "camera.h"

// Class that mainly composites the game class
// keep track of Meshes, Lights, Camera
// drawing, shaders

namespace grafik
{
	class Scene 
	{
	public:
		Scene();

		void setCamera(float near, float far, float FoV);

		void addModel(std::shared_ptr<GameObject>& model);

		void addLight(std::shared_ptr<LightBase>& light);
		
		void Draw();
	private:
		std::shared_ptr<Camera> cam;
		std::vector<std::shared_ptr<GameObject>> gameObjects;
		std::vector<std::shared_ptr<LightBase>> lights;


	};
}