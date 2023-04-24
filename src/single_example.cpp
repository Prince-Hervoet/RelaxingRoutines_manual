#include "single_example.hpp"
#include "tcp_socket.hpp"
#include "simple_routine.hpp"
#include "epoll_pack.hpp"

typedef struct
{
    int conn;
} TaskArgs;

static void *routineTaskFunc(void *args)
{
    TaskArgs *taskArgs = (TaskArgs *)(args);
    int sockfd = taskArgs->conn;
    int flags = fcntl(sockfd, F_GETFL, 0);
    fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);
    ssize_t res = -1;
    char buffer[256];
    do
    {
        res = read(sockfd, buffer, 256);
        if (res == -1)
        {
            simple_epoll_event(sockfd, EPOLLIN);
            simple_await();
        }
    } while (res == -1);
    close(sockfd);
}

void singleThreadTest()
{
    snr::TcpSocket *ts = new snr::TcpSocket();
    ts->setSocket(false);
    ts->bindSocket(9000);
    ts->onListen();
    int conn = -1;
    for (;;)
    {
        conn = ts->onAccept();
        if (conn != -1)
        {
            TaskArgs *taskArgs = new TaskArgs();
            taskArgs->conn = conn;
            RoutineHandler *rh = simple_new(routineTaskFunc, (void *)taskArgs);
            simple_resume(rh);
        }
    }
}