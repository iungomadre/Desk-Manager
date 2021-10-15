#include "../include/setup.h"

void initialiseSerialConnection(HardwareSerial& serial_output, unsigned int port)
{
  serial_output.begin(port);
  serial_output.println("Serial connection initialised.");
}