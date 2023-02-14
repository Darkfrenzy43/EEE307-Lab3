/* *******************************************************************************
* File:  initMICRO.c
*
* Description: To set ECLK speed and mode of operation                      
*
********************************************************************************  */

// INCLUDE FILES
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "initMICRO.h"

/**** FUNCTION DEFINITIONS ******/

/************************************************************************
*  Function: void setECLK_MODE(void)
*
*  Description: The crystal osscilator on the HCS12DP512 processor 
*       is input into a phase-locked-loop module that multiplies and 
*       divides the ECLK by integer values
*     ECLK = OSCCLK * (SYNR+1)/(REFDV+1)
*     Note: For LABS 1-3, board OSCCLK =  4 MHz
*           For LABS 4-7, board OSCCLK = 16 MHz
*  REFERENCES: Valvano Sec 1.8 Page 46
*    and S12CRGV4.pdf  Clock and Reset Generator Block User Guide (Motorola)
* ***********************************************************************/

void setECLK_MODE(void) 
  {
  // REQUIREMENTS: Set SYNR and REFDV values to obtain the desired ECLK rate

    SYNR = 0x07;
   REFDV = 0x01;
   
  CLKSEL = 0x00; // Ensure the clock is drive from the crystal initially
                 // PLLSEL | PSTP | SYSWAI | ROAWAI | PLLWAI | CWAI | RTIWAI | COPWAI 
  PLLCTL = 0xD1; // Set PLL control
                 // CME | PLLON | AUTO | ACQ | 0 | PRE | PCE | SCME
     
  // Wait for PLLCLK to stabilize
  while   ((CRGFLG & CRGFLG_LOCK_MASK)==0);
  CLKSEL |= CLKSEL_PLLSEL_MASK; // Set the CLKSEL bit to take ECLK = PLLCLK/2
  
   // Set MODE of operation
  MODE = 0x80;   // Set HCS12 in normal single-chip mode
  MISC = 0x01;   // Turn ON the Flash ROM
  // PEAR = PEAR_RDWE_MASK|PEAR_LSTRE_MASK;  // Useful for external interfacing  
  }
 