/*
	
Filename:
	keyboard.h
	
Description:
	Header file voor keyboard functie (uitlezen).

Authors:
	JM (TiC)
	FW (EA)
	NHL  2003/2004

Log:
	10/1/2004:
		Eerste lancering voor schakelklok


*/

#define KEYBOARD_X0	RD0
#define KEYBOARD_X1	RD1
#define KEYBOARD_X2	RD2
#define KEYBOARD_X3	RD3
#define KEYBOARD_Y0	RD4
#define KEYBOARD_Y1	RD5
#define KEYBOARD_Y2	RD6
#define KEYBOARD_Y3	RD7

#define KEYBOARD_UNDEFINED_STATE 0xFF

#define KEY_1		0x01
#define KEY_2		0x02
#define KEY_3		0x03
#define KEY_4		0x04
#define KEY_5		0x05
#define KEY_6		0x06
#define KEY_7		0x07
#define KEY_8		0x08
#define KEY_9		0x09
#define KEY_0		0x00
#define KEY_A		0x0A
#define KEY_B		0x0B
#define KEY_C		0x0C
#define	KEY_D		0x0D
#define	KEY_DASH	0x0E
#define KEY_STAR	0x0F

#define ENABLE_KEYBOARD_FUNCTION 1

void initKeyboard(void);
unsigned char readKeyboard(void);
void enableKeyboard(void);
