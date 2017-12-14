/**
  TMR0 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    tmr0.c

  @Summary
    This is the generated driver implementation file for the TMR0 driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This source file provides APIs for TMR0.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.55
        Device            :  PIC18F25K42
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.43
        MPLAB 	          :  MPLAB X 4.00
*/

/**
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/

#include <xc.h>
#include "tmr0.h"


/**
  Section: TMR0 APIs
*/


void TMR0_Initialize(void)
{
    // Set TMR0 to the options selected in the User Interface

    // T0CS LFINTOSC; T0CKPS 1:32; T0ASYNC synchronised; 
    T0CON1 = 0x85;

    // TMR0H 96; 
    TMR0H = 0x60;

    // TMR0L 0; 
    TMR0L = 0x00;

    // Clearing IF flag
    PIR3bits.TMR0IF = 0;

    // T0OUTPS 1:1; T0EN enabled; T016BIT 8-bit; 
    T0CON0 = 0x80;
}

void TMR0_StartTimer(void)
{
    // Start the Timer by writing to TMR0ON bit
    T0CON0bits.T0EN = 1;
}

void TMR0_StopTimer(void)
{
    // Stop the Timer by writing to TMR0ON bit
    T0CON0bits.T0EN = 0;
}

uint8_t TMR0_Read8bitTimer(void)
{
    uint8_t readVal;

    // read Timer0, low register only
    readVal = TMR0L;

    return readVal;
}

void TMR0_Write8bitTimer(uint8_t timerVal)
{
    // Write to Timer0 registers, low register only
    TMR0L = timerVal;
 }

void TMR0_Load8bitPeriod(uint8_t periodVal)
{
   // Write to Timer0 registers, high register only
   TMR0H = periodVal;
}

bool TMR0_HasOverflowOccured(void)
{
    // check if  overflow has occurred by checking the TMRIF bit
    return(PIR3bits.TMR0IF);
}
/**
  End of File
*/