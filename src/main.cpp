#include "tcp_socket.hpp"
#include "loop_list.hpp"
#include <iostream>
int main()
{
    // snr::TcpSocket *ts = new snr::TcpSocket();
    // ts->setSocket();
    // ts->bindSocket(9000);
    // std::cout << "listen on 9000" << std::endl;
    // ts->onListen();
    // ts->syncAccept();
    int a = 10;
    int b = 3434;
    int e = 22222;
    int er = 12121;
    LoopList<int> ls(10);
    ls.add(a);
    ls.add(b);
    ls.add(e);
    ls.add(er);
    ls.poll();
    ls.poll();
    std::cout
        << ls.getSize() << std::endl;
    return 0;
}