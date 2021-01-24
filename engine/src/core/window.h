#pragma once

#include "common.h"
#include "events.h"
#include "input.h"

#include "GLFW/glfw3.h"


namespace grafik
{
    class Window : public eventNode
    {
    public:
        Window(const std::string& title, int width, int height);
        ~Window() {};
        void Update();
        void Clear(const Color& color);
        void SwitchCursorMode();
        void SwitchFullscreen();
        void setWinSize(int& width, int& height);
    private:
        int m_width;
        int m_height;
        int m_pos[2];

        bool m_isFullScreen = false;

        GLFWwindow* m_window;

    };

}


