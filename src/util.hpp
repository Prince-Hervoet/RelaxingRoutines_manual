#include <thread>
#include "scheduler.hpp"

thread_local Scheduler localSc;

class RoutineHandler;

RoutineHandler *simple_new(TaskFunc task, void *args)
{
}

int simple_resume(snr::Routine *routine)
{
}

void simple_await()
{
}

void t_simple_pause()
{
}

class RoutineHandler
{
    friend RoutineHandler *simple_new(TaskFunc task, void *args);
    friend int simple_resume(snr::Routine *routine);
    friend void simple_await();
    friend void t_simple_pause();

private:
    snr::Routine *routine;
};