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
    struct epoll_event event;

public:
    struct epoll_event events[MAX_EVENTS];

    ~EpollPack()
    {
        close(epfd);
    }

    void setEpoll()
    {
        this->epfd = epoll_create1(0);
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

    void removeEvent(int sockfd)
    {
        epoll_ctl(epfd, EPOLL_CTL_DEL, sockfd, nullptr);
    }

    struct epoll_event *waitEvent(int waitTime, int &resultLen)
    {
        int count = epoll_wait(epfd, events, MAX_EVENTS, waitTime);
        resultLen = count;
        return events;
    }
};