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

// auto subscriber = ChannelSubscriber<HelloWorldPubSubType>::create("hello_world", handleHelloWorld);

int main()
{
    eprosima::fastdds::dds::Log::SetVerbosity(eprosima::fastdds::dds::Log::Info);    
   
    std::function<void(const HelloWorld &)> func = handleHelloWorld;
    // auto subscriber = ChannelSubscriber<HelloWorldPubSubType>::create("hello_world", func);
    ChannelSubscriber<HelloWorldPubSubType>::Ptr subscriber = ChannelSubscriber<HelloWorldPubSubType>::create("hello_world", func);
    
    ChannelSubscriber<HelloWorldPubSubType>::Ptr subscriber1 = ChannelSubscriber<HelloWorldPubSubType>::create("hello_world1", handleHelloWorld1);
    while (true)
    {
        sleep(1);
    }
    return 0;
}