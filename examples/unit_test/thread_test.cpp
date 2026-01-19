
#include <unistd.h>
#include <RpcCore/FiberThread.h>
#include <utils/DefaultFuncTracker.h>

class ResTracker
{
    utils::DefaultFuncTracker<> tracker_{"ResTracker"};
};

int param_test1(ResTracker res)
{
    return 0;
}

int param_test2(ResTracker &res)
{
    return 0;
}

int param_test3(const ResTracker &res)
{
    printf("%p\n", &res);
    return 0;
}

int param_test4(ResTracker &&res)
{
    return 0;
}

int param_test5(int n1, const int &n2, int &n3)
{
    n1++;
    n3++;
    return 0;
}

int param_test6(int n1, const int &n2, int &&n3)
{
    n1++;
    n3++;
    return 0;
}

class Test
{
public:
    Test() = default;
    int param_test5(int n1, const int &n2, int &n3)
    {
        n1++;
        n3++;
        return 0;
    }

    int param_test6(int n1, const int &n2, int &&n3)
    {
        n1++;
        n3++;
        return 0;
    }
};

class MyBlock
{
public:
    int block_call(int in)
    {
        printf("MyBlock block_call\n");
        sleep(2);
        return 6;
    }
};


int main()
{
    utils::DefaultFuncTrackCfg::setOutputLevel(utils::DefaultFuncOutput::All);

    std::shared_ptr<rpc::FiberThread> thread2 = rpc::FiberThread::create();

    ResTracker res;

    thread2->postCall(param_test1, res);
    // thread2->postCall(param_test2, res);

    thread2->postCall(param_test3, res);

    thread2->postCall(param_test4, res);

    thread2->postCall(param_test1, std::move(res));

    // thread2->postCall(param_test2, std::move(res));

    thread2->postCall(param_test3, std::move(res));

    thread2->postCall(param_test4, std::move(res));
    //

    thread2->sendCall(param_test1, res);

    thread2->sendCall(param_test2, res);

    thread2->sendCall(param_test3, res);
    // thread2->sendCall(param_test4, res);
    /*int nn = 0;
    int &n1 = nn;
    int &n2 = nn;*/
    const int &n1 = 0;
    const int &n2 = 0;
    // int n1 = 0, n2 = 0;
    int n3 = 0;
    thread2->sendCall(param_test5, n1, n2, n3);
    printf("%d %d %d\n", n1, n2, n3);

    thread2->postCall(param_test6, n1, n2, std::move(n3));
    thread2->postCall(param_test6, n1, std::move(n3), n2);

    Test data;
    thread2->sendCall(&Test::param_test5, &data, n1, n2, n3);
    thread2->sendCall(&Test::param_test5, data, n1, n2, n3);
    printf("%d %d %d\n", n1, n2, n3);

    thread2->postCall(&Test::param_test6, &data, n1, n2, std::move(n3));
    thread2->postCall(&Test::param_test6, &data, n1, std::move(n3), n2);
    thread2->postCall(&Test::param_test6, std::move(data), n1, n2, n3);
    thread2->postCall(&Test::param_test6, data, n1, n2, n3);

    thread2->postCall(&Test::param_test6, data, n1, std::ref(n2), n3);

    thread2->stopThread();

    MyBlock myblock;
    int res1 = rpc::fiber_async(&MyBlock::block_call, myblock, 20);
    return 0;
}