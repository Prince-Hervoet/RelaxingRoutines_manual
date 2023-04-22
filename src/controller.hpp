#pragma once
#include "routine.hpp"
#include "loop_list.hpp"
#include "epoll_pack.hpp"
#include "delay_queue.hpp"

// running stack max size
#define RUNNING_SIZE 512288
// routine init size
#define INIT_STACK_SIZE 4096
// max routines
#define MAX_ROUTINE 64

class RoutineHandler;

typedef struct
{
    RoutineHandler *rh;
    CallbackFunc cf;
    void *args;
} RoutineEvent;

// the controller of a thread

class Controller
{
    friend void threadFunc(void *args);

private:
    // running stack
    char runningStack[RUNNING_SIZE];
    // save routines
    LoopList<RoutineHandler> loopList;
    unsigned long long increment;
    RoutineHandler *running;
    EpollPack *ep;
    DelayQueue<RoutineEvent> *dq;
    ucontext_t host;
    int size = 0;
    int limit = 0;

public:
    Controller() {}
    Controller(int limit);
    RoutineHandler *createRoutine(TaskFunc task, void *args);
    void pendRoutine();
    void resumeRouine(RoutineHandler *rh);
    void addEpollEvent();
    void addTimedTask();

    RoutineHandler *getRunning()
    {
        return running;
    }
    int getSize()
    {
        return size;
    }
};
