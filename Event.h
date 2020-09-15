#ifndef _EVENT_H_
#define _EVENT_H_ 1

#include <vector>
#include "EventSubscription.h"

class Event {
    private:
    std::vector<EventSubscription*> Subscriptions;

    public:
    Event()
    {
    }

    void subscribe(EventSubscription *sub)
    {
        Subscriptions.push_back(sub);
    }

    void unsubscribe(EventSubscription *sub)
    {
        int i = 0;
        for(auto s: Subscriptions)
        {
            if(s == sub)
            {
                Subscriptions.erase(Subscriptions.begin()+i);
            }
            i++;
        }
    }

    void fire(void *data)
    {
        for(auto s: Subscriptions)
        {
            s->fire(data);
        }
    }
};

#endif