#pragma once
#include "core/common.h"
#include "GameObject.h"

namespace grafik
{
	enum LightType
	{
		LIGHT_DIRECTIONAL,
		LIGHT_POINT
	};
	class LightBase : public GameObject
	{
		glm::vec3 color;
	};
	class PointLight : public LightBase
	{
	public:
		glm::vec3 pos;
	};

	class DirLight : public LightBase
	{
	public:
		glm::vec3 dir;
		glm::vec3 pos;
	};


}