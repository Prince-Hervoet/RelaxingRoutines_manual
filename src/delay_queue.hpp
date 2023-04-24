#pragma once
#include "util.hpp"
#include <vector>
#include <queue>
#include <chrono>
long long getNowTimestamp();

template <typename T>
struct TimerTask
{
    T *data;
    long long lastUpdateAt;
    bool operator<(const struct TimerTask<T> &other) const
    {                                             // 重载小于运算符
        return lastUpdateAt > other.lastUpdateAt; // 按照分数从大到小排序
    }
};

template <typename T>
class DelayQueue
{
private:
    int limit = 2000;
    std::priority_queue<struct TimerTask<T> *> minHeap;

public:
    DelayQueue()
    {
    }

    ~DelayQueue()
    {
        while (minHeap.size() > 0)
        {
            TimerTask<T> *tt = minHeap.top();
            minHeap.pop();
            if (tt)
            {
                delete tt;
            }
        }
    }

    int getSize()
    {
        return minHeap.size();
    }

    int push(T &t, long long will);

    T *peek();

    T *poll();

    int pollMany(T *t[], int count);
};

template <typename T>
T *DelayQueue<T>::peek()
{
    if (this->minHeap.size() == 0)
    {
        return nullptr;
    }
    struct TimerTask<T> *tt = minHeap.top();
    return (tt->data);
}

template <typename T>
T *DelayQueue<T>::poll()
{
    if (this->minHeap.size() == 0)
    {
        return nullptr;
    }
    struct TimerTask<T> *tt = minHeap.pop();
    T *data = tt->data;
    delete tt;
    return data;
}

template <typename T>
int DelayQueue<T>::push(T &t, long long will)
{
    if (this->minHeap.size() == limit)
    {
        return -1;
    }
    struct TimerTask<T> *tt = new struct TimerTask<T>();
    tt->data = &t;
    tt->lastUpdateAt = getNowTimestamp() + will;
    minHeap.push(tt);
    return 1;
}

template <typename T>
int DelayQueue<T>::pollMany(T *t[], int count)
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
        struct TimerTask<T> *tt = minHeap.pop();
        t[run] = tt->data;
        delete tt;
        ++run;
    }
    return run;
}