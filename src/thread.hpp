#include <thread>
#include "schedule.hpp"

typedef void (*ThreadFunc)(void *);

namespace snr
{
    class Thread
    {
    private:
        std::thread::id id;
        ThreadFunc func;
        void *args;
        Scheduler sc;
        bool isStart = false;

    public:
        Thread(ThreadFunc func, void *args)
        {
            this->func = func;
            this->args = args;
            sc = Scheduler();
        }

        std::thread::id getId()
        {
            return id;
        }

        void start();
        void stop();
        void giveTask();
    };

    struct ThreadDataPack
    {
        void *userArgs;
        Thread *thread;
    };
};
