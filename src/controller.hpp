#pragma once
#include <set>
#include <ucontext.h>
#include "routine_handler.hpp"
#include "loop_list.hpp"
#include "epoll_pack.hpp"
#include "delay_queue.hpp"

// running stack max size
#define RUNNING_SIZE 512288
// routine init size
#define INIT_STACK_SIZE 4096
// max routines
#define MAX_ROUTINE 64

// class RoutineHandler;

typedef struct
{
    RoutineHandler *rh;
    CallbackFunc cf;
} RoutineEvent;

struct HandlerComparator
{
    bool operator()(const RoutineHandler *a, const RoutineHandler *b) const
    {
        return a > b; // 降序排序
    }
};

// the controller of a thread

class Controller
{
    friend void threadFunc(void *args);

private:
    char runningStack[RUNNING_SIZE];
    std::set<RoutineHandler *, HandlerComparator> routineHandlers;
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
    void removeRoutine(RoutineHandler *rh);
    void addEpollEvent(int sockfd, int eventType);
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
