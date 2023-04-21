#include "thread.hpp"

void snr::Thread::start()
{
    if (isStart || !func)
    {
        return;
    }
    snr::ThreadDataPack *data = new snr::ThreadDataPack;
    data->thread = this;
    data->userArgs = args;
    std::thread tl(func, data);
    this->id = tl.get_id();
    tl.detach();
}