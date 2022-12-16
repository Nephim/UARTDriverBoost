#ifndef UARTDRIVE_H
#define UARTDRIVE_H
using namespace std;
#include <boost/asio.hpp>


#pragma once

class UARTBoostDriver
{
public:
    UARTBoostDriver();
    ~UARTBoostDriver();
    int open_port();
    void write_to_port(uint8_t n);
    uint8_t read_from_port();
    void close_port();

  private:
    uint8_t n;
    boost::asio::io_context io;
    boost::asio::serial_port port;
};

#endif