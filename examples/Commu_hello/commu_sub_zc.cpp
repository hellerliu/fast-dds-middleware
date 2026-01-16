#include "RpcCommu/ChannelFactory.h"
#include "RpcCommu/ChannelSubscriber.h"
#include "RpcCommu/ChannelPublisher.h"

#include "helloworld_zc/msg/HelloWorldPubSubTypes.hpp"
#include <functional>
#include <unistd.h>

#include <fastdds/dds/log/Log.hpp>
#include <sys/types.h>

using namespace RpcCommu;
using namespace helloworld_zc::msg;

void handleHelloWorld(const HelloWorld &msg)
{
    printf("sub:%d %d\n", msg.index(), gettid());
}


int main()
{
    eprosima::fastdds::dds::Log::SetVerbosity(eprosima::fastdds::dds::Log::Info);    
   
    std::function<void(const HelloWorld &)> func = handleHelloWorld;  
    auto subscriber = ChannelSubscriber<HelloWorldPubSubType, true>::create("hello_world", func);    
  
    while (true)
    {
        sleep(1);
    }
    return 0;
}