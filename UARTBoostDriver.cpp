#include "UARTBoostDriver.h"
#include <errno.h>   /* Error number definitions */
#include <fcntl.h>   /* File control definitions */
#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <stdlib.h>


using namespace boost;



UARTBoostDriver::UARTBoostDriver() : port(io)
{ 
  open_port();

}

UARTBoostDriver::~UARTBoostDriver()
{
  close_port();
}

int UARTBoostDriver::open_port()
{
    port.open("/dev/ttyS0"); // Hvis i bruger en USB2Uart ting
    port.set_option(asio::serial_port_base::baud_rate(115200));

  return 1;
}

void UARTBoostDriver::write_to_port(uint8_t n)
{
  int bytes_written = asio::write(port, asio::buffer(&n, 1));
  //printf("Bytes written: %d\n", bytes_written);
}

uint8_t UARTBoostDriver::read_from_port() 
{ 
  uint8_t c;

  asio::read(port, asio::buffer(&c,1));

  return c;
}

void UARTBoostDriver::close_port() 
{ 
  port.close();
}