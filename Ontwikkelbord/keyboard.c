#include "keyboard.h"

void KeyboardInit(void) {
	TRISD = 0x0F; 
	PORTD = 0x00; 
}

unsigned char KeyboardRead(void) {
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
	
	KeyboardInit();
	return key;
}
