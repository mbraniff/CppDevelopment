#ifndef _FUNCTIONQUEUE_H_
#define _FUNCTIONQUEUE_H_

#include <vector>
#include <iostream>

typedef void *params;
typedef void(*function)(params context);

class FunctionQueue
{
    private:
    std::vector<std::pair<function,params>> OneShot;
    std::vector<std::pair<function,params>> Persistent;

    public:
    FunctionQueue()
    {
    }

    void push_persistent(function f, params p)
    {
        Persistent.push_back({f,p});
    }

    void push_one_shot(function f, params p)
    {
        OneShot.push_back({f,p});
    }

    void main()
    {
        while(1)
        {
            static long int counter = 0;
            if(!OneShot.empty())
            {
                auto call = OneShot.back();
                call.first(call.second);
                OneShot.pop_back();
            }
            else if (!Persistent.empty())
            {
                auto call = Persistent.at(counter);
                counter++;
                call.first(call.second);
            }
            if(counter == Persistent.size())
            {
                counter = 0;
            }
        }
    }
};

#endif