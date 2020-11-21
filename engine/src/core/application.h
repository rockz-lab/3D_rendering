#pragma once

#include "common.h"
#include "window.h"

namespace grafik
{
    class Application : public Listener
    {
    public:
        Application();

        //virtual ~Application() {}

        void Run();

        void onEvent() override;
        void onEvent(void* data) override;

    private:
        void Update();
        std::unique_ptr<Window> m_window;
    };
}



