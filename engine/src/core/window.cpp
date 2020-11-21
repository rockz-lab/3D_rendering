#include "window.h"

#include "utils/log_errs.h"


namespace grafik
{
    void cursorCB(GLFWwindow* win, double xNew, double yNew)
    {
        void* winUserPointer = glfwGetWindowUserPointer(win);

        eventData data;
        data.type = MOUSE_MOVE;
        data.xNew = xNew;
        data.yNew = yNew;

        static_cast<Window*>(winUserPointer)->publishEvent(&data);
    }

    Window::Window(const std::string& title, int width, int height) : m_width(width), m_height(height)
    {
        glfwInit();

        glfwSetErrorCallback(error_callback);

        m_window = glfwCreateWindow(m_width, m_height, title.c_str(), NULL, NULL);


        if (glfwRawMouseMotionSupported())
            glfwSetInputMode(m_window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
        glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        glfwSetWindowUserPointer(m_window, this);

        // callbacks
        glfwSetCursorPosCallback(m_window, cursorCB);
        //glfwSetWindowCloseCallback()

        glfwMakeContextCurrent(m_window);

    }

    void Window::Update()
    {
        glfwSwapBuffers(m_window);
        glfwWaitEvents(); // wait events?
        double x, y;
        glfwGetCursorPos(m_window, &x, &y);

        std::cout << x << " \t" << y << "\n";
    }

    void Window::Clear(const Color& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    }

}


