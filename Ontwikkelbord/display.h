#ifndef DISPLAY_H_INCLUDED
#define DISPLAY_H_INCLUDED      

#define	LCD_CLS			0x01 	/*Clear screen*/
#define	LCD_HOME		0x02  	/*Cursor home*/
#define	LCD_STDENTRY	0x06    /*select standard entry format*/
#define	LCD_ONELINE		0x20   	/*select 1 line display*/
#define	LCD_TWOLINE		0x28   	/*select 2 line display*/
#define	LCD_ON			0x0c  	/*switch lcd on*/

void DisplayInit(void);
void DisplayCommand(unsigned char command);
void DisplaySend(const unsigned char *data, unsigned char length);
void DisplaySendLines(unsigned char *, unsigned char *, unsigned char *, unsigned char *);
#endif
