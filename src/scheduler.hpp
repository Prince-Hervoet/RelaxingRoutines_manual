#pragma once
#include "loop_list.hpp"
#include "routine.hpp"
#include <thread>

#define MAX_ROUTINE_SIZE 64
namespace snr
{
    class Scheduler
    {
    private:
        LoopList<snr::Routine> looplist;
        snr::Routine *running;
        int limit = 0;

    public:
        Scheduler()
        {
            looplist = LoopList<snr::Routine>(64);
        }

        int getSize()
        {
            return looplist.getSize();
        }

        int createRoutine(TaskFunc task, void *args);

        int runRoutine();

        int pendRoutine();
    };
}
