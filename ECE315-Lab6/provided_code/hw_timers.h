/*
 * hw_timers.h
 *
 *  Created on: Jun 22, 2021
 *      Author: Joe Krachey
 */

#ifndef HW_TIMERS_H_
#define HW_TIMERS_H_

#include <stdbool.h>
#include "msp.h"

#define TICKS_SECOND_1              (SystemCoreClock - 1)   // FIXME -- Currenly 1 second
#define TICKS_MILLISECOND_2         (((2*SystemCoreClock)/1000)-1)

extern volatile bool ALERT_1_SECOND ;
extern volatile bool ALERT_2_MILLISECOND ;

/*****************************************************
 * Configures Timer32_1 to generate a periodic interrupt
 *
 * Parameters
 *      None
 * Returns
 *      None
 *****************************************************/
void hw_timer_init_1S_irq(void);

/*****************************************************
 * Configures Timer32_2 to generate a periodic interrupt
 *
 * Parameters
 *      None
 * Returns
 *      None
 *****************************************************/
void hw_timer_init_2ms_irq(void);
#endif /* HW_TIMERS_H_ */
