#include "SerialClass.h"

#ifdef HAS_USB_SERIAL
SerialClass::SerialClass(Serial_ & port)
{
	USBport=&port;
	HWport=NULL;
	init();
}

#endif


SerialClass::SerialClass(HardwareSerial & port)
{
	HWport=&port;
	#ifdef HAS_USB_SERIAL
	USBport=NULL;
	#endif
	init();
}

void SerialClass::init(void)
{

}

SerialClass::operator bool()
{
	bool bActive=HWport;

	#ifdef HAS_USB_SERIAL
	if (!bActive)
	{
		/*
		 * Windows: SerialUSB becomes true when connection is established
		 *          but stays true when USB connection is closed
		 * 			dtr() becomes false when USB connection is closed
		 * Linux:   SerialUSB represents the connection state of an
		 *          USB serial port. no issues
		 * 
		 * Issue:	A cakk to USBPort costs 10 ms , use dtr() instead
		 */ 
		bActive=*USBport;
		if (bActive)
			bActive=USBport->dtr();
	}
	#endif
	return bActive;
}

void SerialClass::begin(unsigned long baud, uint16_t config)
{
	if (HWport)
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
	if (HWport)
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
	if (HWport)
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
	if (HWport)
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
	if (HWport)
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
	if (HWport)
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
	if (HWport)
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
	if (HWport)
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

size_t SerialClass::write(const uint8_t *buffer, size_t size)
{
	if (HWport)
	{	// HardwareSerial
		return HWport->write(buffer,size);
	}	// HardwareSerial
	#ifdef HAS_USB_SERIAL
	else
	{	// CDC-Serial
		return USBport->write(buffer,size);
	}	// CDC-Serial
	#endif
}

size_t SerialClass::readBytes( char *buffer, size_t length)
{
	if (HWport)
	{	// HardwareSerial
		return HWport->readBytes(buffer,length);
	}	// HardwareSerial
	#ifdef HAS_USB_SERIAL
	else
	{	// CDC-Serial
		return USBport->readBytes(buffer,length);
	}	// CDC-Serial
	#endif
}

int32_t SerialClass::readBreak()
{
	if (HWport)
	{	// HardwareSerial
		return 0;
	}	// HardwareSerial
	#ifdef HAS_USB_SERIAL
	else
	{	// CDC-Serial
		return USBport->readBreak();
	}	// CDC-Serial
	#endif
}

bool SerialClass::dtr(void)
{
	if (HWport)
	{	// HardwareSerial
		return true;
	}	// HardwareSerial
	#ifdef HAS_USB_SERIAL
	else
	{	// CDC-Serial
		return USBport->dtr();
	}	// CDC-Serial
	#endif
}

bool SerialClass::rts(void)
{
	if (HWport)
	{	// HardwareSerial
		return true;
	}	// HardwareSerial
	#ifdef HAS_USB_SERIAL
	else
	{	// CDC-Serial
		return USBport->rts();
	}	// CDC-Serial
	#endif
}
