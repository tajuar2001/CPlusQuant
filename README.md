# Low-Latency C++ Trading Algorithm

This repository tries to accomplish a low-latency trading algorithm written in C++. The algorithm is engineered to interact seamlessly with stock market data, executing trades based on various technical analysis indicators. It's optimized for efficiency and speed, making it suitable for high-frequency trading environments.

## Features

- **Real-time Market Data Processing**: The algorithm processes live market data, allowing for rapid decision-making based on current market conditions.
- **Technical Analysis Tools**: Implements various technical indicators such as RSI (Relative Strength Index), SMA (Simple Moving Average), and others, offering versatile trading strategies.
- **Multithreading Support**: Utilizes multithreading for efficient data handling and computation, ensuring minimal latency in trading decisions.

## Dependencies

To successfully run this application, the following libraries must be installed:

- **[Libcurl](https://curl.haxx.se/docs/install.html)**: A client-side URL transfer library, essential for interacting with online data sources.
- **[Jsoncpp](https://github.com/open-source-parsers/jsoncpp)**: A C++ library for parsing and interacting with JSON data, critical for handling market data feeds.

### Compilation
Use the following command to compile:

```bash
g++ *.cpp -std=c++11 -ljsoncpp -lcurl -o exa.out && ./exa.out -I/usr/local/Cellar/boost/1.67.0_1/include/boost/
```
