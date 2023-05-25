#pragma once
#include "util.hpp"
#include <map>
class RoutineHandler;

RoutineHandler *simple_new(TaskFunc task, void *args);

void simple_resume(RoutineHandler *rh);

void simple_await();

void simple_epoll_event(int sockfd, int eventType);

void simple_epoll_remove(int sockfd);

struct epoll_event *simple_epoll_wait();

RoutineHandler *simple_timer_wait();

void simple_add_timed();

void simple_read(int sockfd, char buffer[], int count);

typedef struct
{
    RoutineHandler *rh;
    bigInt lastUpdateAt;
} FdTimeoutPack;

class SimpleFdTimeoutList
{
private:
    std::map<int, FdTimeoutPack *> timeoutList;
    bigInt waitTime;

public:
    SimpleFdTimeoutList();
    SimpleFdTimeoutList(bigInt waitTime);

    void push(int fd, RoutineHandler *rh);
    void checkAndClear();
};
