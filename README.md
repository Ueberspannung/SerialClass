# SerialClass
Serial Wrapper for Arduino Boards

##motivation
wenn porgramming across different arduino boards I found it not convenient to use differnt names for serial ports.
The UNO uses Serial as primary interface the Pro Micro / Leonardo uses Serial ord SerialUSB as primary port and the 
Zero uses SerialUSB as primary port. Even when using one of the other SerialPorts it's Serial1 Serial2 ,,,   
My itention is to use a SerialClass wich is initilized with the desired port and than uses as usual.

such as   
```
#include "SerialClass.h"

SerialClass ComPort{SerialUSB);

void setup(void)
{
	ComPort.begin(115200);
	while(!ComPort)
	{
		asm("nop"); 
	}
	ComPort.println("Hello World");
}
```