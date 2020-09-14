#ifndef _EVENT_
#define _EVENT_ 1

#include <queue>
#include <stdint.h>
#include "EventSubscription.h"

class EventSubscription;

class Event {
    friend class EventSubscription;
    private:
    std::queue<EventSubscription*> Subscriptions;
    size_t SubscriptionSize;

    public:
    Event()
    {
        SubscriptionSize = 0;
    }

    void fire(void *data)
    {
        std::queue<EventSubscription*> copy = Subscriptions;
        while(!copy.empty())
        {
            EventSubscription* curr = copy.front();
            curr->fire(data);
        }
    }
};

#endif