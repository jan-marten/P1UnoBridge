#include <pic18.h>
#include "display.h"

#define	LCDE		RA5  		/*Lcd Enable signal*/	
#define	LCDRS		RA4    		/*Lcd RS signal*/

#define	LCD4		RA0     	/*Lcd data bus*/
#define	LCD5		RA1      	/*Lcd data bus*/
#define	LCD6		RA3        	/*Lcd data bus*/
#define	LCD7		RA2        	/*Lcd data bus*/

#define	LCDRESTIME	11000 		/*reset sequence delay=16ms*/
#define	LCDCOMTIME	1400		/*command delay=2ms*/
#define	LCDDATTIME	33    		/*data delay=50us*/
 
/*local functions*/ 
void DisplayNibble(unsigned char data);
void DisplayDelay(unsigned short delay); 
 
/*************************************************************************************/
/*external interface routines*/
/*************************************************************************************/
    
/*Reset LCD controller and select 4-bit interface, note that the lcd must still 
be configured for one/two line and entry mode etc.*/
void DisplayInit(void)
{                                          
    /*select instruction register*/
    LCDRS = 0;
        
    /*make sure E is set alright*/
    DisplayNibble(0x00);

    /*execute reset sequence*/
    DisplayDelay(LCDRESTIME); 
    DisplayNibble(0x03);
    DisplayDelay(LCDRESTIME); 
    DisplayNibble(0x03);
    DisplayDelay(LCDRESTIME); 
    DisplayNibble(0x03);
    DisplayDelay(LCDRESTIME); 
    DisplayNibble(0x02);
    DisplayDelay(LCDRESTIME); 	

} 

/*send a command to the lcd controller*/
void DisplayCommand(unsigned char command)
{
	/*select instruction register*/
	LCDRS = 0;

    /*write high nibble*/
    DisplayNibble(command / 16);
    /*write low nibble*/
    DisplayNibble(command);
    /*give controller time to finish*/
    DisplayDelay(LCDCOMTIME);

}

/*send data to the LCD's ram*/
void DisplaySend(const unsigned char *data, unsigned char length)
{
    /*select data register*/
    LCDRS = 1;                      

    while(length--)
    {
        /*write high nibble*/
        DisplayNibble(*data/16);
        /*write low nibble*/
        DisplayNibble(*(data++));
        /*give controller time to finish*/
        DisplayDelay(LCDDATTIME);
    }
}

/*************************************************************************************/
/*internal routines*/
/*************************************************************************************/

/*send a single nibble to the lcd*/             
void DisplayNibble(unsigned char data)
{
    /*set data*/    
    LCD4 = 0;
    LCD5 = 0;
    LCD6 = 0;
    LCD7 = 0;
    if (data & 0x01)
        LCD4 = 1;
    if (data & 0x02)
        LCD5 = 1;
    if (data & 0x04)
        LCD6 = 1;
    if (data & 0x08)
        LCD7 = 1;
        
    /*select write mode*/
    //LCDRW=0; //already 0

    /*pulse E*/
    LCDE = 1;
    // asm("nop");
    // asm("nop");
    // asm("nop");
    // asm("nop");
    // asm("nop");
    DisplayDelay(5);
    LCDE = 0;
}                                 

/*wait some time*/      
void DisplayDelay(unsigned short delay)
{   	
    while(delay--) asm("nop");
}

void DisplaySendLines(unsigned char *line1, 
                  unsigned char *line2, 
                  unsigned char *line3, 
                  unsigned char *line4) {
    //position 1
    DisplayCommand(LCD_CLS); 
    DisplaySend(line1, 20);
    DisplaySend(line3, 20);
    DisplaySend(line2, 20);
    DisplaySend(line4, 20);
}
