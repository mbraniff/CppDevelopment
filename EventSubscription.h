#ifndef _EVENTSUBSCRIPTION_
#define _EVENTSUBSCRIPTION_ 1

#include "Event.h"
#include <queue>

class Event;

class EventSubscription {
    friend class Event;
    public:
    typedef void(*callback)(void *context, void *data);

    private:
    void *Context;
    callback Callback;
    void fire(void *data)
    {
        Callback(Context, data);
    }

    public:
    EventSubscription(void *context, callback _callback)
    {
        Context = context;
        Callback = _callback;
    }

    void Subscribe(Event* e)
    {
        e->Subscriptions.push(this);
    }
};

#endif