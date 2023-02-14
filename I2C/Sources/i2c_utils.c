/* *******************************************************************************
* File:  I2Cutils.c
*        Functions definintions used for the I2C interface to the LCD-Keypad pair.                          
*
**********************************************************************************/

// INCLUDE FILES
#include <hidef.h>       /* common defines and macros */
#include "derivative.h"  /* derivative-specific definitions */
#include "i2c_utils.h" 

// VARIABLES' DECLARATIONS
unsigned char keyval[4];


// FUNCTION DEFINITIONS

/*******************************************************
* Function: void String_to_LCD(char *s)
* Description: sends a character string to the LCD
* Input:  pointer to start address of character string
* Output: character string to LCD
********************************************************/
void String_to_LCD(char *s) {
  int x;
  for(x=0; s[x]!='\0'; x++)
  Write_Cmd0(LCD,s[x]);
}

/*********************************************************************
* Function: unsigned char *Read_LCD_Regs(unsigned char LCD_Address)
* Description: reads the four registers of the LCD
* Input:  address of the LCD slave device
* Output: register data (4 bytes) returned via character array
**********************************************************************/
unsigned char *Read_LCD_Regs(unsigned char LCD_Address) {

  while (IBSR_IBB) {};              // loop while bus is busy
  IBCR |= 0x30;                     // MS/SL=1, TX/RX=1
  IBDR = (LCD_Address | 0x01);      // Transmit Slave address, Read mode R/W = 1
  while ((IBSR & 0x02) == 0) {};    // Loop while transfer takes place
  IBSR_IBIF = 1;                    // Clear transfer complete flag (via IBIF)
  
  IBCR_TXAK = 0;                    // Prepare ACK to acknowledge data
  IBCR_TX_RX = 0;                   // Data to be read
  keyval[0] = IBDR;                 // Dummy read to initiate receiving
  while ((IBSR & 0x02) == 0) {};    // Loop while transfer takes place
  IBSR_IBIF = 1;                    // Clear transfer complete flag (via IBIF)
  
  keyval[0] = IBDR;                 // Read first byte
  while ((IBSR & 0x02) == 0) {};    // Loop while transfer takes place
  IBSR_IBIF = 1;                    // Clear transfer complete flag (via IBIF)
    
  keyval[1] = IBDR;                 // Read second byte
  while ((IBSR & 0x02) == 0) {};    // Loop while transfer takes place
  IBSR_IBIF = 1;                    // Clear transfer complete flag (via IBIF)
  
  IBCR_TXAK = 1;                    // Prepare NACK to indicate last read
  keyval[2] = IBDR;                 // What is purpose of this read?
  while ((IBSR & 0x02) == 0) {};    // Loop while transfer takes place
  IBSR_IBIF = 1;                    // Clear transfer complete flag (via IBIF)
  
  IBCR &= 0b11000111 ;              // MS/SL=0, TX/RX=0, TXAK=0, other bits kept
  keyval[3] = IBDR;                 // What is purpose of this read?
  
  return keyval;
   
}

/***************************************************************************
* Function: void Write_Cmd0(unsigned char LCD_Address, unsigned char data)
* Description: send a one ASCII character to the LCD
* Inputs:  address of the LCD slave device and ASCII code of character
* Output: command to LCD
***************************************************************************/

void Write_Cmd0(unsigned char LCD_Address, unsigned char data) {
  
  while (IBSR_IBB) {};              // loop while bus is busy
  IBCR |= 0x30;                     // MS/SL=1, TX/RX=1
  IBDR = LCD_Address & 0xFE;        // Transmit Slave address, Read mode R/W = 0
  while ((IBSR & 0x02) == 0) {};    // Loop while transfer takes place
  IBSR_IBIF = 1;                    // Clear transfer complete flag (via IBIF) 
  
  IBDR = Reg0;                      // Address Command Register
  while ((IBSR & 0x02) == 0) {};    // Loop while transfer takes place
  IBSR_IBIF = 1;                    // Clear transfer complete flag (via IBIF)  
  
  IBDR = data;                      // Write ASCII character (32-255) to LCD
  while ((IBSR & 0x02) == 0) {};    // Loop while transfer takes place
  IBSR_IBIF = 1;                    // Clear transfer complete flag (via IBIF)

  IBCR &= 0b11001111 ;              // MS/SL=1->0 = STOP, TX/RX=0 
}

