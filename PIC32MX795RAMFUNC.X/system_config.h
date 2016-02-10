/* 
 * File:   system_config.h
 * Author: Tim
 *
 * Created on February 5, 2016, 9:44 PM
 */

#ifndef SYSTEM_CONFIG_H
#define	SYSTEM_CONFIG_H

#ifdef	__cplusplus
extern "C" {
#endif


// *****************************************************************************
/* Clock System Service Configuration Options
*/
#define SYS_CLK_FREQ                        80000000ul
#define SYS_CLK_BUS_PERIPHERAL_1            80000000ul
#define SYS_CLK_UPLL_BEFORE_DIV2_FREQ       48000000ul
#define SYS_CLK_CONFIG_PRIMARY_XTAL         8000000ul
#define SYS_CLK_CONFIG_SECONDARY_XTAL       0ul
   
/*** Interrupt System Service Configuration ***/
#define SYS_INT                     true

/*** Ports System Service Configuration ***/
#define SYS_PORT_AD1PCFG        ~0xffdf
#define SYS_PORT_CNPUE          0x0
#define SYS_PORT_CNEN           0x0

#define SYS_PORT_D_TRIS         0xfff8
#define SYS_PORT_D_LAT          0x0
#define SYS_PORT_D_ODC          0x0
    
    
 // *****************************************************************************
/* BSP Configuration Options
*/
#define BSP_OSC_FREQUENCY 8000000


// *****************************************************************************
/* Baud Rate Configuration
*/

#define BAUDRATE2       921600UL  //38400UL //921600UL //57600UL
#define BRG_DIV2        4 
#define BRGH2           1 

#define BAUDRATEREG2        ((SYS_CLK_BUS_PERIPHERAL_1+(BRG_DIV2/2*BAUDRATE2))/BRG_DIV2/BAUDRATE2-1)

#define BAUD_ACTUAL         (SYS_CLK_BUS_PERIPHERAL_1/BRG_DIV2/(BAUDRATEREG2+1))

#define BAUD_ERROR              ((BAUD_ACTUAL > BAUDRATE2) ? BAUD_ACTUAL-BAUDRATE2 : BAUDRATE2-BAUD_ACTUAL)
#define BAUD_ERROR_PERCENT      ((BAUD_ERROR*100+BAUDRATE2/2)/BAUDRATE2)
#if (BAUD_ERROR_PERCENT >= 3)
    #error UART frequency error is worse than 3%
#elif (BAUD_ERROR_PERCENT > 2)
    #warning UART frequency error is worse than 2%
#endif

//#if (BAUDRATEREG2==20)
//    #warning BAUDRATEREG2 is 20
//#elif (BAUDRATEREG2==21)
//    #warning BAUDRATEREG2 is 21
//#endif
   
    


#ifdef	__cplusplus
}
#endif

#endif	/* SYSTEM_CONFIG_H */

