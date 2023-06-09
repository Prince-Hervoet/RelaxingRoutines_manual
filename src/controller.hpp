#pragma once
#include <set>
#include <ucontext.h>
#include <chrono>
#include "routine_handler.hpp"
#include "block_loop_list.hpp"
#include "epoll_pack.hpp"
#include "delay_queue.hpp"

// running stack max size
#define RUNNING_SIZE 512288
// routine init size
#define INIT_STACK_SIZE 4096
// max routines
#define MAX_ROUTINE 128

// the controller of a thread
class Controller
{
    friend void threadFunc(void *args);

private:
    // running stack: it is opened in the thread
    char runningStack[RUNNING_SIZE];

    // routines,why set?
    /*
        We're not sure if we're going to use id maps or something else,
        so we're going to use a collection, so we can just grab it.
    */
    std::set<RoutineHandler *> routineHandlers;
    unsigned long long increment;
    RoutineHandler *running;
    // epoll event list
    EpollPack *ep;
    // timer task list
    DelayQueue<RoutineHandler> *dq;
    // this context of the main routine
    ucontext_t host;

public:
    ~Controller();
    RoutineHandler *createRoutine(TaskFunc task, void *args);
    void pendRoutine();
    void resumeRouine(RoutineHandler *rh);
    void removeRoutine(RoutineHandler *rh);
    void addEpollEvent(int sockfd, int eventType);
    void removeEpollEvent(int sockfd);
    struct epoll_event *waitEpollEvent();
    void addTimedTask(int sockfd, long long will);
    RoutineHandler *waitTimedTask();

    Controller() {}

    RoutineHandler *getRunning()
    {
        return running;
    }

    int getSize()
    {
        return routineHandlers.size();
    }
};
