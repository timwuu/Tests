#include <xc.h>
#include <sys/kmem.h>
#include "system_config.h"

void DMA_Initialize();

void SYS_Initialize ( void )
{

    /* Initialize the Application */
//    APP_Initialize();
    
    DMA_Initialize();    
}


void DMA_Initialize()
{
            
    // Initialisation UART
    U1MODE = 0;
    IFS0bits.U1TXIF = 0; 
    IEC0bits.U1TXIE = 0;

    U1MODEbits.BRGH = BRGH2; // Standard speed mode
    U1BRG = BAUDRATEREG2; // Pbclk = 500kHz, baud rate = 2400, error 0.16%
    U1MODEbits.PDSEL = 0x00; // 8 bits data no parity
    U1MODEbits.STSEL = 0; // 1 stop bit
    U1MODEbits.RXINV = 0; // Polarit? de r?ception invers?e
    U1STAbits.UTXINV = 0; // Polarit? de transmission invers?e
    U1STAbits.UTXEN = 1; // Activation transmission
    U1STAbits.UTXISEL = 0x00;
    U1MODEbits.ON = 1; // Activation module UART
    
    // Iniialisation DMA UART TX

    IEC1CLR= _IEC1_DMA0IE_MASK; // disable DMA channel 0 interrupts
    IFS1CLR= _IFS1_DMA0IF_MASK;  //0x00010000; // clear existing DMA channel 0 interrupt flag
    DMACONSET= _DMACON_ON_MASK; // enable the DMA controller

    // program the transfer
//    DCH0SSA=KVA_TO_PA(DRV_NVM_MEDIA_START_ADDRESS); // transfer source physical address
    DCH0DSA=KVA_TO_PA(&U1TXREG); // transfer destination physical address
    DCH0ECONbits.CHSIRQ = _UART1_TX_IRQ; // IRQ UART1 TX
    DCH0ECONbits.SIRQEN = 1; // Activation de la commande via interruption
    DCH0SSIZ=16;  //BUFFSIZE; // source size 256 bytes
    DCH0DSIZ=1; // destination size 1 bytes
    DCH0CSIZ=1; // 1 bytes transferred per event    
    
    TRISEbits.TRISE5 = 0;  //output
    LATEbits.LATE5=0;
            
    //PBCLK = 48MHz
    //PR1= 46874;  // 0.25sec, Prescaler=256
    //T1CONbits.TCKPS=3; //1:256
    //IFS0bits.T1IF=0;
    //T1CONbits.ON=1;    
}
/*******************************************************************************
 End of File
*/

