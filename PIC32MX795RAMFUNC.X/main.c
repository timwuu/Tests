/* 
 * File:   main.c
 * Author: Tim
 *
 *   1. test ram function
 *   2. test ram function copy
 *   3. test R/W at RAM Kernel Program
 * 
 *   notes: 
 *   myramfunc at 0xA0008000, return an unsigned integer for PR1
 *   ptmyramfunc pointer to a ramfunc at 0xA0018000 which is a copy of myramfunc
 *   ptPR1 at 0xA0010000, a unsigned integer pointer
 * 
 * Created on December 19, 2015, 6:01 PM
 */

#include <xc.h>
#include <stdbool.h>
#include <stdint.h>
#include <sys\kmem.h>
//#include <sys\attribs.h>
//#include "arduino.h"


//#define _BMXBMXDKPBA 0x00008000

#define HIGH 1
#define LOW 0
#define OUTPUT 0
#define BUFFSIZE 512

void setup(void);
void loop(void);

unsigned int *ptPR1;

/************************************************
 * timijk: BMXDRMSZ: 128k
 * RAM Data:32k, RAM Program:96k
 * setup in blt_mx.ld 
 ************************************************/ 
// a dummy ram function to set the value of BMXDKPBA 
__attribute__((ramfunc,section(".ramfunc"),far,unique_section))
unsigned int myramfunct (void)
{ return *ptPR1; }

// ramfunc pointer
__attribute__((ramfunc,section(".ramfunc"),far,unique_section))
unsigned int (*ptmyramfunct) (void);

void main()
{   
    setup();
    while(1){ loop();}
}

void SYS_Initialize ( void );

void setup()
{
    int i;
   
    unsigned char *pt1;
    unsigned char *pt2;

    ptPR1= (unsigned int *)0xA0010000L;
    
    *ptPR1= 31249; // 62499;
    
    ptmyramfunct = (void*)0xA0018000L;
    
    pt1= (void*)&myramfunct;
    pt2= (void*)ptmyramfunct;
    
    //sizeof(myramfunct) not working
    for(i=0; i<0x0C; i++) *pt2++ = *pt1++;
                
    TRISEbits.TRISE5 = 0;  //output
    LATEbits.LATE5=0;
 
    //PBCLK = 80MHz
    T1CONbits.TCKPS = 0b11;  // Prescaler=256
    //PR1= myramfunct();  //31249;  // 0.1sec,
    PR1 = (*ptmyramfunct)();
    IFS0bits.T1IF=0;
    T1CONbits.ON=1;

}

void loop()
{
    
    while(IFS0bits.T1IF==0);

    LATEbits.LATE5 ^= HIGH;
    
    IFS0bits.T1IF=0;
    
}
