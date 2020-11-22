#pragma once

#include "common.h"
#include "window.h"

namespace grafik
{
    class grafikAPI Application : public Listener
    {
    public:
        Application();

        void Run();

        void onEvent() override;
        void onEvent(void* data) override;

        void addWinListener();
    protected:
        void Update();
        std::unique_ptr<Window> m_window;
        bool m_runApp = true;
    };
}



