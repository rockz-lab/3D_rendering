#include "application.h"
#include <memory>



namespace grafik
{
    Application::Application()
    {
        m_window = std::unique_ptr<Window>(new Window("title", 559, 559));
        
        m_scene = std::make_unique<Scene>();
        
        // subscribe to window
        m_window->addListener(this);


    }


    void Application::Run()
    {
        while (m_runApp)
        {
            Update();
        }
    }

    void Application::Update()
    {
        Color color(1, 0, 0);
        m_window->Clear(color);

        
        m_scene->Draw();
        m_window->Update();

    }

    void Application::onEvent(void *data)
    {
        switch (static_cast<eventData*>(data)->type)
        {
        case MOUSE_MOVE:
        {
            double x = static_cast<mouseMovData*>(data)->x_new;
            double y = static_cast<mouseMovData*>(data)->y_new;
            //printf("Mouse Movement: Position (%f, %f)\n", x, y);
            break;
        }
        case WINDOW_CLOSE:
        {
            m_runApp = false;
            printf("Closing App\n");
            break;
        }
        }
       
    }

    void Application::onEvent()
    {
        printf("event registered!\n");
    }
}
