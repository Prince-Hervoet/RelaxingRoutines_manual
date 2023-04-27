#pragma once
#include <set>
#include <ucontext.h>
#include <chrono>
#include "routine_handler.hpp"
#include "loop_list.hpp"
#include "epoll_pack.hpp"
#include "delay_queue.hpp"

// running stack max size
#define RUNNING_SIZE 512288
// routine init size
#define INIT_STACK_SIZE 4096
// max routines
#define MAX_ROUTINE 128

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
    ~Controller()
    {
        if (running)
        {
            delete running;
        }
        if (ep)
        {
            delete ep;
        }
        if (dq)
        {
            delete dq;
        }
        for (auto it = routineHandlers.begin(); it != routineHandlers.end(); ++it)
        {
            RoutineHandler *rh = *it;
            delete rh;
        }
        routineHandlers.clear();
    }
    RoutineHandler *createRoutine(TaskFunc task, void *args);
    void pendRoutine();
    void resumeRouine(RoutineHandler *rh);
    void removeRoutine(RoutineHandler *rh);
    void addEpollEvent(int sockfd, int eventType);
    void removeEpollEvent(int sockfd);
    void addTimedTask(int sockfd, long long will);

    RoutineHandler *getRunning()
    {
        return running;
    }
    int getSize()
    {
        return size;
    }
};
