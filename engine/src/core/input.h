#pragma once

#include "GLFW/glfw3.h"
#include "events.h"

namespace grafik
{
	enum Key
	{
		KEY_ESCAPE = 1
	};

	struct mouseMovData : public eventData
    {
        mouseMovData() : eventData()
        {
            type = MOUSE_MOVE;
            x_new = 0;
            y_new = 0;
        }

        float x_new;
        float y_new;
    };

    struct keyPressData : public eventData
    {
        keyPressData() : eventData()
        {
            type = KEY_PRESS;
        }
        int key;

    };
    
	/*Key get_Key(int scanCode)
	{

	}*/
	
}