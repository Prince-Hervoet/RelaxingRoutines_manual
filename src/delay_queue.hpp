#pragma once
#include "util.hpp"
#include <vector>
#include <queue>
#include <chrono>

typedef struct
{
    void *data;
    long long lastUpdateAt;
    bool operator<(const TimerTask &other) const
    {                                             // 重载小于运算符
        return lastUpdateAt > other.lastUpdateAt; // 按照分数从大到小排序
    }
} TimerTask;

template <typename T>
class DelayQueue
{
private:
    int limit = 0;
    std::priority_queue<TimerTask *> minHeap;

public:
    int getSize()
    {
        return minHeap.size();
    }

    int push(T &t, long long timestamp);

    T *peek();

    T *poll();

    void pollMany(T *t[], int count);
};