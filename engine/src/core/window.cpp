#include "window.h"

#include "utils/log_errs.h"


namespace grafik
{
    void cursorCB(GLFWwindow* win, double xNew, double yNew);
    void closeCB(GLFWwindow* win);
    void keyCB(GLFWwindow* win, int key, int scancode, int action, int mods);

    Window::Window(const std::string& title, int width, int height) : m_width(width), m_height(height)
    {
        // init glfw
        glfwInit();
        // error handling
        glfwSetErrorCallback(error_callback);

        // create window
        m_window = glfwCreateWindow(m_width, m_height, title.c_str(), NULL, NULL);

        glfwGetWindowPos(m_window, &m_pos[0], &m_pos[1]);

       if (glfwRawMouseMotionSupported())
            glfwSetInputMode(m_window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

        
        // user pointer we set to out window
        glfwSetWindowUserPointer(m_window, this);

        // callbacks
        glfwSetCursorPosCallback(m_window, cursorCB);
        glfwSetWindowCloseCallback(m_window, closeCB);
        glfwSetKeyCallback(m_window, keyCB);

        // set rendering context -> OpenGL calls will draw into this window
        glfwMakeContextCurrent(m_window);

        glfwSwapInterval(1);        // vsync on
    }

    void Window::Update()
    {
        glfwSwapBuffers(m_window);
        glfwWaitEvents(); // wait events?
        double x, y;
        glfwGetCursorPos(m_window, &x, &y);
    }

    void Window::Clear(const Color& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    }

    void Window::SwitchCursorMode()
    {
        int cursorMode = glfwGetInputMode(m_window, GLFW_CURSOR);
        if (cursorMode == GLFW_CURSOR_NORMAL)
            glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        else if (cursorMode == GLFW_CURSOR_DISABLED)
            glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    void Window::SwitchFullscreen()
    {
        if (m_isFullScreen) // switch from fullscreen
        {   // reset back to previous position
            glfwSetWindowMonitor(m_window, nullptr, m_pos[0], m_pos[1], m_width, m_height, 0);
            m_isFullScreen = !m_isFullScreen;
        }
        else    // switch to fulscreen
        {
            glfwGetWindowPos(m_window, &m_pos[0], &m_pos[1]);       // save last window pos
            glfwGetWindowSize(m_window, &m_width, &m_height);
            const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

            glfwSetWindowMonitor(m_window, glfwGetPrimaryMonitor(), 0, 0, mode->width, mode->height, mode->refreshRate);
            m_isFullScreen = !m_isFullScreen;
        }
    }
   
    void Window::setWinSize(int& width, int& height)
    {
        m_width = width;
        m_height = height;
    }

    void cursorCB(GLFWwindow* win, double xNew, double yNew)
    {
        void* winUserPointer = glfwGetWindowUserPointer(win);

        mouseMovData data;
        data.type = MOUSE_MOVE;
        data.x_new = xNew;
        data.y_new = yNew;

        static_cast<Window*>(winUserPointer)->publishEvent(&data);
    }


    void keyCB(GLFWwindow* win, int key, int scancode, int action, int mods)
    {
        void* winUserPointer = glfwGetWindowUserPointer(win);
        Window* windowPtr = static_cast<Window*>(winUserPointer);

        if (action == GLFW_PRESS)
        {
            keyPressData data;
            data.type = KEY_PRESS;

            data.key = key;

            windowPtr->publishEvent(&data);

            // set window mode
            if (key == GLFW_KEY_ESCAPE)
                windowPtr->SwitchCursorMode();

            if (key == GLFW_KEY_F11)
                windowPtr->SwitchFullscreen();
        }

        if (action == GLFW_RELEASE)
        {
            keyPressData data;
            data.type = KEY_RELEASE;

            data.key = key;

            windowPtr->publishEvent(&data);
        }

        if (action == GLFW_REPEAT)
        {
            keyPressData data;
            data.type = KEY_REPEAT;

            data.key = key;

            windowPtr->publishEvent(&data);
        }
    }

    void closeCB(GLFWwindow* win)
    {
        void* winUserPointer = glfwGetWindowUserPointer(win);

        eventData data;
        data.type = WINDOW_CLOSE;
        static_cast<Window*>(winUserPointer)->publishEvent(&data);
    }

    void resizeCB(GLFWwindow* win, int width, int height)
    {
        void* winUserPointer = glfwGetWindowUserPointer(win);

        static_cast<Window*>(winUserPointer)->setWinSize(width, height);
    }
}


