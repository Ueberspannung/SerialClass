#ifndef __SerialClass_h__
#define __SerialClass_h__

#include <Arduino.h>
#include <stdint.h>
#include <Stream.h>

#if defined(HAVE_CDCSERIAL) || !defined(ARDUINO_ARCH_AVR)
#define HAS_USB_SERIAL
#endif


class SerialClass: public Stream
{
	public:

		SerialClass(HardwareSerial & port);
		#ifdef HAS_USB_SERIAL
		SerialClass(Serial_ & port);
		#endif

		void message(void);

		bool isUSB(void) { return bUSB; }
		bool isConnected(void);

		void begin(unsigned long baud) { begin(baud, SERIAL_8N1); }
		void begin(unsigned long baud, uint16_t config);
		void end();
 		virtual int available(void);
		virtual int peek(void);
		virtual int read(void);
		virtual int availableForWrite(void);
		virtual void flush(void);
		virtual size_t write(uint8_t);
		inline size_t write(unsigned long n) { return write((uint8_t)n); }
		inline size_t write(long n) { return write((uint8_t)n); }
		inline size_t write(unsigned int n) { return write((uint8_t)n); }
		inline size_t write(int n) { return write((uint8_t)n); }

		
	
		operator bool();

		
	private:
		bool			bUSB;
		HardwareSerial 	* HWport;
		#ifdef HAS_USB_SERIAL
		Serial_			* USBport;
		#endif
		
		void init(void);
};

#endif // __SerialClass_h__
