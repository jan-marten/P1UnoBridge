/*
 *	LCD interface example
 *	Uses routines from delay.c
 *	This code will interface to a standard LCD controller
 *	like the Hitachi HD44780. It uses it in 4 or 8 bit mode
 *	
 */

#include	<pic18.h>
#include	"lcd.h"
#include	"delay.h"
 

/* send a command to the LCD */
void lcd_cmd(unsigned char c) {
	LCD_WAIT; // may check LCD busy flag, or just delay a little, depending on lcd.h

	LCD_DATA = ( ( c >> 4 ) & 0x0F );
	LCD_STROBE();
	LCD_DATA = ( c & 0x0F );
	LCD_STROBE();
}

/* send data to the LCD */
void lcd_data(unsigned char c) {
	
	unsigned char temp;

	LCD_WAIT; // may check LCD busy flag, or just delay a little, depending on lcd.h

	//LCD_DATA = 0;
	LCD_D4 = LCD_D5 = LCD_D6 = LCD_D7 = 0;
	LCD_RS = 1;
		
	// High nibble

	temp = (c / 16); //shift right
	if (temp & 0x01)
		LCD_D7 = 1;
	if (temp & 0x02)
		LCD_D6 = 1;
	if (temp & 0x04)
		LCD_D5 = 1;
	if (temp & 0x08)
		LCD_D4 = 1;

	LCD_STROBE();

	// low nibble
	
	LCD_D4 = LCD_D5 = LCD_D6 = LCD_D7 = 0;

	temp = c & 0x0F;
	if (temp & 0x01)
		LCD_D7 = 1;
	if (temp & 0x02)
		LCD_D6 = 1;
	if (temp & 0x04)
		LCD_D5 = 1;
	if (temp & 0x08)
		LCD_D4 = 1;

	LCD_STROBE();

	LCD_RS = 0;
}

/* write a string of chars to the LCD */

void lcd_puts(const char * s) {
	while(*s) {
		lcd_data(*s++);
	}
}

void lcd_string(const char * s) {
	// Deze routine gooit een string van 16 karakters naar het display.
	// Speciaal gemaakt voor 1x16-karakter LCD display
	unsigned char i;
	lcd_goto(0);
	for (i=0; i<8; i++) {
		lcd_data(*s++);
	}
	lcd_goto(43);
	for (i=0; i<8; i++) {
		lcd_data(*s++);
	}	
}

