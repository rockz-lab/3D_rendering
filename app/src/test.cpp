#include "test.h"

template<typename T>
constexpr auto get_event_type(T data) { return static_cast<grafik::eventData*>(data)->type; }

void testPoint::onEvent(void* data)
{
    switch (get_event_type(data))
    {
    case grafik::MOUSE_MOVE:
    {
        onMouseMove(data);
        break;
    }
    case grafik::KEY_PRESS:
    {
        grafik::keyPressData* eData = static_cast<grafik::keyPressData*>(data);

        if (eData->key == GLFW_KEY_ESCAPE)
        {
            std::cout << "espace key has been pressed!\n";
        }
        break;
    }
    
    case grafik::KEY_REPEAT:
    {
        grafik::keyPressData* eData = static_cast<grafik::keyPressData*>(data);

        if (eData->key == GLFW_KEY_ESCAPE)
        {
            std::cout << "espace key has been pressed!\n";
        }
        break;
    }
    case grafik::COLLISION:
    {
        collisionData* eData = static_cast<collisionData*>(data);
        std::cout << "ouch, collsion!\n";

        
        m_pos_x = eData->set_pos[0];
        m_pos_y = eData->set_pos[1];

        m_prevPos_x = m_pos_x;
        m_prevPos_y = m_pos_y;
        

        break;
    }
    }
}

void testPoint::onMouseMove(void* data)
{
    int x_new = (int) static_cast<grafik::mouseMovData*>(data)->x_new;
    int y_new = (int) static_cast<grafik::mouseMovData*>(data)->y_new;

    int x_diff;
    int y_diff;

    if (m_init)
    {
        x_diff = x_new - m_cursor_x_old;
        y_diff = y_new - m_cursor_y_old;
    }
    else
    {
        x_diff = 0;
        y_diff = 0;
    }
    m_init = true;

    m_cursor_x_old = x_new;
    m_cursor_y_old = y_new;


    m_pos_x += m_speed * (float)x_diff;
    m_pos_y += m_speed * (float)y_diff;
    
    m_prevPos_x = m_pos_x;
    m_prevPos_y = m_pos_y;

    printf("Mouse Movement: Position (%f, %f)\n", m_pos_x, m_pos_y);
}

void testPoint::onEvent()
{
    // empty
}


