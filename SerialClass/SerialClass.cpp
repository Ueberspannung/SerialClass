#include "SerialClass.h"

#ifdef HAS_USB_SERIAL
SerialClass::SerialClass(Serial_ & port)
{
	USBport=&port;
	bUSB=true;
	init();
}

#endif


SerialClass::SerialClass(HardwareSerial & port)
{
	HWport=&port;
	bUSB=false;
	init();
}

void SerialClass::init(void)
{

}

bool SerialClass::isConnected(void)
{
	bool bConnected=!bUSB;
	#ifdef HAS_USB_SERIAL
	if (!bConnected)
	{
		/*
		 * Windows: SerialUSB becomes true when connection is established
		 *          but stays true when USB connection is closed
		 * 			dtr() becomes false when USB connection is closed
		 * Linux:   SerialUSB represents the connection state of an
		 *          USB serial port. no issues
		 */
		 bConnected=USBport->dtr();
	}
	#endif
	return bConnected;
}

SerialClass::operator bool()
{
	bool bActive=!bUSB;

	#ifdef HAS_USB_SERIAL
	if (!bActive)
	{
		/*
		 * Windows: SerialUSB becomes true when connection is established
		 *          but stays true when USB connection is closed
		 * 			dtr() becomes false when USB connection is closed
		 * Linux:   SerialUSB represents the connection state of an
		 *          USB serial port. no issues
		 */ 
		bActive=*USBport;
		if (bActive)
			bActive=USBport->dtr();
	}
	#endif
	return bActive;
}

void SerialClass::message(void)
{
	if (bUSB)
		println(F("USB Serial detected"));
	else
		println(F("Hardware Serial detected"));
}

void SerialClass::begin(unsigned long baud, uint16_t config)
{
	if (!bUSB)
	{	// HardwareSerial
		HWport->begin(baud,config);
	}	// HardwareSerial
	#ifdef HAS_USB_SERIAL
	else
	{	// CDC-Serial
		USBport->begin(baud,config);
	}	// CDC-Serial
	#endif
}

void SerialClass::end()
{
	if (!bUSB)
	{	// HardwareSerial
		HWport->end();
	}	// HardwareSerial
	#ifdef HAS_USB_SERIAL
	else
	{	// CDC-Serial
		USBport->end();
	}	// CDC-Serial
	#endif
}

int	SerialClass::available(void)
{
	if (!bUSB)
	{	// HardwareSerial
		return HWport->available();
	}	// HardwareSerial
	#ifdef HAS_USB_SERIAL
	else
	{	// CDC-Serial
		return USBport->available();
	}	// CDC-Serial
	#endif
}

int SerialClass::peek(void)
{
	if (!bUSB)
	{	// HardwareSerial
		return HWport->peek();
	}	// HardwareSerial
	#ifdef HAS_USB_SERIAL
	else
	{	// CDC-Serial
		return USBport->peek();
	}	// CDC-Serial
	#endif
}

int SerialClass::read(void)
{
	if (!bUSB)
	{	// HardwareSerial
		return HWport->read();
	}	// HardwareSerial
	#ifdef HAS_USB_SERIAL
	else
	{	// CDC-Serial
		return USBport->read();
	}	// CDC-Serial
	#endif
}

int SerialClass::availableForWrite(void)
{
	if (!bUSB)
	{	// HardwareSerial
		return HWport->availableForWrite();
	}	// HardwareSerial
	#ifdef HAS_USB_SERIAL
	else
	{	// CDC-Serial
		return USBport->availableForWrite();
	}	// CDC-Serial
	#endif
}

void SerialClass::flush(void)
{
	if (!bUSB)
	{	// HardwareSerial
		HWport->flush();
	}	// HardwareSerial
	#ifdef HAS_USB_SERIAL
	else
	{	// CDC-Serial
		USBport->flush();
	}	// CDC-Serial
	#endif
}

size_t SerialClass::write(uint8_t c)
{
	if (!bUSB)
	{	// HardwareSerial
		return HWport->write(c);
	}	// HardwareSerial
	#ifdef HAS_USB_SERIAL
	else
	{	// CDC-Serial
		return USBport->write(c);
	}	// CDC-Serial
	#endif
}
