#include "simple_routine.hpp"
#include "controller.hpp"

extern thread_local Controller localCon;

RoutineHandler *simple_new(TaskFunc task, void *args)
{
    RoutineHandler *rh = localCon.createRoutine(task, args);
    return rh;
}

void simple_resume(RoutineHandler *rh)
{
    localCon.resumeRouine(rh);
}

void simple_await()
{
    localCon.pendRoutine();
}

void simple_epoll_event()
{
}

void simple_timed_task()
{
}

void t_simple_pause()
{
}

void simple_read(int sockfd, char buffer[], int count)
{
    int flags = fcntl(sockfd, F_GETFL, 0);
    fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);
    ssize_t res = -1;
    do
    {
        res = read(sockfd, buffer, count);
        if (res == -1)
        {
            localCon.addEpollEvent(sockfd, EPOLLIN);
            simple_await();
        }
    } while (res == -1);
}