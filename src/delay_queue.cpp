#include "delay_queue.hpp"

extern long long getNowTimestamp();

template <typename T>
T *DelayQueue<T>::peek()
{
    if (this->minHeap.size == 0)
    {
        return nullptr;
    }
    TimerTask *tt = minHeap.top();
    return &((T)(tt->data));
}

template <typename T>
T *DelayQueue<T>::poll()
{
    if (this->minHeap.size == 0)
    {
        return nullptr;
    }
    TimerTask *tt = minHeap.pop();
    return &((T)(tt->data));
}

template <typename T>
int DelayQueue<T>::push(T &t, long long will)
{
    if (this->minHeap.size == limit)
    {
        return -1;
    }
    TimerTask *tt = new TimerTask();
    tt->data = (void *)t;
    tt->lastUpdateAt = getNowTimestamp() + will;
    minHeap.push(tt);
    return 1;
}

template <typename T>
void DelayQueue<T>::pollMany(T *t[], int count)
{
    long long now = getNowTimestamp();
    int run = 0;
    while (minHeap.size() > 0)
    {
        if (now < minHeap.top()->lastUpdateAt)
        {
            break;
        }
        if (run == count)
        {
            break;
        }
        TimerTask *tt = minHeap.pop();
        t[run] = tt;
        ++run;
    }
}