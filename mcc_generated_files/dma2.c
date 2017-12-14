/**
  DMA Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    dma2.c

  @Summary
    This is the generated driver implementation file for the DMA driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides implementations for driver APIs for DMA CHANNEL2.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.55
        Device            :  PIC18F25K42
        Driver Version    :  2.0
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.43
        MPLAB 	          :  MPLAB X 4.00
*/

/*
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
#include "dma2.h"

/**
  Section: Global Variables Definitions
*/

/**
  Section: DMA APIs
*/
void DMA2_Initialize(void)
{
    DMA2SIRQ = 0x11; // set DMA Transfer Trigger Source
    DMA2AIRQ = 0x01; // set DMA Transfer abort Source
    DMA2CON1 = 0x00; // set modes
    DMA2CON0 = 0xC0; // enable
}

void DMA2_Start(void)
{
    DMA2CON0bits.DGO = 1;   // start
}

void DMA2_WaitUntilTransferCompleted(void)
{
    while(!PIR5bits.DMA2DCNTIF);    // wait for transfer completion
    PIR5bits.DMA2DCNTIF=0;          // clear flag
}




/**
  End of File
*/