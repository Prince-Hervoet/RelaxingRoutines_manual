#include "routine.hpp"

/*
    this class...emm
    is a handle to a real routine structure
*/
class RoutineHandler
{
    friend RoutineHandler *simple_new(TaskFunc task, void *args);
    friend void simple_resume(RoutineHandler *rh);
    friend void simple_await();
    friend void threadFunc(void *args);
    friend class Controller;

public:
    RoutineHandler() {}

    RoutineHandler(RoutineProcess *pro, RoutineHandler *father)
    {
        routine = pro;
    }

    ~RoutineHandler()
    {
        if (routine)
        {
            delete routine;
        }
    }

private:
    RoutineHandler *parent;
    RoutineProcess *routine;
};
