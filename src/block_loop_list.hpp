#pragma once
#include <mutex>
#include <condition_variable>
#include <chrono>

template <typename T>
class LoopList
{
private:
    int head = 0, tail = 0;
    int size = 0;
    int limit = 0;
    std::mutex mu;
    std::condition_variable cond;
    T *ts;

public:
    LoopList()
    {
    }

    LoopList(int limit)
    {
        this->limit = limit;
        this->ts = new T[limit];
    }

    ~LoopList()
    {
        if (ts)
        {
            delete[] ts;
        }
    }

    int add(T &data, int waitTime)
    {
        mu.lock();
        while (size == limit)
        {
            if (waitTime < 0)
            {
                cond.wait();
                continue;
            }
            else if (waitTime > 0)
            {
                cond.wait_for(mu, std::chrono::milliseconds(waitTime));
                if (size > 0)
                {
                    break;
                }
            }
            mu.unlock();
            return -1;
        }
        ts[tail] = data;
        ++tail;
        ++size;
        tail = tail == limit ? 0 : tail;
        cond.notify_all();
        mu.unlock();
        return 1;
    }

    T *poll(int waitTime)
    {
        mu.lock();
        while (size == 0)
        {
            if (waitTime < 0)
            {
                cond.wait();
                continue;
            }
            else if (waitTime > 0)
            {
                cond.wait_for(mu, std::chrono::milliseconds(waitTime));
                if (size > 0)
                {
                    break;
                }
            }
            mu.unlock();
            return nullptr;
        }
        T *ans = &ts[head];
        --size;
        ++head;
        head = head == limit ? 0 : head;
        cond.notify_all();
        mu.unlock();
        return ans;
    }

    int getSize()
    {
        return this->size;
    }
};