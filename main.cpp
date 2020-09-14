#include <iostream>
#include "Event.h"
#include "EventSubscription.h"

using namespace std;

void callMe(void *context, void *data) {
    cout << (*(int*)data) << endl;
};

int main(int argc, char **argv){
    Event e;
    EventSubscription Sub((void*)0, callMe);
    Sub.Subscribe(&e);
    int data = 5;
    e.fire(&data);
}