/* initialize the LCD */
void lcd_init() {

//1. Display clear
//
//2. Function set ..... DL = 1: 8 bit interface
//                       N = 0: 1 line display
//                       F = 0: 5 x 7 dot character font
//
//3. Display ON/OFF ...  D = 0: Display OFF
//                       C = 0: Cursor OFF
//                       B = 0: Blink OFF
//
//4. Entry mode set .. I/D = 1: +1 (increment)
//                       S = 0: No shift
//
//5. Write DD RAM
//   When the rise time of power supply (0.2 -> 4.5) is out
//   of the range 0.1ms - 10ms, or when the low level width
//   of power OFF (less than 0.2) is less than 1ms, the
//   internal reset circuit will not operate normally.
//   In this case, initialisation will not be performed
//   normally. Initialise by instruction, as detailed below.
//
//If the power supply conditions for correctly operating the internal reset circuit are not met, initialisation by instruction is required.
	
//        [Power ON]
//
//[  Wait more than 15ms  ]
//[after Vdd rises to 4.5v]
//

	DelayMs(15);

//RS  R/W DB7 DB6 DB5 DB4  Can't check BF before this instruction
// 0   0   0   0   1   1   Function set (8-bit interface)
//

	//LCD_DATA = 0x03;
	LCD_D4 = 1;
	LCD_D5 = 1;
	LCD_D6 = 0;
	LCD_D7 = 0;
	LCD_RS = 0;
	LCD_STROBE();

//    [Wait more than]
//    [     4.1ms    ]
//

	DelayMs(5);

//RS  R/W DB7 DB6 DB5 DB4  Can't check BF before this instruction
// 0   0   0   0   1   1   Function set (8-bit interface)
//

	//LCD_DATA = 0x03;
	LCD_D4 = 1;
	LCD_D5 = 1;
	LCD_D6 = 0;
	LCD_D7 = 0;
	LCD_RS = 0;
	LCD_STROBE();

//    [Wait more than]
//    [     100us    ]
//

	DelayUs(200);

//RS  R/W DB7 DB6 DB5 DB4  Can't check BF before this instruction
// 0   0   0   0   1   1   Function set (8-bit interface)
//
//                         BF can be checked after the following
//                         instructions. When BF is not checked,
//                         the waiting time between instructions
//                         is longer than the execution time.
//                         (See Instruction set)
//

	//LCD_DATA = 0x03;
	LCD_D4 = 1;
	LCD_D5 = 1;
	LCD_D6 = 0;
	LCD_D7 = 0;
	LCD_RS = 0;
	LCD_STROBE();

//RS  R/W DB7 DB6 DB5 DB4
// 0   0   0   0   1   0   Function set (to 4-bit interface)
//

	//LCD_DATA = 0x02;
	LCD_D4 = 0;
	LCD_D5 = 1;
	LCD_D6 = 0;
	LCD_D7 = 0;
	LCD_RS = 0;
	LCD_STROBE();
	// komt ook voor in volgende cmd...???

//RS  R/W DB7 DB6 DB5 DB4
// 0   0   0   0   1   0
// 0   0   N   F   *   *   Function set  [4-bit Interface      ]
//                                       [Specify display lines]
//										 [and character font   ]
//											These cannot be
//											changed afterwards

	//LCD_DATA = 0x02;
	LCD_D4 = 0;
	LCD_D5 = 1;
	LCD_D6 = 0;
	LCD_D7 = 0;
	LCD_RS = 0;
	LCD_STROBE();
	//LCD_DATA = 0x00;
	LCD_D4 = 0;
	LCD_D5 = 0;
	LCD_D6 = 0;
	LCD_D7 = 0;
	LCD_RS = 0;
	LCD_STROBE();

	DelayUs(200);


//RS  R/W DB7 DB6 DB5 DB4                
// 0   0   0   0   0   0                  
// 0   0   1   0   0   0   Display OFF    
//                                        

	//LCD_DATA = 0x00;
	LCD_D4 = 0;
	LCD_D5 = 0;
	LCD_D6 = 0;
	LCD_D7 = 0;
	LCD_RS = 0;
	LCD_STROBE();
	//LCD_DATA = 0x08;
	LCD_D4 = 0;
	LCD_D5 = 0;
	LCD_D6 = 0;
	LCD_D7 = 1;
	LCD_RS = 0;
	LCD_STROBE();

	DelayUs(200);

//RS  R/W DB7 DB6 DB5 DB4
// 0   0   0   0   0   0   
// 0   0   0   0   0   1   Display ON
//

	//LCD_DATA = 0x00;
	LCD_D4 = 0;
	LCD_D5 = 0;
	LCD_D6 = 0;
	LCD_D7 = 0;
	LCD_RS = 0;
	LCD_STROBE();
	//LCD_DATA = 0x01;
	LCD_D4 = 1;
	LCD_D5 = 0;
	LCD_D6 = 0;
	LCD_D7 = 0;
	LCD_RS = 0;
	LCD_STROBE();

	DelayUs(200);

//RS  R/W DB7 DB6 DB5 DB4 
// 0   0   0   0   0   0   
// 0   0   0   1  I/D  S   entry mode set
	
	//LCD_DATA = 0x00;
	LCD_D4 = 0;
	LCD_D5 = 0;
	LCD_D6 = 0;
	LCD_D7 = 0;
	LCD_RS = 0;
	LCD_STROBE();
	//LCD_DATA = 0x06;
	LCD_D4 = 0;
	LCD_D5 = 1;
	LCD_D6 = 1;
	LCD_D7 = 0;
	LCD_RS = 0;
	LCD_STROBE();

	DelayUs(200);
	
	
}



