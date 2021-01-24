#include "scene.h"
#include "rendering/vertex_buffer.h"

namespace grafik
{
	Scene::Scene()
	{
		cam = std::make_unique<Camera>(70, 1280, 720, 0.1, 1000);
	}

	void Scene::setCamera(float, float, float FoV)
	{
	}

	void Scene::addModel(std::shared_ptr<GameObject>& model)
	{
		gameObjects.push_back(std::move(model));

		// extend the Vertex Buffer 


	}

	void Scene::addLight(std::shared_ptr<LightBase>& light)
	{
	}

	void Scene::Draw()
	{

	}

}
