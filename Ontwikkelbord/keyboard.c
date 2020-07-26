
#include "keyboard.h"


/*********************  leesKeyBoard :: ISR  ******************************/
unsigned char leesToetsAanslag(void) {
	//
	//	Leest het toetsenbord uit zodra er een toetsaanslag is geweest.
	//

	unsigned char key;
	key = KEYBOARD_UNDEFINED_STATE;
	DelayMs(10); // anti-dender wachten

	if (!KEYBOARD_X0 && KEYBOARD_X1 && KEYBOARD_X2 && KEYBOARD_X3) {
		TRISD = 0xF0;
		DelayMs(1);
		if (!KEYBOARD_Y0) key = KEY_1;
		if (!KEYBOARD_Y1) key = KEY_4;
		if (!KEYBOARD_Y2) key = KEY_7;
		if (!KEYBOARD_Y3) key = KEY_STAR;
	} 
	if (KEYBOARD_X0 && !KEYBOARD_X1 && KEYBOARD_X2 && KEYBOARD_X3) {
		TRISD = 0xF0;
		DelayMs(1);
		if (!KEYBOARD_Y0) key = KEY_2;
		if (!KEYBOARD_Y1) key = KEY_5;
		if (!KEYBOARD_Y2) key = KEY_8;
		if (!KEYBOARD_Y3) key = KEY_0;

	} 
	if (KEYBOARD_X0 && KEYBOARD_X1 && !KEYBOARD_X2 && KEYBOARD_X3) {
		TRISD = 0xF0;
		DelayMs(1);
		if (!KEYBOARD_Y0) key = KEY_3;
		if (!KEYBOARD_Y1) key = KEY_6;
		if (!KEYBOARD_Y2) key = KEY_9;
		if (!KEYBOARD_Y3) key = KEY_DASH;
	} 
	if (KEYBOARD_X0 && KEYBOARD_X1 && KEYBOARD_X2 && !KEYBOARD_X3) {
		TRISD = 0xF0;
		DelayMs(1);
		if (!KEYBOARD_Y0) key = KEY_A;
		if (!KEYBOARD_Y1) key = KEY_B;
		if (!KEYBOARD_Y2) key = KEY_C;
		if (!KEYBOARD_Y3) key = KEY_D;
	} 
	//else {
		//key = 0x10; // Not possible!
	//	key = KEYBOARD_UNDEFINED_STATE; // No button is pressed.
	//}

	
	init_KeyBoard();
	return key;
}

void enableKeyboard(void) {
	// toest is afgehandeld
	//IE1 = 0; // reset interrupt
	//EX1 = 1; // interrupt enable
	//key = KEYBOARD_UNDEFINED_STATE;
}

void init_KeyBoard(void) {
	TRISD = 0x0F; 
	PORTD = 0x00; 
}
