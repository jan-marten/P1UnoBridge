
#include "rs232.h"


void send_string_UART(unsigned char *string) {
	while(*string) {
		send_byte_UART(*string);
		string++;
	}
}

void send_byte_UART(unsigned char byte_to_send) {
	cleanerror_UART(); //clear errors indien nodig
	TXREG = byte_to_send;
	asm("nop"); // short propagation delay
	while(TXIF == 0); //wacht tot ie klaar is.
}

void send_string_UART_int(unsigned char *string) {
	// deze routine kan vanuit Interrupt aangesproken worden.
	while(*string) {
		send_byte_UART_int(*string);
		string++;
	}
}

void send_byte_UART_int(unsigned char byte_to_send) {
	// deze routine kan vanuit Interrupt aangesproken worden.
	cleanerror_UART(); //clear errors indien nodig
	TXREG = byte_to_send;
	asm("nop"); // short propagation delay
	while(TXIF == 0); //wacht tot ie klaar is.
}


unsigned char rec_byte_UART() {
	// receive a byte and store it in
	cleanerror_UART(); //clear errors indien nodig.
	while(RCIF==0);//wacht totdat we klaar zijn, hier crasht ie weleens...
	return RCREG;
}

void cleanerror_UART(void) {
	if(FERR || OERR) {
		//check for hardware errors
		CREN=0;
		//magic error clearing code
		CREN=1;
		//hardware framing or overrun error
	}
}

//void init_UART(unsigned char baudrate) {
void init_UART(void) {

	TXSTA = 0x24; //TXenable, Highbaudrate
	RCSTA = 0x90; //SerialPortEnable, Continues Receive enable
	//SPBRG = baudrate; // BAUD_6900 of BAUD_19200

}
