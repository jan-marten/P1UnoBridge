

//#define BAUD_9600  51 //geregeld in bootloader!
//#define BAUD_19200 25


#define TERMINAL_BELL		0x07
#define TERMINAL_BACKSPACE	0x08
#define TERMINAL_TAB		0x09
#define TERMINAL_LF			0x0A
#define TERMINAL_FF			0x0C
#define TERMINAL_CR			0x0D


// prototypings etcetera go here...

unsigned char RXbuf[32];
unsigned char RXbuf_ptr;


//void init_UART(unsigned char); // geregeld in Bootloader?
void init_UART(void); // geregeld in Bootloader!
void send_byte_UART(unsigned char);
void send_byte_UART_int(unsigned char);
//unsigned char read_byte_UART(void); --> through Seriele Interrupt

void cleanerror_UART(void);
void send_string_UART(unsigned char *);
void send_string_UART_int(unsigned char *);

