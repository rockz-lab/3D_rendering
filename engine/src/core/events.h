#pragma once
#include "common.h"
#include "input.h"

// interface for the event system
// all objects that subscribe or publish events must derive from the respective base classes
// some Data can be passed

namespace grafik
{
    enum eventType
    {
        MOUSE_MOVE,
        WINDOW_CLOSE,

        KEY_PRESS,
        KEY_RELEASE,
        KEY_REPEAT
    };


    struct eventData
    {
        eventType type;
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

    class Listener
    {
    public:

        Listener() { }
        virtual ~Listener();

        virtual void onEvent() = 0;
        //template <typename T>
        virtual void onEvent(void* data) = 0;   // data can be anything

        //void subsribeTo(Publisher)
    };


    class Publisher
    {
    public:
        virtual ~Publisher()
        {
            listeners.clear();
        }
        void addListener(Listener* listener);

        // notify
        void publishEvent();

        void publishEvent(void* data);
    private:
        std::vector<Listener*> listeners;

    };


}


