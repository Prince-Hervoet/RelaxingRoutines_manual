#include "simple_routine.hpp"
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
    RoutineHandler *rh = simple_new(test, nullptr);
    simple_resume(rh);
    std::cout << "two" << std::endl;
    simple_resume(rh);
    return 0;
}