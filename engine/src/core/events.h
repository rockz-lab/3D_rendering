#pragma once
#include "common.h"

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
        KEY_REPEAT,

        COLLISION
    };


    struct eventData
    {
        eventType type;
    };


    class eventNode
    {
    public:
        eventNode() {}
        virtual ~eventNode()
        {
            listeners.clear();
        }
        //template <typename T>
        void addListener(eventNode* listener);

        // notify
        void publishEvent();

        void publishEvent(void* data);

        virtual void onEvent() { };
        virtual void onEvent(void* data) { };   // data can be anything
    private:
        std::vector<eventNode*> listeners;

    };


    /*struct collisionData : public eventData
    {
        collisionData() : eventData()
        {
            type = COLLISION;
        }

        float set_pos[2];
        float pos[2];
    }*/;
}


