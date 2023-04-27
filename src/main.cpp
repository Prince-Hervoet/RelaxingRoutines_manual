#include "simple_routine.hpp"
#include "tcp_socket.hpp"
#include "delay_queue.hpp"
#include <iostream>

void *test(void *args)
{
    std::cout << "one" << std::endl;
    simple_await();
    std::cout << "three" << std::endl;
    return nullptr;
}

int main()
{
    // snr::TcpSocket *ts = new snr::TcpSocket();
    // ts->setSocket();
    // ts->bindSocket(9000);
    // std::cout << "listen on 9000" << std::endl;
    // ts->onListen();
    // ts->syncAccept();
    RoutineHandler *rh1 = simple_new(test, nullptr);
    RoutineHandler *rh2 = simple_new(test, nullptr);
    simple_resume(rh1);
    std::cout << "two" << std::endl;
    simple_resume(rh2);
    simple_resume(rh1);

    // DelayQueue<int> *dq = new DelayQueue<int>();
    // int a = 123;
    // int b = 8987;
    // int c = 9999;
    // dq->push(a, 2000LL);
    // dq->push(b, 122LL);
    // dq->push(c, 122132LL);
    // std::cout << *(dq->peek()) << std::endl;
    return 0;
}