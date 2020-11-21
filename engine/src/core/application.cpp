#include "application.h"



namespace grafik
{
    Application::Application()
    {
        m_window = std::make_unique<Window>("title", 559, 559);

        // subscribe to window

        m_window->addListener(this);
    }


    void Application::Run()
    {
        while (true)
        {
            Update();


        }
    }

    void Application::Update()
    {

        m_window->Update();

        Color color(1, 0, 0);

        m_window->Clear(color);
    }

    void Application::onEvent(void *data)
    {
        double x = static_cast<eventData*>(data)->xNew;
        double y = static_cast<eventData*>(data)->yNew;

        printf("Mouse Movement: Position (%f, %f)\n", x, y);
    }

    void Application::onEvent()
    {
        printf("event registered!\n");
    }
}
