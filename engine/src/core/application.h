#pragma once

#include "common.h"
#include "window.h"

#include "scene/scene.h"

namespace grafik
{
    class grafikAPI Application : public eventNode
    {
    public:
        Application();

        void Run();

        void onEvent() override;
        void onEvent(void* data) override;

        //void addWinListener();
    protected:
        
        void Update();

        std::unique_ptr<Window> m_window;
        std::unique_ptr<Scene> m_scene;

        bool m_runApp = true;
    };
}



