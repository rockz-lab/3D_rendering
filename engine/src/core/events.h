#pragma once
#include "common.h"

// interface for the event system
// all objects that subscribe or publish events must derive from the respective base classes
// some Data can be passed

namespace grafik
{
    enum eventType
    {
        MOUSE_MOVE
    };

    struct eventData
    {
        eventType type;
        double xNew, yNew;
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
        void addListener(Listener* listener);

        // notify
        void publishEvent();

        void publishEvent(void* data);
    private:
        std::vector<std::unique_ptr<Listener>> listeners;

    };


}


