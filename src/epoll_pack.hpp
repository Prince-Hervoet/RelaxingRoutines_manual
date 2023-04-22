#include <sys/epoll.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_EVENTS 32

class EpollPack
{
private:
    int epfd = -1;
    struct epoll_event event, events[MAX_EVENTS];

public:
    void setEpoll()
    {
        this->epfd = (0);
        if (this->epfd == -1)
        {
            perror("epoll_create1");
        }
    }

    void setEvent(int op, int eventType, int listenfd, void *data)
    {
        event.data.fd = listenfd;
        event.data.ptr = data;
        event.events = eventType;
        int result = epoll_ctl(epfd, op, listenfd, &event);
        if (result == -1)
        {
            perror("epoll_ctl");
        }
    }

    struct epoll_event *waitEvent(int waitTime, int &resultLen)
    {
        int count = epoll_wait(epfd, events, MAX_EVENTS, waitTime);
        resultLen = count;
        return events;
    }
};