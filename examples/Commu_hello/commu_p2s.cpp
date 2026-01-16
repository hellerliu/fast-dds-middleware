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

void handleHelloWorld(const HelloWorld &msg)
{
    printf("sub:%d %d\n", msg.index(), gettid());
}

void handleHelloWorld1(const HelloWorld &msg)
{
    printf("sub1:%d %d\n", msg.index(), gettid());
}

int main()
{
    eprosima::fastdds::dds::Log::SetVerbosity(eprosima::fastdds::dds::Log::Info);

    auto publisher = ChannelPublisher<HelloWorldPubSubType>::create("hello_world", nullptr, nullptr, nullptr, ChannelFactory::create(0, nullptr));
    auto subscriber = ChannelSubscriber<HelloWorldPubSubType>::create("hello_world", handleHelloWorld, false, nullptr, nullptr, nullptr, ChannelFactory::create(0, nullptr));

    auto publisher1 = ChannelPublisher<HelloWorldPubSubType>::create("hello_world1");
    auto subscriber1 = ChannelSubscriber<HelloWorldPubSubType>::create("hello_world1", handleHelloWorld1);

    HelloWorld msg;
    msg.index(0);
    while (true)
    {
        msg.index(msg.index() + 1);
        msg.message("---HelloWorld---");
        int res = publisher->publish(msg);
        printf("pub:%d %d\n", msg.index(), res);

        res = publisher1->publish(msg);
        printf("pub1:%d %d\n", msg.index(), res);
        sleep(1);
    }

    return 0;
}