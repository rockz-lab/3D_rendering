#include "test.h"


void Test::onEvent(void* data)
{
    switch (static_cast<grafik::eventData*>(data)->type)
    {
    case grafik::MOUSE_MOVE:
    {
        int x_new = (int) static_cast<grafik::mouseMovData*>(data)->x_new;
        int y_new = (int) static_cast<grafik::mouseMovData*>(data)->y_new;

        int x_diff;
        int y_diff;

        if (m_init)
        {
            x_diff = x_new - m_x_old;
            y_diff = y_new - m_y_old;
        }
        else
        {
            x_diff = 0;
            y_diff = 0;
        }
        m_init = true;

        m_x_old = x_new;
        m_y_old = y_new;

        m_pos_x += (float) x_diff;
        m_pos_y += (float) y_diff;

        printf("Mouse Movement: Position (%f, %f)\n", m_pos_x, m_pos_y);
        break;
    }
    case grafik::KEY_PRESS:
    {
        grafik::keyPressData* eventData = static_cast<grafik::keyPressData*>(data);

        if (eventData->key == GLFW_KEY_ESCAPE)
        {
            std::cout << "espace key has been pressed!\n";
        }
        break;
    }
    
    case grafik::KEY_REPEAT:
    {
        grafik::keyPressData* eventData = static_cast<grafik::keyPressData*>(data);

        if (eventData->key == GLFW_KEY_ESCAPE)
        {
            std::cout << "espace key has been pressed!\n";
        }
        break;
    }
    }
}

void Test::onEvent()
{
}

