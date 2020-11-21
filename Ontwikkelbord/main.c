/*
 * Frutzels.c
 * JMR
 *
 * Compile: C:\HTSOFT\PIC18\bin\picc18.exe -C -E"Error.log" "main.c" -O"main.obj" -Zg9 -O -ASMLIST -18F452
 * Link: C:\HTSOFT\PIC18\bin\picc18.exe -E"Error.log" "main.obj" -M"Projectmain.map" -O"Projectmain.cof" -O"Projectmain.hex" -18F452
 *
 * Tiny Bootloader gebruiken om .hex in te laden
 * Schakelaar naar beneden = COM-poort selectie
 * Baudrate = 115200
 * Druk op Write Flash
 * Hou RA4 ingedrukt en druk op Reset binnen gestelde zoekperiode
 * 
 */

#define XTAL_FREQ 20MHZ
void Toggle(x) { 
	if (x) { 
		x = 0; 
	} else { 
		x = 1; 
	}
}

#include <stdio.h>
#include <string.h>
#include <pic18.h>
#include "delay.c"
#include "rs232.c"
//#include "lcd.c"
#include "Lcd_18.c"
#include "keyboard.c"
#include "interrupts.c"

unsigned char RXbuffer[32];
unsigned char RXptr;
unsigned char RXshowData;
unsigned char key;
unsigned int Timer0Teller;

void main(void) {

	// Vars:
	//unsigned char i;
	//unsigned char taskID;


	//unsigned char *testje;
	unsigned char taskID;
	unsigned char taskState; // 0 = starting, 1 = running, 2 = waiting, 5=finished


	unsigned char TXbuf[32];
	unsigned char LCDbuf[16];
	//unsigned char RX;
	unsigned char ptr;
	unsigned char keyChar;

	ptr = 0;
	RXptr = 0;
	RXshowData = 0;
	key = 0xFF; //KEYBOARD_UNDEFINED_STATE
	keyChar = '?';

	taskID = 0;
	taskState = 0;
	Timer0Teller = 0;

	ADCON1	= 0x06;		// PortA is compleet Digitaal
	PORTA	= 0x00;
	TRISA	= 0x00;		// PortA OUTPUT mode voor display control

	TRISB	= 0xFF;		// PortB INPUT-mode
	RBPU	= 0;		// Enable weak-pull-ups
	PORTB	= 0xFF;

	//TRISD	= 0x00;		// PortD OUTPUT-mode
	//PORTD	= 0xFF;		// ledjes uitschakelen (1=uit, 0=aan)

	TRISE	= 0x00;
	PORTE	= 0x00;

	//Initialiseer de seriele poort:
	init_UART();
	strcpy(TXbuf, "Hello world.\r\n");
	send_string_UART(TXbuf);
	
	//Initialiseer het LCD:
	//lcd_init(EIGHTBIT_MODE);
	//lcd_init(FOURBIT_MODE);
	//             0000000001111111111222222222233333333334444444444555555555566666666667
	//             1234567890123456789012345678901234567890123456789012345678901234567890
	//lcd_init();
	//
	//strcpy(LCDbuf,"-Typmaschientje-");
	//lcd_string(LCDbuf);

	InitLcd(); 
	CommandLcd(LCD_TWOLINE);
	CommandLcd(LCD_STDENTRY);
	CommandLcd(LCD_ON);  
	CommandLcd(LCD_CLS); 
	SendLcd("Typmaschien v0.0.2A ", 20); //regel 1
	SendLcd("info@regeling.com   ", 20); //regel 3
	SendLcd("J.M. Regeling       ", 20); //regel 2
	SendLcd("http://regeling.com ", 20); //regel 4

	//initialize keyboard
	initKeyboard();
	
	init_INT();

	while(1) {
		if (key != KEYBOARD_UNDEFINED_STATE) { //0xFF) {
			//send_byte_UART(key);
			//key = 0xFF;

			switch (key) {
				case 0: keyChar = '0'; break;
				case 1: keyChar = '1'; break;
				case 2: keyChar = '2'; break;
				case 3: keyChar = '3'; break;
				case 4: keyChar = '4'; break;
				case 5: keyChar = '5'; break;
				case 6: keyChar = '6'; break;
				case 7: keyChar = '7'; break;
				case 8: keyChar = '8'; break;
				case 9: keyChar = '9'; break;
				case 10: keyChar = 'A'; break;
				case 11: keyChar = 'B'; break;
				case 12: keyChar = 'C'; break;
				case 13: keyChar = 'D'; break;
				case 14: keyChar = '#'; break;
				case 15: keyChar = '*'; break;
				default: keyChar = '?'; break;
			}


			send_byte_UART(keyChar);

			//lcd_data(keyChar);
			SendLcd(&keyChar, 1);

			if (key == 15){
				RXshowData = 1;
			}

			key = KEYBOARD_UNDEFINED_STATE; // 0xFF;
		}
		
		if (RXshowData == 1) {
			RXshowData=0;
			CommandLcd(LCD_CLS); 
			SendLcd("Typmaschien v0.0.2  ",20); //regel 1
			SendLcd(&RXbuffer,20); //regel 3
			SendLcd("Data received:      ",20); //regel 2
			SendLcd("                    ",20); //regel 4
		}
	}
}

