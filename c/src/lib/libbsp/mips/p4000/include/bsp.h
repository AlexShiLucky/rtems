/*  bsp.h
 *
 *  This include file contains all board IO definitions.
 *
 *  XXX : put yours in here
 *
 *  COPYRIGHT (c) 1989-1999.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id$
 */
/* @(#)bsp.h       03/15/96     1.1 */

#ifndef __P4000_BSP_h
#define __P4000_BSP_h

#ifdef __cplusplus
extern "C" {
#endif

#include <bspopts.h>

#include <rtems.h>
#include <rtems/console.h>
#include <rtems/clockdrv.h>

/*
 *  confdefs.h overrides for this BSP:
 *   - number of termios serial ports (defaults to 1)
 *   - Interrupt stack space is not minimum if defined.
 */

/* #define CONFIGURE_NUMBER_OF_TERMIOS_PORTS 2 */
#define CONFIGURE_INTERRUPT_STACK_MEMORY  (4 * 1024)

extern void WriteDisplay( char * string );

extern uint32_t   mips_get_timer( void );

#define CPU_CLOCK_RATE_MHZ     (50)
#define CLOCKS_PER_MICROSECOND ( CPU_CLOCK_RATE_MHZ ) /* equivalent to CPU clock speed in MHz */

/*
 *  Simple spin delay in microsecond units for device drivers.
 *  This is very dependent on the clock speed of the target.
 *
 *  NOTE: This macro generates a warning like "integer constant out
 *        of range" which is safe to ignore.  In 64 bit mode, uint32_t
 *        types are actually 64 bits long so that comparisons between
 *        uint32_t   types and pointers are valid.  The warning is caused
 *        by code in the delay macro that is necessary for 64 bit mode.
 */

#define rtems_bsp_delay( microseconds ) \
  { \
     uint32_t   _end_clock = \
          mips_get_timer() + microseconds * CLOCKS_PER_MICROSECOND; \
     _end_clock %= 0x100000000;  /* make sure result is 32 bits */ \
     \
     /* handle timer overflow, if necessary */ \
     while ( _end_clock < mips_get_timer() );  \
     \
     while ( _end_clock > mips_get_timer() ); \
  }

/* Constants */

#define RAM_START 0
#define RAM_END   0x100000

/* miscellaneous stuff assumed to exist */

extern rtems_configuration_table BSP_Configuration;

/*
 *  Device Driver Table Entries
 */

/*
 * NOTE: Use the standard Console driver entry
 */

/*
 * NOTE: Use the standard Clock driver entry
 */

/* miscellaneous stuff assumed to exist */

mips_isr_entry set_vector(                      /* returns old vector */
  rtems_isr_entry     handler,                  /* isr routine        */
  rtems_vector_number vector,                   /* vector number      */
  int                 type                      /* RTEMS or RAW intr  */
);

#ifdef __cplusplus
}
#endif

#endif
/* end of include file */
