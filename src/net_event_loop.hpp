
typedef void *(*AccectTasks)(void *);

class NetEventLoop
{
private:
    AccectTasks func;

public:
    NetEventLoop() {}
    void start();
};