void interrupt interrupt_handler(void) {

	if (INT0IF) { // INT0 = Keyboard interrupt
		//Toggle(RE0);
		send_string_UART_int("intK");
		GIE = 0; // disable interupts
		key = readKeyboard();
		//send_byte_UART_int('k'); //just to check if this routine is executed
		INT0IF = 0; //clear interrupt flag
		GIE = 1; // enable interupts
	}
	else if (INT1IF) { // INT1 (switch 1)
		//Toggle(RE1);
		//send_byte_UART_int('1');
		INT1IF = 0; //clear interupt flag
		send_string_UART_int("int1");
		send_byte_UART_int(RXptr + 0x30);
		
		send_string_UART_int(&RXbuffer);
		send_string_UART_int("\r\n");
		
	}
	else if (INT2IF) { //INT2 (switch 2)
		//Toggle(RE2);
		//send_byte_UART_int('2');
		send_string_UART_int("int2");
		INT2IF = 0; //clear interrupt flag
	}

	//if (TMR0IF) { //Timer0
	//Disabled: display hangt hier ook aan vast (RA4)
	//	send_byte_UART_int('3');
	//	Timer0Teller++;
	//	if (Timer0Teller > 10000) {
	//		Timer0Teller = 0;
	//		Toggle(RE0);
	//	}
	//	TMR0IF = 0; //clear interrupt flag
	//}

	//if (ADIF) { //AD-conversion int-flag
	//	ADIF = 0; //clear
	//}

	else if (RCIF) { //USART Receive int-flag
		//RCIF cleared when read:
		//RXbuffer[RXptr] = RCREG;
		RXbuffer[RXptr] = rec_byte_UART();
		RXptr++;
		if (RXptr > 31) {
			RXptr = 0;
			RXshowData = 1;
		}
	}

	//if (TXIF) { //USART TX int-flag, TX-buffer is empty
	//	//TXIF cleared when TXREG is written - not used here
	//}
	//
	//if (CCP1IF) { //CCP1 int-flag
	//	//Capture mode: TMR1 capture occured
	//	//Compare mode: TMR1 compare occured
	//	CCP1IF = 0; //clear
	//}
	//
	//if (TMR1IF) { //Timer1
	//	TMR1IF = 0; //clear
	//}
	//
	//if (TMR2IF) { //Timer2
	//	TMR2IF = 0; //clear
	//}
	//
	//
	//if (EEIF) { //Data EEPROM/FLASH write operation intflag
	//	EEIF = 0; //clear
	//}
	//
	//if (BCLIF) { //Bus collision int-flag
	//	BCLIF = 0;
	//}
	//
	//if (TMR3IF) { //Timer3
	//	TMR3IF = 0; //clear
	//}
	//
	//if (CCP2IF) { //CCPx int-flag
	//	CCP2IF = 0;
	//}
}

