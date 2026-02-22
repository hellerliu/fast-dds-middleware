#!/usr/bin/python3

import sys
sys.path.append("../lib")

import RpcCommu
import json
import time

client = RpcCommu.NormalClient("IFiberCall")

data = {
    "data" : 1,
    "msg" : "hello"
}

res, msg = client.call_json("jsonTest", json.dumps(data), 5)
print(f"call_json res:{res}, {msg}")

async def async_callback(res:int, msg :str) :
    print(f"async_callback res:{res}, {msg}")

for i in range(2):
    data["data"] += 1
    client.async_call_json("jsonTest", json.dumps(data), async_callback, 5)

def async_callback1(res:int, msg :str) :
    print(f"callback res:{res}, {msg}")

for i in range(2):
    data["data"] += 1
    client.async_call_json("jsonTest", json.dumps(data), async_callback1, 5)

time.sleep(2)