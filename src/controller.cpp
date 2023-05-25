#include "controller.hpp"
#include <cstring>
#include <thread>

thread_local Controller localCon;

void threadFunc(void *args)
{
    RoutineHandler *rh = localCon.running;
    if (rh && rh->routine)
    {
        try
        {
            rh->routine->task(rh->routine->args);
        }
        catch (const char *msg)
        {
            std::cout << msg << std::endl;
        }
        localCon.removeRoutine(rh);
    }
}

void callback(void *args)
{
    RoutineHandler *rh = (RoutineHandler *)args;
    simple_resume(rh);
}

RoutineHandler *Controller::createRoutine(TaskFunc task, void *args)
{
    RoutineProcess *pro = new RoutineProcess(this->increment, task, args);

    /*
        the parent of this routine is nullptr,
        because only the routine that started this routine is its parent,
        not the coroutine that created it.
    */
    RoutineHandler *rh = new RoutineHandler(pro, nullptr);
    this->routineHandlers.insert(rh);
    this->increment += 1;
    return rh;
}

void Controller::pendRoutine()
{
    char flag = 0;
    if (!this->running)
    {
        return;
    }
    RoutineProcess *pro = this->running->routine;
    int needSize = this->runningStack + RUNNING_SIZE - &flag;
    if (!pro->save)
    {
        int needSizeBigger = needSize + 16;
        pro->save = new char[needSizeBigger];
        pro->saveSize = 0;
        pro->capSize = needSizeBigger;
    }
    else if (pro->capSize < needSize)
    {
        delete[] pro->save;
        pro->capSize = needSize;
        pro->save = new char[needSize];
    }
    pro->saveSize = needSize;
    memcpy(pro->save, &flag, needSize);
    pro->status = PENDING;
    this->routineHandlers.erase(this->running);

    /*
        When the current routine is pended, you go back to the routine where you started it.
    */
    RoutineHandler *father = this->running->parent;

    /*
        If its parent is empty, the main corroutine started it.
    */
    if (father)
    {
        father->routine->status = RUNNING;
    }
    this->running = this->running->parent;
    swapcontext(&pro->current, pro->current.uc_link);
}

void Controller::resumeRouine(RoutineHandler *rh)
{

    RoutineProcess *pro = rh->routine;
    RoutineHandler *running = this->running;
    ucontext_t *prevCtx = running == nullptr ? &this->host : &(running->routine->current);
    switch (pro->status)
    {
    case INIT:
        getcontext(&pro->current);
        pro->current.uc_stack.ss_sp = this->runningStack;
        pro->current.uc_stack.ss_size = RUNNING_SIZE;
        pro->current.uc_link = prevCtx;
        makecontext(&pro->current, (void (*)(void))threadFunc, 0);
        break;
    case PENDING:
        break;
    default:
        return;
    }

    /*
        The running routine is its parent.
    */
    rh->parent = running;
    pro->status = RUNNING;

    /*
        If the running routine isn't the main routine,it will be pending.
        The main routine hasn't its status.(It is always running..)
    */
    if (running)
    {
        running->routine->status = PENDING;
    }
    this->running = rh;
    swapcontext(prevCtx, &pro->current);
}

void Controller::removeRoutine(RoutineHandler *rh)
{
    this->routineHandlers.erase(rh);
    delete rh;
}

Controller::Controller(int limit)
{
    this->limit = limit;
}

void Controller::addEpollEvent(int sockfd, int eventType)
{
    if (!this->ep)
    {
        this->ep = new EpollPack();
        this->ep->setEpoll();
    }
    if (this->running)
    {
        this->ep->setEvent(EPOLL_CTL_ADD, eventType, sockfd, (void *)(this->running));
    }
}

void Controller::removeEpollEvent(int sockfd)
{
    if (!this->ep)
    {
        return;
    }
    this->ep->removeEvent(sockfd);
}

void Controller::addTimedTask(int sockfd, long long will)
{
    if (!this->dq)
    {
        this->dq = new DelayQueue<RoutineHandler *>();
    }
    if (this->running)
    {
        dq->push(this->running, will);
    }
}