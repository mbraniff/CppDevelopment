#include <iostream>
#include <thread>
#include <chrono>
#include "Event.h"
#include "EventSubscription.h"
#include "FunctionQueue.h"

using namespace std;

void callMe(void *context, void *data) {
    cout << *(int*)data << endl;
};

void add(void *context)
{
    typedef struct{
        int data;
        Event* event;
    }param;

    param* params = (param*)context;
    params->data += 1;
    params->event->fire(&params->data);
}

void wait_call(FunctionQueue *fq, void *context)
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    fq->push_one_shot(add, context);
    wait_call(fq, context);
}

int main(int argc, char **argv){
    Event e;
    EventSubscription Sub((void*)0, callMe);
    struct{
        int data;
        Event* event;
    }param;
    FunctionQueue functionQueue;
    e.subscribe(&Sub);

    std::thread time(wait_call, &functionQueue, &param);

    param.event = &e;
    param.data = 0;
    functionQueue.push_one_shot(add, &param);
    functionQueue.main();
    return 0;
}