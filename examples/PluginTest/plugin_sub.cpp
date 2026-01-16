#include "RpcCommu/Node.h"

#include "RpcCommu/ChannelSubscriber.h"
#include "helloworld/msg/HelloWorldPubSubTypes.hpp"
#include <functional>
#include <unistd.h>

using namespace RpcCommu;
using namespace helloworld::msg;

void handleHelloWorld(const HelloWorld &msg)
{
    printf("sub:%d %d\n", msg.index(), gettid());
}

class SubTestNode : public RpcCommu::Node
{

public:
    SubTestNode()
    {
        printf("SubTestNode\n");
        std::function<void(const HelloWorld &)> func = handleHelloWorld;

        subscriber_ = ChannelSubscriber<HelloWorldPubSubType>::create("hello_world", func);
        assert(subscriber_);
    }

    ~SubTestNode()
    {
        printf("SubTestNode release\n");
    }

private:
    ChannelSubscriber<HelloWorldPubSubType>::Ptr subscriber_;
};

COMPONENTS_REGISTER_NODE(SubTestNode)