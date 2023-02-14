/* *******************************************************************************
* File:  I2Cutils.h
*        Functions declarations used for the I2C interface to the LCD-Keypad pair.                        
*
********************************************************************************  */

// INCLUDE FILES
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

// Constants' DECLARAITONS
#define LCD 0xC6        // LCD slave address
#define Reg0 0x00       // Register 0 (writable command register of LCD)
#define CLRSCRN 0x0C    // Clear screen and and set cursor to home position
#define BACK_LIGHT_OFF 0x14 // Turns on LCD backlight
#define BACK_LIGHT_ON 0x13  // Turns on LCD backlight
#define CURSORbox 0x02      // Cursor(cell location) command
#define LN_COL 0x03         // Cursor(line,column) command 

//  Functions' DECLARATIONS 
/*** Data transfert ***/
void String_to_LCD(char *s);
unsigned char *Read_LCD_Regs(unsigned char LCD_Address);
void Write_Cmd0(unsigned char LCD_Address, unsigned char data);
void Write_Cmd1(unsigned char LCD_Address, unsigned char cursor_position);
void Write_Cmd2(unsigned char LCD_Address, unsigned char line, unsigned char column);
/*** Useful approximate delays ***/
void delay100msec_x_N (int N);
void delay100msec(void);
void delay10msec(void);
void delay20usec(void);

