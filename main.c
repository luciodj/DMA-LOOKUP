/**
 Demonstrate using DMA1 and DMA2 to perform an automatic table translation

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    Demonstrate using DMA1 and DMA2 to perform an automatic table translation/lookup


  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.55
        Device            :  PIC18F25K42
        Driver Version    :  2.00
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

#include "mcc_generated_files/mcc.h"
#include <string.h>

extern char dict[16] @ 0x100;   // placed at fixed location

char dict_init[16] = { '\n','E','H','L','O','\n','\0'};

char source[] = {2,1,3,3,4,0};  // offsets in the dict


void BUS_ArbiterLock(void)
{
    GIE = 0;                // bus arbiter configuration
    PRLOCK = 0x55;
    PRLOCK = 0xAA;
    PRLOCKbits.PRLOCKED = 1; // lock peripherals
}

void main(void)
{
    SYSTEM_Initialize();
    BUS_ArbiterLock();

    // init the dict
    memcpy(dict, dict_init, sizeof(dict_init));

    // DMA1 moves the pointer (DMA2SSA)
    DMA1SSZ = sizeof(source); // source message
    DMA1DSZ = 1;  // modify only LSB
    DMA1SSA = (uint24_t)source;
    DMA1DSA = (uint24_t)&DMA2SSAL; // move the DMA2 pointer

    //DMA2 fetches the value
    DMA2SSZ = 1;    // translate one byte
    DMA2DSZ = 1;    // to one byte
    DMA2SSA = (uint24_t)dict;
    DMA2DSA = (uint24_t)&U1TXB; // send directly to UART1

    while (1)
    {
        // do not enable PRO mode or the optimizer will remove the whole loop!
    }
}
