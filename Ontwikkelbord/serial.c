#include "serial.h"

void SerialInit(void) {
    TXSTA = 0x24; //TXenable, Highbaudrate
    RCSTA = 0x90; //SerialPortEnable, Continues Receive enable
    //SPBRG = baudrate - baudrate is set in bootloader!
}

void SerialClearError(void) {
    if(FERR || OERR) {
        //check for hardware errors
        CREN=0;
        //magic error clearing code
        CREN=1;
        //hardware framing or overrun error
    }
}

void SerialSendString(unsigned char *string) {
	while(*string) {
		SerialSendByte(*string);
		string++;
	}
}

void SerialSendByte(unsigned char byte_to_send) {
	SerialClearError(); 
	TXREG = byte_to_send;
	asm("nop"); // short propagation delay
	while(TXIF == 0); //wacht tot ie klaar is.
}

void SerialSendStringInterrupt(unsigned char *string) {
	// deze routine kan vanuit Interrupt aangesproken worden.
	while(*string) {
		SerialSendByteInterrupt(*string);
		string++;
	}
}

void SerialSendByteInterrupt(unsigned char byte_to_send) {
	// deze routine kan vanuit Interrupt aangesproken worden.
	SerialClearError(); //clear errors indien nodig
	TXREG = byte_to_send;
	asm("nop"); // short propagation delay
	while(TXIF == 0); //wacht tot ie klaar is.
}


unsigned char SerialReceivedByte() {
	// receive a byte and store it in
	SerialClearError(); //clear errors indien nodig.
	while(RCIF==0);//wacht totdat we klaar zijn, hier crasht ie weleens...
	return RCREG;
}

