#include "simple_routine.hpp"
#include "tcp_socket.hpp"
#include "delay_queue.hpp"
#include "single_example.hpp"
#include <iostream>

void *test(void *args)
{
    int a = 123;
    int adf = 3434;
    int sadf = 123123123;
    std::cout << sadf << std::endl;
    simple_await();
    std::cout << "three" << std::endl;
    return nullptr;
}

int main()
{
    // RoutineHandler *rh1 = simple_new(test, nullptr);
    // RoutineHandler *rh2 = simple_new(test, nullptr);
    // simple_resume(rh1);
    // std::cout << "two" << std::endl;
    // simple_resume(rh2);
    // simple_resume(rh1);
    // return 0;

    singleThreadTest();
}
