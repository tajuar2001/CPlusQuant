# Low-Latency C++ Trading Algo
This repository contains a low-latency trading algorithm implemented in C++. It's designed to interact with stock market data and execute trades based on technical analysis indicators.

## Dependencies
Before you run this application, ensure that you have the following libraries installed: 

[Libcurl](https://curl.haxx.se/docs/install.html): A client-side URL transfer library. 

[Jsoncpp](https://github.com/open-source-parsers/jsoncpp): A C++ library for interacting with JSON data. 


## To Run
To compile and run:

```bash
g++ *.cpp -std=c++11 -ljsoncpp -lcurl -o exa.out && ./exa.out -I/usr/local/Cellar/boost/1.67.0_1/include/boost/
```
