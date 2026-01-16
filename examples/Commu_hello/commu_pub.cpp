#include "RpcCommu/ChannelFactory.h"
#include "RpcCommu/ChannelSubscriber.h"
#include "RpcCommu/ChannelPublisher.h"
#include "helloworld/msg/HelloWorldPubSubTypes.hpp"
#include <functional>
#include <unistd.h>

#include <fastdds/dds/log/Log.hpp>
#include <sys/types.h>

using namespace RpcCommu;
using namespace helloworld::msg;

int main()
{
    eprosima::fastdds::dds::Log::SetVerbosity(eprosima::fastdds::dds::Log::Info);
    // ChannelPublisher<HelloWorldPubSubType>::Ptr publisher = ChannelPublisher<HelloWorldPubSubType>::create("hello_world");
    auto publisher = ChannelPublisher<HelloWorldPubSubType>::create("hello_world", nullptr, nullptr, nullptr, ChannelFactory::create(0, nullptr));
    auto publisher1 = ChannelPublisher<HelloWorldPubSubType>::create("hello_world1", nullptr, nullptr, nullptr, ChannelFactory::create(0, nullptr));

    HelloWorld msg;
    msg.index(0);
    while (true)
    {
        msg.index(msg.index() + 1);
        msg.data()[0] = 1;
        msg.data()[1] = 2;
        msg.message("---HelloWorld---");
        int res = publisher->publish(msg);
        printf("pub:%d %d\n", msg.index(), res);

        res = publisher1->publish(msg);
        printf("pub1:%d %d\n", msg.index(), res);
        sleep(1);
    }

    return 0;
}