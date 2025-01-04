# SerialClass
Serial Wrapper for Arduino Boards

## motivation
wenn porgramming across different arduino boards I found it not convenient to use differnt names for serial ports.
The UNO uses Serial as primary interface the Pro Micro / Leonardo uses Serial ord SerialUSB as primary port and the 
Zero uses SerialUSB as primary port. Even when using one of the other SerialPorts it's Serial1, Serial2 ... 
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

## issues
There are two types of serial classe Hwardware Serial and Serial_ (at least on AVR and SAM devices)  
Serial_ is only defined on devices with USB. So any reference to Serial_ has to be removed to compile on  
Hardware without USB such as the original Arduino Uno.
This can be done the C++ way such as ["How to check if a class is declared in c++"](https://stackoverflow.com/questions/53297795/how-to-check-if-a-class-is-declared-in-c)  
or you can make use of predefined framework makros.
I am working with avr and sam boards. On AVR Boards the is a macro called ***HAVE_CDCSERIAL*** and other
platforms have USB so the second macro to check is if it is not an AVR ***ARDUINO_ARCH_AVR***.  
using these two macros an conditional compiling solves the problem.

Detecting on USB Serial connection should be easy. To check this the class itselve has an boolean operator
which can be used to detect an open usb connection. But the are two problems:
- Problem 1:
    - Windows Platforms:  
    The object becomes true when a windows host when a USB Serial Port is opened but stays true when it is closed.
    - Linux Platforms  
	The object becomes true a ttyUSB is opened and false when it is closed
	- **Solution**  
	When a port is opened the dtr() member becomes true and false when it is closed. So when the object is true
	the dtr() needs to be checked to be sure
- Problem 2:  
A singel call to the Object itself takes 10 ms blocking. This cant be used if strict timing is required  
    - **Solution:**   
	a call to dtr() is possible even when no usb connection exists.

## interface
the public interface of SerialClass is identical to Serclass_ and HardwareSerial.
Dependent on the constructor used member calls are redirected either to HardwareSerial or Serial_

## Paltforms
Tested on 
- AVR without USB (Atmega328 / UNO)
- AVR with USB (Atmega32U4 / Pro Micro)  
- ARM (SAMD21G18 / Zero)  

