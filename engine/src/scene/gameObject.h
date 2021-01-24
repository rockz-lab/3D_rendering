#pragma once

#include "core/events.h"
#include "rendering/visualModel.h"

namespace grafik
{
	class GameObject : public eventNode
	{
	public:
		GameObject()
		{

		}

			
		void addVisual(const std::string& fileName)
		{
			// make new visual Model
			//VisualModel test(fileName);
			auto newPtr = std::shared_ptr<VisualModel>(new VisualModel(fileName));
			m_visualModel.push_back(newPtr);
		}


		
	private:
		std::vector<std::shared_ptr<VisualModel>> m_visualModel;
		// may or may not need a collidor
		// maybe add a behaviour
	};

}