/*
	interrupts.c
*/

#include "interrupts.h"

void init_INT(void){

	IPEN	= 0; // Priority disabled
	//RCON	= RCON; // Hmz, lees documentatie na (pag 84)
	IPR2	= 0x1F; // Prio, standaard (0x1F)
	IPR1	= 0xFF; // Prio, standaard (0xFF)
	PIE2	= 0x00;

	PIR2	= 0x00;
	PIR1	= 0x00;
	INTCON3	= 0xD8;
	INTCON2	= 0x35; // let op: RBPU wordt ook al gezet in main.c!
	INTCON	= 0xD0; // als laatste, enabled alle interrupts
	
	
	init_INT_Usart1();
	
}


void init_Timer0(void){
	T0CON = 0xFF;
}

void init_INT_Usart1() 
{
	// 8.3 PIE Registers
	// The PIE registers contain the individual enable bits for
	// the peripheral interrupts. Due to the number of peripheral
	// interrupt sources, there are two Peripheral Interrupt
	// Enable Registers (PIE1, PIE2). When IPEN = 0,
	// the PEIE bit must be set to enable any of these
	// peripheral interrupts.
	// REGISTER 8-6: PIE1: PERIPHERAL INTERRUPT ENABLE REGISTER 1
	// R/W-0 R/W-0 R/W-0 R/W-0 R/W-0 R/W-0 R/W-0 R/W-0
	// PSPIE(1) ADIE RCIE TXIE SSPIE CCP1IE TMR2IE TMR1IE
	
	// bit 7 bit 0
	// bit 7 PSPIE(1): Parallel Slave Port Read/Write Interrupt Enable bit
	// 1 = Enables the PSP read/write interrupt
	// 0 = Disables the PSP read/write interrupt
	
	// bit 6 ADIE: A/D Converter Interrupt Enable bit
	// 1 = Enables the A/D interrupt
	// 0 = Disables the A/D interrupt
	
	// bit 5 RCIE: USART Receive Interrupt Enable bit
	// 1 = Enables the USART receive interrupt
	// 0 = Disables the USART receive interrupt
	
	// bit 4 TXIE: USART Transmit Interrupt Enable bit
	// 1 = Enables the USART transmit interrupt
	// 0 = Disables the USART transmit interrupt
	
	// bit 3 SSPIE: Master Synchronous Serial Port Interrupt Enable bit
	// 1 = Enables the MSSP interrupt
	// 0 = Disables the MSSP interrupt
	
	// bit 2 CCP1IE: CCP1 Interrupt Enable bit
	// 1 = Enables the CCP1 interrupt
	// 0 = Disables the CCP1 interrupt
	
	// bit 1 TMR2IE: TMR2 to PR2 Match Interrupt Enable bit
	// 1 = Enables the TMR2 to PR2 match interrupt
	// 0 = Disables the TMR2 to PR2 match interrupt
	
	// bit 0 TMR1IE: TMR1 Overflow Interrupt Enable bit
	// 1 = Enables the TMR1 overflow interrupt
	// 0 = Disables the TMR1 overflow interrupt
	
	// Note 1: This bit is reserved on PIC18F2X2 devices; always maintain this bit clear.
	// Legend:
	// R = Readable bit W = Writable bit U = Unimplemented bit, read as ‘0’
	// - n = Value at POR ’1’ = Bit is set ’0’ = Bit is cleared x = Bit is unknown	
	
	PIE1	= 0x20; // hier zit usart ook in: RX wel, TX geen interrupt
	//PIE1	= 0x00; // hier zit usart ook in: RX wel, TX geen interrupt
	
	
	
	
}
