#ifndef SERIAL_H_INCLUDED
#define SERIAL_H_INCLUDED

#define TERMINAL_BELL		0x07
#define TERMINAL_BACKSPACE	0x08
#define TERMINAL_TAB		0x09
#define TERMINAL_LF			0x0A
#define TERMINAL_FF			0x0C
#define TERMINAL_CR			0x0D

unsigned char RXbuf[32];
unsigned char RXbuf_ptr;

void SerialInit(void); // geregeld in Bootloader!
void SerialClearError(void);

void SerialSendByte(unsigned char);
void SerialSendByteInterrupt(unsigned char);

void SerialSendString(unsigned char *);
void SerialSendStringInterrupt(unsigned char *);

#endif
