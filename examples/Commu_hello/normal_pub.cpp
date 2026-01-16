#include "RpcCommu/ChannelFactory.h"
#include "RpcCommu/NormalPublisher.h"

#include <functional>
#include <unistd.h>

#include <sys/types.h>

using namespace RpcCommu;
using namespace eprosima::fastdds::dds;
/*
int main()
{
    auto publisher = NormalPublisher<std::string>::create("hello_world");
    while (true)
    {
        std::string data = "123456";
        int res = publisher->publish(data);
        printf("pub:%d \n", res);

        sleep(1);
    }

    return 0;
}
*/

int main()
{
    DataWriterQos writer_qos = DATAWRITER_QOS_DEFAULT;

    writer_qos.durability().kind = DurabilityQosPolicyKind::TRANSIENT_LOCAL_DURABILITY_QOS;
    writer_qos.reliability().kind = ReliabilityQosPolicyKind::RELIABLE_RELIABILITY_QOS;
    //writer_qos.reliability().kind = ReliabilityQosPolicyKind::BEST_EFFORT_RELIABILITY_QOS;
    writer_qos.history().kind = HistoryQosPolicyKind::KEEP_LAST_HISTORY_QOS;
    writer_qos.history().depth = 10;
    auto publisher = NormalPublisher<int>::create("hello_world", nullptr, nullptr, &writer_qos);
    int data = 0;
    while (true)
    {

        int res = publisher->publish(++data);
        printf("pub:%d %d \n", data, res);

        sleep(1);
    }

    return 0;
}