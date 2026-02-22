#pragma once

#include <RpcBase/BaseService.h>
#include <testProto/TestMessage.pb.h>
#include <string>

struct EchoMessage
{
    int index;
    std::string message;

    template <typename T>
    void serialize(T &ar)
    {
        ar & index & message;
    }
};

struct JsonStruct
{
    int data;
    std::string msg;
};

namespace reflect
{
    DEFINE_STRUCT_SCHEMA(JsonStruct,
                         DEFINE_STRUCT_FIELD(data),
                         DEFINE_STRUCT_FIELD(msg));

}

class IFiberCall : public rpc::BaseService
{
public:
    IFiberCall() : IFiberCall(true)
    {
    }
    CLIENT_CALL(fiberTest, EchoMessage, proto::EchoMessage);

    CLIENT_CALL(jsonTest, JsonStruct, JsonStruct);

protected:
    IFiberCall(bool isClient) : BaseService(isClient, 5)
    {
        addFunction<&IFiberCall::fiberTest>(true);
        addFunction<&IFiberCall::jsonTest>(true);
    }
};
