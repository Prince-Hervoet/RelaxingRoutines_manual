#pragma once
#include <cstdio>

namespace snr
{
    class ThreadPool
    {
    private:
        size_t maxQueueSize;
        int coreThreadSize;
        int maxThreadSize;
        int currentThread;
        };
};