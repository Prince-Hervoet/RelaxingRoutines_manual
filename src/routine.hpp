#pragma once
#include <cstddef>
typedef void *(*TaskFunc)(void *);

#define INIT 0
#define RUNNING 1
#define PENDING 2
#define STOP 3

class Scheduler;
namespace snr
{
    class Routine
    {
    private:
        size_t id;
        TaskFunc task;
        int status;
        void *taskArgs;
        Scheduler *sc;
        char *stack;

    public:
        Routine(size_t id, Scheduler *sc, TaskFunc task, void *args)
        {
            this->id = id;
            this->sc = sc;
            this->status = INIT;
            this->task = task;
            this->taskArgs = args;
        }

        size_t getId()
        {
            return id;
        }

        void setStatus(int status)
        {
            this->status = status;
        }
    };

};
