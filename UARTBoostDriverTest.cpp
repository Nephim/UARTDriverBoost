#include "UARTBoostDriver.h"
#include <iostream>
#include <pthread.h>
using namespace std;

UARTBoostDriver  test;

void* reader(void* arg)
{
    while(true)
    {
        char n = test.read_from_port();
        cout << "Read: " << n << endl;
    }
}

int main() 
{ 
  pthread_t   readUART;
  char        temp;

  pthread_create(&readUART, NULL, reader, NULL);

    // Kør fremad
    while (true)
    {
      cout << "\nIndtast besked: ";
      cin >> temp;
      test.write_to_port(temp);
    }


    test.close_port();
    return 0;
    
}