#include "util.hpp"
#include <vector>

template <typename T>
class DelayQueue
{
private:
    int limit = 0;
    int size = 0;
    std::vector<T> data;

    void heapUp();
    void heapify();

public:
    int getSize()
    {
        return size;
    }

    T *poll();

    int add(T &t);
};