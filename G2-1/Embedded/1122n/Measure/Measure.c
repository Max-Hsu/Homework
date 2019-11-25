/******************************************************************************/
/* MEASURE.C: Remote Measurement Recorder                                     */
/******************************************************************************/
/* This file is part of the uVision/ARM development tools.                    */
/* Copyright (c) 2005-2006 Keil Software. All rights reserved.                */
/* This software may only be used under the terms of a valid, current,        */
/* end user licence from KEIL for a compatible version of KEIL software       */
/* development tools. Nothing else gives you the right to use this software.  */
/******************************************************************************/

#include <stdio.h>                       /* standard I/O .h-file              */
#include <ctype.h>                       /* character functions               */
#ifndef MCB2130
  #include <LPC21xx.H>                   /* LPC21xx definitions               */
#else
  #include <LPC213x.H>                   /* LPC213x definitions               */
  #define  ADCR    AD0CR
  #define  ADDR    AD0DR
#endif

#include "measure.h"                     /* global project definition file    */

volatile int button_counter = 0;
volatile int continous_time_button = 0;

struct interval setinterval;                /* interval setting values        */
struct interval interval;                   /* interval counter               */

volatile int measurement_interval = 0;      /* measurement interval over      */
volatile int mdisplay = 0;                  /* measurement display requested  */
volatile int startflag = 0;                 /* start measurement recording    */

struct mrec current;                        /* current measurements           */

#define SCNT  6                             /* number of records              */

struct mrec save_record[SCNT];              /* buffer for measurements        */
int sindex;                                 /* save index                     */
int savefirst;                              /* save first index               */

char ERROR [] = "\n*** ERROR: %s\n";        /* ERROR message string in code   */

#define WRONGINDEX 0xffff                   /* error signal for wrong index   */



/* Default Interrupt Function: may be called when timer ISR is disabled */
void DefISR (void) __irq  {
  ;
}

/******************************************************************************/
/*                Timer Counter 0 interrupt service function                  */
/*                executes each 1ms                                           */
/******************************************************************************/
__irq void tc0 (void) {
  unsigned int val;
  unsigned int crval;
  int i;

  if (measurement_interval)  {                 /* measurement done ?          */
																								/* yes -> save measurements    */
    measurement_interval = 0;                  /* Save measurements done      */
  }
                                               /* check if interval is over   */
  if (interval.min  == 0 &&
      interval.sec  == 0 &&
      interval.msec == 0     )  {
    interval = setinterval;                    /* set interval time again     */
    measurement_interval = startflag;          /* determine measurement flag  */
  }
  else  {                                      /* update interval time        */
    if (interval.msec-- == 0)  {               /* calculate millisecond       */
      interval.msec = 999;
      if (interval.sec-- == 0)  {              /* calculate second            */
        interval.sec = 59;
        interval.min--;                        /* calculate minute            */
      }
    }
  }
                                               /* update current time         */
  if (++current.time.msec == 1000)  {          /* update millisecond cnt      */
    current.time.msec = 0;

    if (++current.time.sec == 60)  {           /* update second counter       */
      current.time.sec = 0;

      if (++current.time.min == 60)  {         /* update minute counter       */
        current.time.min = 0;

        if (++current.time.hour == 24)  {      /* update hour counter         */
          current.time.hour = 0;
        }
      }
    }
  }	/* end of if( ++current.time.msec... */

  if (measurement_interval || mdisplay)  {     /* process measurement         */
    current.port0 = IOPIN0;                    /* read port 0                 */
    for (i = 0; i != 4; i++) {                 /* loop for 4 A/D inputs       */
      crval = 0x01000000 | (1<<i);
      ADCR |= crval;                           /* Start A/D Conversion        */
      do {
        val = ADDR;                            /* Read A/D Data Register      */
      } while ((val & 0x80000000) == 0);       /* Wait for end of A/D Convers.*/
      ADCR &= ~crval;                          /* Stop A/D Conversion         */
      val = (val >> 8) & 0xFF;                 /* Extract AIN Value           */
      current.analog[i] = val;                 /* result of A/D process       */ 
    }
    mdisplay = 0;                              /* mdisplay = 0 for ready sig. */
  }

  T0IR = 1;                                    /* Clear interrupt flag        */
  VICVectAddr = 0;                             /* Acknowledge Interrupt       */
}





/******************************************************************************/
/***************************      MAIN PROGRAM      ***************************/
/******************************************************************************/
int main (void)  {                             /* main entry for program      */
  char cmdbuf [15];                            /* command input buffer        */
  int i;                                       /* index for command buffer    */
  int idx;                                     /* index for circular buffer   */

  PINSEL1 = 0x15400000;                        /* Select AIN0..AIN3           */
  IODIR1  = 0xFF0000;                          /* P1.16..23 defined as Outputs*/
	//how to define input for port 0
	
  ADCR    = 0x002E0401;                        /* Setup A/D: 10-bit @ 3MHz    */

  init_serial ();                              /* initialite serial interface */

  /* setup the timer counter 0 interrupt */
  T0MR0 = 14999;                               /* 1mSec = 15.000-1 counts     */
  T0MCR = 3;                                   /* Interrupt and Reset on MR0  */
  T0TCR = 1;                                   /* Timer0 Enable               */
  VICVectAddr0 = (unsigned long)tc0;           /* set interrupt vector in 0   */
  VICVectCntl0 = 0x20 | 4;                     /* use it for Timer 0 Interrupt*/
  VICIntEnable = 0x00000010;                   /* Enable Timer0 Interrupt     */
  VICDefVectAddr = (unsigned long) DefISR;     /* un-assigned VIC interrupts  */

																								/* initialize circular buffer  */
  //printf ( menu );                             /* display command menu        */
  while (1)  {                                 /* loop forever                */
    
  }
}
