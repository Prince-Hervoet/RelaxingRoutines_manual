#include "controller.hpp"
#include "routine_handler.hpp"
#include <cstring>
#include <iostream>

thread_local Controller localCon;

void threadFunc(void *args)
{
    RoutineHandler *rh = localCon.running;
    rh->routine->task(rh->routine->args);
    delete rh;
}

void callback(void *args)
{
    RoutineHandler *rh = (RoutineHandler *)args;
    simple_resume(rh);
}

RoutineHandler *Controller::createRoutine(TaskFunc task, void *args)
{
    RoutineProcess *pro = new RoutineProcess(this->increment, task, args);
    pro->save = new char[INIT_STACK_SIZE];
    pro->saveSize = 0;
    pro->capSize = INIT_STACK_SIZE;
    RoutineHandler *rh = new RoutineHandler(pro, this->running);
    // this->loopList.add(*rh);
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
    if (pro->capSize < needSize)
    {
        delete[] pro->save;
        pro->capSize = needSize;
        pro->save = new char[needSize];
    }
    pro->saveSize = needSize;
    memcpy(pro->save, &flag, needSize);
    pro->status = PENDING;

    // 这里后续需要考虑父协程在子协程还没恢复的时候就挂了
    RoutineHandler *father = this->running->father;
    if (father)
    {
        father->routine->status = RUNNING;
    }
    std::cout << "222asdfasdf222" << std::endl;
    this->running = this->running->father;
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
        // std::cout << "asdf" << std::endl;
        break;
    case PENDING:
        break;
    default:
        return;
    }

    pro->status = RUNNING;
    if (running)
    {
        running->routine->status = READY;
    }

    this->running = rh;
    swapcontext(prevCtx, &pro->current);
}

Controller::Controller(int limit)
{
    this->limit = limit;
    this->loopList = LoopList<RoutineHandler>(MAX_ROUTINE);
}

void Controller::addEpollEvent(int sockfd, int eventType)
{
    if (!this->ep)
    {
        this->ep = new EpollPack();
        this->ep->setEpoll();
    }
    RoutineEvent *re = new RoutineEvent();
    re->rh = this->running;
    re->cf = callback;
    this->ep->setEvent(EPOLL_CTL_ADD, eventType, sockfd, (void *)re);
}