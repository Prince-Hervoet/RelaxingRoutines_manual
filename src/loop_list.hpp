#pragma once
template <typename T>
class LoopList
{
private:
    int head = 0, tail = 0;
    int size = 0;
    int limit = 0;
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

    int add(T &data)
    {
        if (size == limit)
        {
            return -1;
        }
        ts[tail] = data;
        ++tail;
        ++size;
        tail = tail == limit ? 0 : tail;
        return 1;
    }

    T *poll()
    {
        if (size == 0)
        {
            return nullptr;
        }

        T *ans = &ts[head];
        --size;
        ++head;
        head = head == limit ? 0 : head;
        return ans;
    }

    int getSize()
    {
        return this->size;
    }
};