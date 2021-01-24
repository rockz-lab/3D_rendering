#include "events.h"


namespace grafik
{

    void eventNode::addListener(eventNode* listener)
    {
        listeners.push_back(listener);
    }

    void eventNode::publishEvent()
    {
        for (auto& l : listeners)
        {
            l->onEvent();
        }
    }

    void eventNode::publishEvent(void* data)
    {
        for (auto& l : listeners)
        {
            l->onEvent(data);
        }
    }

}