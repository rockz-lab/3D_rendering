#pragma once

#include "common.h"
#include "events.h"

#include "GLFW/glfw3.h"


namespace grafik
{
    class Window : public Publisher
    {
    public:
        Window(const std::string& title, int width, int height);

        void Update();
        void Clear(const Color& color);
    private:
        int m_width;
        int m_height;

        GLFWwindow* m_window;


    };

}


