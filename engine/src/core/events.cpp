#include "events.h"


grafik::Listener::~Listener() { }

void grafik::Publisher::addListener(grafik::Listener *listener)
{
    listeners.push_back(std::unique_ptr<Listener>(listener));
}

void grafik::Publisher::publishEvent()
{
    for (auto& l : listeners)
    {
        l->onEvent();
    }
}

void grafik::Publisher::publishEvent(void* data)
{
    for (auto& l : listeners)
    {
        l->onEvent(data);
    }
}

