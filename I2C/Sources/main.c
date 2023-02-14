/********************************************************
*  File descripton
*  This code test and controls the LCD I2C slave device
*  It detects that a key has been pressed on a keypad
*  and displays the value of this key on the LCD display
*********************************************************/

#include <hidef.h>      /* common defines and macros */
#include <stdio.h>
#include "derivative.h"      /* derivative-specific definitions */
#include "i2c_utils.h"
#include "initMICRO.h"

// VARIALES                          
char strg1[]= "Testing LCD/Keypad";
char strg2[]= "Press a key: " ;
char strg3[]= "Key pressed was: ";
char strg[80];                      // Reserve space for 80 characters
unsigned char *key;                 // Pointer to space to hold reading of keyboard
char keypad[] = "123456789*0#";     // String of characters found on keypad.

// Other declarations as required


/*** MAIN SOURCE CODE ***/

void main(void) 
{

// Part 1 - Setting HCS12 and I2C device

/**** ENTER CODE HERE TO MEET REQUIREMENTS 1 and 2  ****/
 
 // Initialize ECLK
 setECLK_MODE();
 
 //
 IBCR = 0x80; // I2C enabled, no interrupt, slave mode. Remaining registers are 0. 
 IBFD = 0x20; // IBFD clock rate set to 100KHz.
 IBSR = 0x02; // clear pending flags                                                                                                                                      0;
 
 Write_Cmd0(LCD, BACK_LIGHT_ON); //  Turn LCD back light on.
 
 Write_Cmd0(LCD, CLRSCRN);  //  clear the screen.
 
 String_to_LCD("Testing LCD/keypad"); //  send the string to LCD
 
 Write_Cmd2(LCD, 2, 5);                                        // and move cursor to (2, 5).
 
 //delay or wait for a key to be pressed to allow reading of display.
 delay100msec_x_N (100);
 
 Write_Cmd0(LCD, CLRSCRN);  //clear the screen.
 
 String_to_LCD("Press a key: "); 
 
 
 while(key[1] == 0b00000000 && key[2] == 0b00000000) {
  key = Read_LCD_Regs(LCD);
     // String_to_LCD("in while loop")  ;
     //     delay100msec_x_N (100);
 }
 
             /*
 if (key[1] == 0b00000001) {
    key = "1";
 } else if (key[1] == 0b00000010) {
    key = "2
 } else if (key[1] == 0b00000100) {
    key = "3";
 } else if (key[1] == 0b00001000) {
    key = "4";
 } else if (key[1] == 0b00010000) {
    key = "5";
 } else if (key[1] == 0b00100000) {
  
 }        */
  
 switch(key[1]){
  case 0b00000001:
    key = "1";
    break;
    case 0b00000010:
    key = "2";
    break;
    case 0b00000100:
    key = "3";
    break;
    case 0b00001000:
    key = "4";
    break;
    case 0b00010000:
    key = "5";
    break;
    case 0b00100000:
    key = "6";
    break;
    case 0b01000000:
    key = "7";
    break;
    case 0b10000000:
    key = "8";
    break;
 }
  switch(key[2]){
  case 0b00000001:
  key = "9";
  break;
  case 0b00000010:
    key = "*";
    break;
    case 0b00000100:
    key = "0";
    break;
    case 0b00001000:
    key = "#";
    break;
    default:
    key = "0";
 }
 
  Write_Cmd1(LCD, 0x2A);    // and move cursor to cell 41.   
  String_to_LCD("Key pressed was ");   
  String_to_LCD(key);   
 
 
// Part 2 - Test and use LCD/Keypad

/**** ENTER CODE HERE TO MEET OTHER REQUIREMENTS  ****/




/*************************************************************/         
 for (;;) {asm("NOP");}    // Just in case, stay here

}
