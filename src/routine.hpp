#pragma once
#include "util.hpp"
typedef void *(*TaskFunc)(void *);
#define INIT 0
#define READY 1
#define RUNNING 2
#define PENDING 3
#define DEAD 4

class Controller;
class RoutineProcess
{
public:
    unsigned long long id;
    TaskFunc task;
    void *args;
    char *save;
    Controller *con;
    ucontext_t current;
    int status = INIT;
    int saveSize = 0;
    int capSize = 0;

public:
    RoutineProcess(unsigned long long id, TaskFunc task, void *args)
    {
        this->id = id;
        this->task = task;
        this->args = args;
    }

    ~RoutineProcess()
    {
        if (save)
        {
            delete[] save;
        }
    }
};

// class RoutineHandler
// {
//     friend RoutineHandler *simple_new(TaskFunc task, void *args);
//     friend int simple_resume(RoutineProcess *routine);
//     friend void simple_await();
//     friend void t_simple_pause();
//     friend class Controller;
//     friend void threadFunc(void *args);

// public:
//     RoutineHandler()
//     {
//     }
//     RoutineHandler(RoutineProcess *pro, RoutineHandler *father)
//     {
//         routine = pro;
//     }

//     ~RoutineHandler()
//     {
//         delete routine;
//     }

// private:
//     RoutineHandler *father;
//     RoutineProcess *routine;
// };