/*************************************************************************************
* Function: void Write_Cmd1(unsigned char LCD_Address, unsigned char cursor_position)
* Description: send a command to the LCD to place cursor in specific cell
* Input:  address of the LCD slave device and cell position value
* Output: place LCD cursor in specified cell position
**************************************************************************************/
void Write_Cmd1(unsigned char LCD_Address, unsigned char cursor_position) {
  
  while (IBSR_IBB) {};              // loop while bus is busy
  IBCR |= 0x30;                     // MS/SL=1, TX/RX=1
  IBDR = LCD_Address & 0xFE;        // Transmit Slave address, Read mode R/W = 0
  while ((IBSR & 0x02) == 0) {};    // Loop while transfer takes place
  IBSR_IBIF = 1;                    // Clear transfer complete flag (via IBIF) 
  
  IBDR = Reg0;                      // Address Command Register
  while ((IBSR & 0x02) == 0) {};    // Loop while transfer takes place
  IBSR_IBIF = 1;                    // Clear transfer complete flag (via IBIF)  

  IBDR = CURSORbox;                 // Cursor(location) command
  while ((IBSR & 0x02) == 0) {};    // Loop while transfer takes place
  IBSR_IBIF = 1;                    // Clear transfer complete flag (via IBIF)

  IBDR = cursor_position;           // Write 1 of 80 locations.
  while ((IBSR & 0x02) == 0) {};    // Loop while transfer takes place
  IBSR_IBIF = 1;                    // Clear transfer complete flag (via IBIF)

  IBCR &= 0b11001111 ;              // MS/SL=1->0 = STOP, TX/RX=0
}

/***********************************************************************************************
* Function: void Write_Cmd2(unsigned char LCD_Address, unsigned char line, unsigned char column)
* Description: send a command to the LCD to place cursor in specific cell
* Input:  address of the LCD slave device and cell line,column coordinates
* Output: place LCD cursor in specified cell position
************************************************************************************************/
void Write_Cmd2(unsigned char LCD_Address, unsigned char line, unsigned char column) {
  
  while (IBSR_IBB) {};              // loop while bus is busy
  IBCR |= 0x30;                     // MS/SL=1, TX/RX=1
  IBDR = LCD_Address & 0xFE ;       // Transmit Slave address, Read mode R/W = 0
  while ((IBSR & 0x02) == 0) {};    // Loop while transfer takes place
  IBSR_IBIF = 1;                    // Clear transfer complete flag (via IBIF) 
  
  IBDR = Reg0;                      // Address Command Register
  while ((IBSR & 0x02) == 0) {};    // Loop while transfer takes place
  IBSR_IBIF = 1;                    // Clear transfer complete flag (via IBIF)  

  IBDR = LN_COL;                    // Cursor(line,column) command
  while ((IBSR & 0x02) == 0) {};    // Loop while transfer takes place
  IBSR_IBIF = 1;                    // Clear transfer complete flag (via IBIF)

  IBDR = line;                      // Write line number (1 of 4)
  while ((IBSR & 0x02) == 0) {};    // Loop while transfer takes place
  IBSR_IBIF = 1;                    // Clear transfer complete flag (via IBIF)
  
  IBDR = column;                    // Write column number (1 of 20)
  while ((IBSR & 0x02) == 0) {};    // Loop while transfer takes place
  IBSR_IBIF = 1;                    // Clear transfer complete flag (via IBIF)

  IBCR &= 0b11001111 ;              // MS/SL=1->0 = STOP, TX/RX=0
  
}

/********************************************
* Function: void delay100msec_x_N (int N)
* Description: Generates a delay
* Input:  N = number of 100ms delays
* Output: Delay = Nx100mse
*********************************************/
void delay100msec_x_N (int N) {
  int i;
  for(i=0; i<N; i++) delay100msec(); }

/********************************************
* Function: void delay100msec(void)
* Description: Generates a delay
* Input:  None
* Output: Delay = ~100ms
*********************************************/
void delay100msec(void) {
  int i;
  for(i=0; i<10; i++) delay10msec(); }

/*********************************************
* Function: void delay10msec(void)
* Description: Generates a delay
* Input:  None
* Output: Delay = ~10ms
**********************************************/
void delay10msec(void){
  int i;
  for(i=0; i<5000; i++);
  asm("NOP"); }

/**********************************************
* Function: void delay20usec(void)
* Description: Generates a delay
* Input:  None
* Output: Delay = ~20us
***********************************************/
void delay20usec(void){
 int i;
  for(i=0; i<20; i++);
  asm("NOP"); }  // takes 1 ECLK cycle
/**********************************************/