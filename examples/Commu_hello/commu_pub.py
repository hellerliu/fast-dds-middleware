#!/usr/bin/python3

import sys
sys.path.append("../lib")

import time
import RpcCommu
import HelloWorld
import json



if __name__ == "__main__":
    publisher = RpcCommu.ChannelPublisher(HelloWorld.HelloWorldPubSubType, "hello_world")
    msg = HelloWorld.HelloWorld()
   
    index = 0
    #print(json.dumps(msg.__dict__))
    
    while True:
        index += 1
        msg.index(index)
        msg.header().frame_id("hello")
        msg.data()[0] = 1
        res = publisher.publish(msg)
        print(f"py pub:{msg.index()} {res}")
        time.sleep(1) 

    exit()


