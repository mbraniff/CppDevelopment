#ifndef _EVENTSUBSCRIPTION_H_
#define _EVENTSUBSCRIPTION_H_ 1

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

};

#endif