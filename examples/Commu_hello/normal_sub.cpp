#include "RpcCommu/ChannelFactory.h"
#include "RpcCommu/NormalSubscriber.h"

#include <functional>
#include <unistd.h>
#include <string>

#include <sys/types.h>

using namespace RpcCommu;

/*void handleHelloWorld(const std::string &msg)
{
    printf("sub:%s %d\n", msg.c_str(), gettid());
}

int main()
{

    std::function<void(const std::string &)> func = handleHelloWorld;
    auto subscriber = NormalSubscriber<std::string>::create("hello_world", func);

    while (true)
    {
        sleep(1);
    }
    return 0;
}*/

void handleHelloWorld(const int &msg)
{
    printf("sub:%d %d\n", msg, gettid());
    //sleep(3);
}

int main()
{
    DataReaderQos reader_qos = DATAREADER_QOS_DEFAULT;
    // reader_qos.durability().kind = DurabilityQosPolicyKind::VOLATILE_DURABILITY_QOS;
    reader_qos.durability().kind = DurabilityQosPolicyKind::TRANSIENT_LOCAL_DURABILITY_QOS;
    reader_qos.reliability().kind = ReliabilityQosPolicyKind::RELIABLE_RELIABILITY_QOS;
    //reader_qos.reliability().kind = ReliabilityQosPolicyKind::BEST_EFFORT_RELIABILITY_QOS;
    reader_qos.history().kind = HistoryQosPolicyKind::KEEP_LAST_HISTORY_QOS;
    reader_qos.history().depth = 10;

    std::function<void(const int &)> func = handleHelloWorld;
    auto subscriber = NormalSubscriber<int>::create("hello_world", func, false, nullptr, nullptr, &reader_qos);

    while (true)
    {
        sleep(1);
    }
    return 0;
}